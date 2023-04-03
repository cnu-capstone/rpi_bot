#include "pico/stdlib.h"

#define bit_width 4

const uint COMM_PORTS[bit_width] = {2, 3, 4, 5};  //MSB->LSB
const uint LED_PIN = 22;

bool instructions[bit_width] = {false, false, false, false};

void pico_init() {
    for (int i = 0; i < bit_width; i++) {
        gpio_init(COMM_PORTS[i]);
        gpio_set_dir(COMM_PORTS[i], GPIO_IN);
    }
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void pico_clear_gpio() {
    gpio_put(LED_PIN, false);
}

void blink_led() {
    for (int i = 0; i < bit_width; i++) {
        gpio_put(LED_PIN, instructions[i]);
        sleep_ms(1000);  // Delay for visibility
    }
}

void pico_load_instr() {
    for (int i = 0; i < bit_width; i++) {
        instructions[i] = gpio_get(COMM_PORTS[i]);  // Load instruction from respective pin state
        // instructions[i] = i%2==0;  // Load instruction for testing (T,F,T,F)
    }
}

int main() {
    pico_init();

    while (1) {
        pico_load_instr();
        sleep_ms(1000);
        blink_led();
    }

    pico_clear_gpio();
    return 0;
}
