#include "../includes/rotary_encoder.h"

// Global variable to store encoder count
volatile int32_t encoder_count = 0;
volatile int32_t encoder_count_RIGHT = 0;

// Interrupt handler for encoder input A
void encoder_isr_A(uint gpio, uint32_t events) {
   if (gpio == ENCODER_PIN_A) {
        if (gpio_get(ENCODER_PIN_A)) {  // Check if input A is high
            if (gpio_get(ENCODER_PIN_B)) {
                encoder_count--;  // Clockwise rotation
            } else {
                encoder_count++;  // Counter-clockwise rotation
            }
        } else {  // Input A is low
            if (gpio_get(ENCODER_PIN_B)) {
                encoder_count++;  // Counter-clockwise rotation
            } else {
                encoder_count--;  // Clockwise rotation
            }
        }
    }
}

// Interrupt handler for encoder input A
void encoder_isr_A_RIGHT(uint gpio, uint32_t events) {
    if (gpio == ENCODER_PIN_A_RIGHT) {
        if (gpio_get(ENCODER_PIN_A_RIGHT)) {  // Check if input A is high
            if (gpio_get(ENCODER_PIN_B_RIGHT)) {
                encoder_count_RIGHT--;  // Clockwise rotation
            } else {
                encoder_count_RIGHT++;  // Counter-clockwise rotation
            }
        } else {  // Input A is low
            if (gpio_get(ENCODER_PIN_B_RIGHT)) {
                encoder_count_RIGHT++;  // Counter-clockwise rotation
            } else {
                encoder_count_RIGHT--;  // Clockwise rotation
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

    printf("Left Encoder Count: %i \n", encoder_count);

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
    
    printf("Right Encoder Count: %i \n", encoder_count_RIGHT);

    return encoder_count_RIGHT;
}

float ticks_to_cm(int num_ticks) {
    return 27.928814548042 * (num_ticks / 1196.0);
}

//int main() {
    //stdio_init_all();  // INIT COMM
    
    //printf("Starting...\n");
    
    //sleep_ms(1000);
    
    //int encoder_initial = encoder_right();
    //int encoder_final = 0;
    
    //float distance_traveled = 0.0;
    
    //while (distance_traveled < 1000) {
        //sleep_ms(100);
        //encoder_final = encoder_right();
        //distance_traveled += ticks_to_cm(encoder_final - encoder_initial);
        //encoder_initial = encoder_final;
        //printf("Distance: %f \n", distance_traveled);
    //} 
     
    //return SUCCESS;
//}
