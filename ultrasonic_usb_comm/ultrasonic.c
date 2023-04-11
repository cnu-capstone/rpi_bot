#include <stdio.h>
#include "pico/stdlib.h"

#define SUCCESS 0

int main() {
	stdio_init_all();
	
	while (1) {
		printf("Hello World");  // Use printf whenever you need std out
	}
	
	return SUCCESS;
}
