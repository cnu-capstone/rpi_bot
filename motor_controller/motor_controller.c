#include <stdio.h>  // COMM STUFF
#include "pico/stdlib.h"

#ifndef bit_width
#define bit_width 3
#endif

#ifndef CMD_LEN
#define CMD_LEN 8
#endif

bool INSTRUCTIONS[bit_width] = {false, false, false};  // Enable, A, B
const uint MOTOR1_ENABLE_PIN = 18;  // Right Motor
const uint MOTOR1_POS_PIN = 19;
const uint MOTOR2_POS_PIN = 20;
const uint MOTOR2_ENABLE_PIN = 21;  // Left Motor
// const uint LED_PIN = PICO_DEFAULT_LED_PIN;  // PICO W is pin 22
const uint LED_PIN = 22;  // Uncomment for PICO W usage

// COMM PORT CODE
void read_stream(char* buff) {
    scanf("%8s", buff);

    printf("Data received: %s\n", buff);
}

void enqueue(char* data, char* buff) {
    for (int i = 0; i < CMD_LEN; i++) {
        *(buff++) = *(data+i);  // Dereference data at position i and store into buff and increment buff position
    }
}

// MOTOR CODE
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

// void motor_forward(int duty_cycle) {  // With DUTY CYCLE
//     // SET MOTOR DIRECTION FORWARD
//     gpio_put(MOTOR1_POS_PIN, true);
//     gpio_put(MOTOR2_POS_PIN, true);
//     // SET DUTY CYCLE
//     gpio_put(MOTOR1_ENABLE_PIN, true);
//     gpio_put(MOTOR2_ENABLE_PIN, true);
//     sleep_ms(duty_cycle);
//     if (duty_cycle > 0) {
//         gpio_put(MOTOR1_ENABLE_PIN, false);
//         gpio_put(MOTOR2_ENABLE_PIN, false);
//         sleep_ms(100-duty_cycle);
//     }
// }

void motor_forward() {
    // SET MOTOR DIRECTION FORWARD
    gpio_put(MOTOR1_POS_PIN, true);
    gpio_put(MOTOR2_POS_PIN, true);
    // SET MOTOR STATE TO ON
    gpio_put(MOTOR1_ENABLE_PIN, true);
    gpio_put(MOTOR2_ENABLE_PIN, true);
    sleep_ms(1000);
}

void motor_right() {  // 0 Degree Turn
    // SET LEFT MOTOR FORWARD and RIGHT MOTOR BACKWARD
    gpio_put(MOTOR2_POS_PIN, true);
    gpio_put(MOTOR1_POS_PIN, false);
    // SET MOTOR STATE TO ON
    gpio_put(MOTOR2_ENABLE_PIN, true);
    gpio_put(MOTOR1_ENABLE_PIN, true);
    sleep_ms(1000);
}

void motor_left() {  // 0 Degree Turn
    // SET RIGHT MOTOR FORWARD and LEFT MOTOR BACKWARD
    gpio_put(MOTOR2_POS_PIN, false);
    gpio_put(MOTOR1_POS_PIN, true);
    // SET MOTOR STATE TO ON
    gpio_put(MOTOR2_ENABLE_PIN, true);
    gpio_put(MOTOR1_ENABLE_PIN, true);
    sleep_ms(1000);
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
    stdio_init_all();  // INIT COMM
    pico_init();  // INIT GPIO

    char cmd[CMD_LEN];

    while(1) {
        read_stream(cmd);

        for (int i = 0; i < bit_width; i ++) {
            if (cmd[i] == '1') {
                INSTRUCTIONS[i] = true;
            }
        }

        if (INSTRUCTIONS[0] && INSTRUCTIONS[1] && INSTRUCTIONS[2]) {  // 111
            motor_forward();
        }
        else if (INSTRUCTIONS[0] && !INSTRUCTIONS[1] && INSTRUCTIONS[2]) {  // 101
            motor_left();
        }
        else if (INSTRUCTIONS[0] && INSTRUCTIONS[1] && !INSTRUCTIONS[2]) {  // 110
            motor_right();
        }
        else {
            motor_stall();
        }
        // gpio_put(LED_PIN, true);
        // Drive
        // motor_forward(100);
        // motor_forward(50);
        // motor_forward(25);
        // Stall
        // gpio_put(LED_PIN, false);
        // motor_stall();
        motor_stall();
    }

    pico_deinit();
    return 0;
}