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

float ticks_to_cm(int num_ticks) {
    return METER_ROTATIONS_CONV * (num_ticks / TICKS_PER_ROTATION);
}
