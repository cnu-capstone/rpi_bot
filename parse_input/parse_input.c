#include "pico/stdlib.h"

const uint bit_width = 4;
const uint COMMS[bit_width] = {2, 3, 4, 5};
const uint LED_PIN = 22;

void pico_init() {
    for (uint i = 0; i < bit_width; i++) {
        gpio_init(COMMS[i]);
        gpio_set_dir(COMMS[i], GPIO_IN);
    }
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void pico_clear_gpio() {
    gpio_put(LED_PIN, false);
}

void blink_led(bool* instr) {
    for (uint i = 0; i < bit_width; i++) {
        gpio_put(LED_PIN, *(instr + i));
    }
}

int main() {
    pico_init();

    bool instructions[bit_width];

    while (1) {
        sleep_ms(100);
        for (uint i = 0; i < bit_width; i++) {
            instructions[i] = gpio_get(COMMS[i]);
        }
    }

    pico_clear_gpio();
    return 0;
}
