#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int main() {
    // stdio_init_all();
    // if (cyw43_arch_init()) {
    //     printf("WiFi init failed");
    //     return -1;
    // }
    const uint LED_PIN = 22;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, 1);
        // cyw43_arch_gpio_put();
        sleep_ms(330);
        gpio_put(LED_PIN, 0);
        // cyw43_arch_gpio_put();
        sleep_ms(330);
    }
    return 0;
}