// Returns temperature in DegC, resolution is 0.01 DegC. Output value of “5123” equals 51.23 DegC.
// t_fine carries fine temperature as global value

#include "bmp280.h"

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

#include <stdint.h>

#define BMP280_S32_t int32_t
#define BMP280_U32_t uint32_t
#define BMP280_S64_t int64_t

static BMP280_S32_t t_fine = 0;

// Returns temperature in DegC, resolution is 0.01 DegC, Output value of "5123"
// equals 51.23 DegC
// t_fine carries fine temperature as global value
static BMP280_S32_t bmp280_compensate_T_int32(BMP280_S32_t adc_T, struct bmp280 *bmp)
{
	BMP280_S32_t var1, var2, T;
	var1 = ((((adc_T>>3) - ((BMP280_S32_t)bmp->dig_T1<<1))) * ((BMP280_S32_t)bmp->dig_T2)) >> 11;
	var2 = (((((adc_T>>4) - ((BMP280_S32_t)bmp->dig_T1)) * ((adc_T>>4) - ((BMP280_S32_t)bmp->dig_T1))) >> 12) *
			((BMP280_S32_t)bmp->dig_T3)) >> 14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	return T;
}

// Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8 fractional bits).
// Output value of “24674867” represents 24674867/256 = 96386.2 Pa = 963.862 hPa
static BMP280_U32_t bmp280_compensate_P_int64(BMP280_S32_t adc_P, struct bmp280 *bmp)
{
	BMP280_S64_t var1, var2, p;
	var1 = ((BMP280_S64_t)t_fine) - 128000;
	var2 = var1 * var1 * (BMP280_S64_t)bmp->dig_P6;
	var2 = var2 + ((var1*(BMP280_S64_t)bmp->dig_P5)<<17);
	var2 = var2 + (((BMP280_S64_t)bmp->dig_P4)<<35);
	var1 = ((var1 * var1 * (BMP280_S64_t)bmp->dig_P3)>>8) + ((var1 * (BMP280_S64_t)bmp->dig_P2)<<12);
	var1 = (((((BMP280_S64_t)1)<<47)+var1))*((BMP280_S64_t)bmp->dig_P1)>>33;
	if (var1 == 0)
	{
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576-adc_P;
	p = (((p<<31)-var2)*3125)/var1;
	var1 = (((BMP280_S64_t)bmp->dig_P9) * (p>>13) * (p>>13)) >> 25;
	var2 = (((BMP280_S64_t)bmp->dig_P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((BMP280_S64_t)bmp->dig_P7)<<4);
	return (BMP280_U32_t)p;
}

int bmp280_init(struct bmp280 *bmp, i2c_inst_t *i2c) {
	i2c_init(i2c, 100000);
	bmp->i2c = i2c;
	gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
	gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
	gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
	gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

	uint8_t buf[2];

	buf[0] = BMP_REG_ID;
	i2c_write_blocking(i2c, bmp->conf.addr, (uint8_t*)buf, 1, true);
	i2c_read_blocking(i2c, bmp->conf.addr, (uint8_t*)&(bmp->id), 1, false);

	buf[0] = BMP_REG_CTRL;
	buf[1] = bmp->conf.oversamp | bmp->conf.powmode;
	i2c_write_blocking(i2c, bmp->conf.addr, (uint8_t*)buf, 2, false);
	
	buf[0] = BMP_REG_CONF;
	buf[1] = bmp->conf.sbtime | (bmp->conf.filter_coeff << 1);
	i2c_write_blocking(i2c, bmp->conf.addr, (uint8_t*)buf, 2, false);

	char comp_buf[24];

	buf[0] = 0x88;
	i2c_write_blocking(i2c, bmp->conf.addr, (uint8_t*)buf, 1, 1);
	i2c_read_blocking(i2c, bmp->conf.addr, (uint8_t *)comp_buf, 24, false);

	bmp->dig_T1 = (uint16_t)comp_buf[0] | ((uint16_t)comp_buf[1] << 8);
	bmp->dig_T2 = (int16_t)comp_buf[2] | ((int16_t)comp_buf[3] << 8);
	bmp->dig_T3 = (int16_t)comp_buf[4] | ((int16_t)comp_buf[5] << 8);

	bmp->dig_P1 = (uint16_t)comp_buf[6] | ((uint16_t)comp_buf[7] << 8);
	bmp->dig_P2 = (int16_t)comp_buf[8] | ((int16_t)comp_buf[9] << 8);
	bmp->dig_P3 = (int16_t)comp_buf[10] | ((int16_t)comp_buf[11] << 8);
	bmp->dig_P4 = (int16_t)comp_buf[12] | ((int16_t)comp_buf[13] << 8);
	bmp->dig_P5 = (int16_t)comp_buf[14] | ((int16_t)comp_buf[15] << 8);
	bmp->dig_P6 = (int16_t)comp_buf[16] | ((int16_t)comp_buf[17] << 8);
	bmp->dig_P7 = (int16_t)comp_buf[18] | ((int16_t)comp_buf[19] << 8);
	bmp->dig_P8 = (int16_t)comp_buf[20] | ((int16_t)comp_buf[21] << 8);
	bmp->dig_P9 = (int16_t)comp_buf[22] | ((int16_t)comp_buf[23] << 8);
}

int bmp280_read(struct bmp280 *bmp, struct bmp280_reading *out) {
	int32_t raw_p, raw_t;

	char buf[6];

	char addr = BMP_REG_P_MSB;

	i2c_write_blocking(bmp->i2c, bmp->conf.addr, (uint8_t*)&addr, 1, true);
	i2c_read_blocking(bmp->i2c, bmp->conf.addr, (uint8_t *)buf, 6, false);

	raw_p = ((int32_t)buf[0] << 12) | ((int32_t)buf[1] << 4) | ((int32_t)buf[2] >> 4);
	raw_t  = ((int32_t)buf[3] << 12) | ((int32_t)buf[4] << 4) | ((int32_t)buf[5] >> 4);

	out->pres = (float)bmp280_compensate_P_int64(raw_p, bmp)/256.0f;
	out->temp = (float)bmp280_compensate_T_int32(raw_t, bmp)/100.0f;

	return 0;
}
