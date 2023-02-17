#include "pico/stdlib.h"

int main() {
    // const uint LED_PIN = 22;  // PICO W LED PIN
    const uint LED_PIN = 25;  // PICO LED PIN
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, true);
        sleep_ms(1000);
        gpio_put(LED_PIN, false);
        sleep_ms(1000);
    }
    return 0;
}
