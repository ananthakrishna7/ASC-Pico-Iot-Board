#ifndef BMP280_H
#define BMP280_H

#include "hardware/i2c.h"
#include <stdint.h>

#define BMP_OSAMP_T_0 		(0)
#define BMP_OSAMP_T_1 		(1 << 5)
#define BMP_OSAMP_T_2 		(2 << 5)
#define BMP_OSAMP_T_4 		(3 << 5)
#define BMP_OSAMP_T_8 		(4 << 5)
#define BMP_OSAMP_T_16		(5 << 5)

#define BMP_OSAMP_P_0  		(0)
#define BMP_OSAMP_P_1  		(1 << 2)
#define BMP_OSAMP_P_2  		(2 << 2)
#define BMP_OSAMP_P_4  		(3 << 2)
#define BMP_OSAMP_P_8  		(4 << 2)
#define BMP_OSAMP_P_16 		(5 << 2)

#define BMP_POWMODE_SLEEP  	0
#define BMP_POWMODE_FORCED 	1
#define BMP_POWMODE_NORMAL 	3

#define BMP_SBTIME_0_5		(0)
#define BMP_SBTIME_62_5		(1 << 5)
#define BMP_SBTIME_125		(2 << 5)
#define BMP_SBTIME_250		(3 << 5)
#define BMP_SBTIME_500		(4 << 5)
#define BMP_SBTIME_1000		(5 << 5)
#define BMP_SBTIME_2000		(6 << 5)
#define BMP_SBTIME_4000		(7 << 5)

#define BMP_REG_ID 		0xD0
#define BMP_REG_RESET 		0xE0
#define BMP_REG_STATUS 		0xF3
#define BMP_REG_CTRL 		0xF4
#define BMP_REG_CONF 		0xF5
#define BMP_REG_P_MSB 		0xF7
#define BMP_REG_P_LSB 		0xF8
#define BMP_REG_P_XLSB 		0xf9
#define BMP_REG_T_MSB 		0xFA
#define BMP_REG_T_LSB 		0xFB
#define BMP_REG_T_XLSB 		0xFC


struct bmp280_config {
	char addr;
	char oversamp;
	char powmode;
	char sbtime;
	char filter_coeff;

};

struct bmp280 {
	struct bmp280_config conf;
	i2c_inst_t *i2c;
	uint16_t dig_T1;
	int16_t dig_T2, dig_T3;

	char id;

	uint16_t dig_P1;
	int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;

};

struct bmp280_reading {
	float temp;
	float pres;
};

int bmp280_init(struct bmp280 *bmp, i2c_inst_t *i2c);
int bmp280_read(struct bmp280 *bmp, struct bmp280_reading *out);

#endif // Header guard
