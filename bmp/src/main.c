#include "bmp280.h"

#include <stdio.h>
#include "pico/stdio.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

#define LED_PIN 25

int main() {
	stdio_init_all();

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	gpio_put(LED_PIN, 1);

	struct bmp280 bmp;

	struct bmp280_reading r;

	bmp.conf.addr = 0x76;
	bmp.conf.oversamp = BMP_OSAMP_P_4 | BMP_OSAMP_T_1;
	bmp.conf.powmode = BMP_POWMODE_NORMAL;
	bmp.conf.sbtime = BMP_SBTIME_0_5;
	bmp.conf.filter_coeff = 4;

	sleep_ms(1000);


	bmp280_init(&bmp, i2c_default);

	sleep_ms(1000);

	while (true) {
		printf("Reading from id %#hhx ..\n", bmp.id);
		bmp280_read(&bmp, &r);
		printf("Pressure: %.2f Temperature: %.2f\n", r.pres, r.temp);
		sleep_ms(2000);
	}

	return 0;
}
