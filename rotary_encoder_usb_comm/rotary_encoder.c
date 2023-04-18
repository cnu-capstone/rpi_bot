// Moved to Header File
// #include <stdio.h>
// #include "pico/stdlib.h"
// #include "hardware/gpio.h"

// // Pin assignments for encoder inputs
// #define ENCODER_PIN_A 14
// #define ENCODER_PIN_B 15
// #define ENCODER_PIN_A_RIGHT 18
// #define ENCODER_PIN_B_RIGHT 19
#include "../../includes/rotary_encoder.h"

// Global variable to store encoder count
volatile int32_t encoder_count = 0;
volatile int32_t encoder_count_RIGHT = 0;

// Interrupt handler for encoder input A
void encoder_isr_A(uint gpio, uint32_t events) {
   if (gpio == ENCODER_PIN_A) {
        if (gpio_get(ENCODER_PIN_A)) {  // Check if input A is high
            if (gpio_get(ENCODER_PIN_B)) {
                encoder_count++;  // Clockwise rotation
            } else {
                encoder_count--;  // Counter-clockwise rotation
            }
        } else {  // Input A is low
            if (gpio_get(ENCODER_PIN_B)) {
                encoder_count--;  // Counter-clockwise rotation
            } else {
                encoder_count++;  // Clockwise rotation
            }
        }
    }
}

// Interrupt handler for encoder input A
void encoder_isr_A_RIGHT(uint gpio, uint32_t events) {
    if (gpio == ENCODER_PIN_A_RIGHT) {
        if (gpio_get(ENCODER_PIN_A_RIGHT)) {  // Check if input A is high
            if (gpio_get(ENCODER_PIN_B_RIGHT)) {
                encoder_count_RIGHT++;  // Clockwise rotation
            } else {
                encoder_count_RIGHT--;  // Counter-clockwise rotation
            }
        } else {  // Input A is low
            if (gpio_get(ENCODER_PIN_B_RIGHT)) {
                encoder_count_RIGHT--;  // Counter-clockwise rotation
            } else {
                encoder_count_RIGHT++;  // Clockwise rotation
            }
        }
    }
}

int encoder_left() {
    gpio_init(ENCODER_PIN_A);  // Initialize encoder input A
    gpio_set_dir(ENCODER_PIN_A, GPIO_IN);
    gpio_pull_up(ENCODER_PIN_A);

    gpio_init(ENCODER_PIN_B);  // Initialize encoder input B
    gpio_set_dir(ENCODER_PIN_B, GPIO_IN);
    gpio_pull_up(ENCODER_PIN_B);
    
    gpio_set_irq_enabled_with_callback(ENCODER_PIN_A, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &encoder_isr_A);  // Enable interrupt on encoder input A

    return encoder_count;
}

int encoder_right() {
    gpio_init(ENCODER_PIN_A_RIGHT);  // Initialize encoder input A
    gpio_set_dir(ENCODER_PIN_A_RIGHT, GPIO_IN);
    gpio_pull_up(ENCODER_PIN_A_RIGHT);

    gpio_init(ENCODER_PIN_B_RIGHT);  // Initialize encoder input B
    gpio_set_dir(ENCODER_PIN_B_RIGHT, GPIO_IN);
    gpio_pull_up(ENCODER_PIN_B_RIGHT);
    
    gpio_set_irq_enabled_with_callback(ENCODER_PIN_A_RIGHT, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &encoder_isr_A_RIGHT);  // Enable interrupt on encoder input A
    
    return encoder_count_RIGHT;
}

// int main() {
//     stdio_init_all();  // Initialize stdio for printing

//     while (true) {
//         // Print encoder count
       
//         sleep_ms(500);
//         encoder_right();
//         sleep_ms(500);
//         encoder_left();  // Delay for stability
//     }

//     return 0;
// }
