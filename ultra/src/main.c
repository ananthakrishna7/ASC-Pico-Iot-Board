#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/multicore.h"

#define TRIG_PIN 8
#define ECHO_PIN 7
#define LED_PIN 25

int delay = 10;

void blink_led() {
	while (1) {
		gpio_put(LED_PIN, 1);
		sleep_ms(delay);
		gpio_put(LED_PIN, 0);
		sleep_ms(delay);
	}
}

float map (float s, float a1, float a2, float b1, float b2) {
	return (s-a1)/(a2-a1) * (b2-b1) + b1;
}

int main() {
	stdio_init_all();

	gpio_init(TRIG_PIN);
	gpio_init(ECHO_PIN);
	gpio_init(LED_PIN);

	gpio_set_dir(TRIG_PIN, GPIO_OUT);
	gpio_set_dir(ECHO_PIN, GPIO_IN);
	gpio_set_dir(LED_PIN, GPIO_OUT);

	gpio_put(TRIG_PIN, 0);

	multicore_launch_core1(blink_led);

	int64_t us;
	float dist;

	while (true) {
		us = 0;

		gpio_put(TRIG_PIN, 1);
		sleep_us(10);
		gpio_put(TRIG_PIN, 0);

		while (!gpio_get(ECHO_PIN)) {
		}

		while (gpio_get(ECHO_PIN)) {
			us++;
			sleep_us(1);
		}

		dist = (float)us/58.0f;
		if (dist < 100) {
			printf("%.2f\n", dist);
			delay = map(dist, 0, 100, 10, 1000);
		}
		sleep_ms(500);

	}
	return 0;
}
