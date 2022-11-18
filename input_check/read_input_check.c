#include "pico/stdlib.h"

const uint SIGNAL_PIN = 0;
const uint RECEIVE_PIN = 20;
const uint LED_PIN = 22;

void pico_init() {
    gpio_init(SIGNAL_PIN);
    gpio_set_dir(SIGNAL_PIN, GPIO_OUT);

    gpio_init(RECEIVE_PIN);
    gpio_set_dir(RECEIVE_PIN, GPIO_IN);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

int pico_deconstruct() {
    gpio_put(LED_PIN, false);
    gpio_put(SIGNAL_PIN, false);
    return 0;
}

int main() {
    pico_init();

    gpio_put(SIGNAL_PIN, true);
    sleep_ms(1000);
    bool receive_pin_state = gpio_get(RECEIVE_PIN);
    sleep_ms(1000);
    if (receive_pin_state) {
        gpio_put(LED_PIN, true);
    }
    sleep_ms(2000);

    return pico_deconstruct();
}