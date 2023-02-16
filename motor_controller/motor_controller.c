#include "pico/stdlib.h"

#ifndef bit_width
#define bit_width 3
#endif

bool INSTRUCTIONS[bit_width] = {false, false, false};  // Enable, A, B
const uint MOTOR_POS_PIN = 21;
const uint MOTOR_NEG_PIN = 20;

// Enable, A, B
// 110, 010

void pico_init() {
    gpio_init(MOTOR_POS_PIN);
    gpio_set_dir(MOTOR_POS_PIN, GPIO_OUT);
    gpio_init(MOTOR_NEG_PIN);
    gpio_set_dir(MOTOR_NEG_PIN, GPIO_OUT);
}

void pico_deinit() {
    gpio_deinit(MOTOR_POS_PIN);
    gpio_deinit(MOTOR_NEG_PIN);
}

void motor_forward() {
    sleep_ms(10);
    gpio_put(MOTOR_POS_PIN, true);
    gpio_put(MOTOR_NEG_PIN, false);
}

void motor_reverse() {
    sleep_ms(10);
    gpio_put(MOTOR_POS_PIN, false);
    gpio_put(MOTOR_NEG_PIN, true);
}

void motor_stall() {
    gpio_put(MOTOR_POS_PIN, true);
    gpio_put(MOTOR_NEG_PIN, true);
}

int main() {
    pico_init();
    
    motor_stall();
    motor_forward();

    sleep_ms(100);

    motor_stall();
    motor_reverse();

    pico_deinit();
    return 0;
}