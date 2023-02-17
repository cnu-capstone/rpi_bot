#include "pico/stdlib.h"

#ifndef bit_width
#define bit_width 3
#endif

bool INSTRUCTIONS[bit_width] = {false, false, false};  // Enable, A, B
const uint MOTOR1_ENABLE_PIN = 18;
const uint MOTOR1_POS_PIN = 19;
const uint MOTOR2_POS_PIN = 20;
const uint MOTOR2_ENABLE_PIN = 21;
const uint LED_PIN = PICO_DEFAULT_LED_PIN;

void pico_init() {
    // MOTOR1 INIT
    gpio_init(MOTOR1_POS_PIN);
    gpio_set_dir(MOTOR1_POS_PIN, GPIO_OUT);
    gpio_init(MOTOR1_ENABLE_PIN);
    gpio_set_dir(MOTOR1_ENABLE_PIN, GPIO_OUT);
    // MOTOR2 INIT
    gpio_init(MOTOR2_POS_PIN);
    gpio_set_dir(MOTOR2_POS_PIN, GPIO_OUT);
    gpio_init(MOTOR2_ENABLE_PIN);
    gpio_set_dir(MOTOR2_ENABLE_PIN, GPIO_OUT);
    // LED PIN INIT
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void pico_deinit() {
    gpio_put(MOTOR1_POS_PIN, false);
    gpio_put(MOTOR1_ENABLE_PIN, false);
    gpio_put(MOTOR2_POS_PIN, false);
    gpio_put(MOTOR2_ENABLE_PIN, false);
    gpio_put(LED_PIN, false);
    // MOTOR1 DEINIT
    gpio_deinit(MOTOR1_POS_PIN);
    gpio_deinit(MOTOR1_ENABLE_PIN);
    // MOTOR2 DEINIT
    gpio_deinit(MOTOR2_POS_PIN);
    gpio_deinit(MOTOR2_ENABLE_PIN);
    // LED PIN DEINIT
    gpio_deinit(LED_PIN);
}

void motor_forward(int duty_cycle) {
    // SET MOTOR DIRECTION FORWARD
    gpio_put(MOTOR1_POS_PIN, true);
    gpio_put(MOTOR2_POS_PIN, true);
    // SET DUTY CYCLE
    gpio_put(MOTOR1_ENABLE_PIN, true);
    gpio_put(MOTOR2_ENABLE_PIN, true);
    sleep_ms(duty_cycle);
    if (duty_cycle > 0) {
        gpio_put(MOTOR1_ENABLE_PIN, false);
        gpio_put(MOTOR2_ENABLE_PIN, false);
        sleep_ms(100-duty_cycle);
    }
}

// void motor_reverse() {
//     sleep_ms(100);
//     gpio_put(MOTOR_POS_PIN, false);
//     gpio_put(MOTOR_NEG_PIN, true);
// }

void motor_stall() {
    gpio_put(MOTOR1_ENABLE_PIN, false);
    gpio_put(MOTOR2_ENABLE_PIN, false);
    sleep_ms(1000);
}

int main() {
    pico_init();

    while(1) {
        // gpio_put(LED_PIN, true);
        // Drive
        motor_forward(100);
        // motor_forward(50);
        // motor_forward(25);
        // Stall
        // gpio_put(LED_PIN, false);
        // motor_stall();
    }

    pico_deinit();
    return 0;
}