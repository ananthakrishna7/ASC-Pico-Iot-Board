#include "pico/stdlib.h"
#include <stdio.h>

int main() {
	stdio_usb_init();
	
	gpio_init(25);
	gpio_set_dir(25, GPIO_OUT);

	char str[50];
	int a, b;
	char op;
	gpio_put(25, 1);

	while (true) {
		printf("Enter the appropriate values: \n");
		fgets(str, 50, stdin);
		sscanf(str, "%d %c %d", &a, &op, &b);
		gpio_put(25, 0);
		switch(op) {
			case '+':
				printf("%d\n", a+b);
				break;
			case '-':
				printf("%d\n", a-b);
				break;
			case '*':
				printf("%d\n", a*b);
				break;
			case '/':
				printf("%d\n", a/b);
				break;
			case '^':
				int p = 1;
				for (int i= 0; i <= b; i++) {
					p *= a;
				}
				printf("%d\n", p);
				break;
			default:
				printf("INVALID OPERAND %hhu \n", op);
		}
		sleep_ms(500);
		gpio_put(25, 1);

	}
	return 0;
}
