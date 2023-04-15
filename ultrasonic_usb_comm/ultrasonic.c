#include "../includes/ultrasonic.h"

volatile uint32_t start_time_LEFT = 0;
volatile uint32_t end_time_LEFT = 0;
volatile bool echo_received_LEFT = false;

volatile uint32_t start_time_RIGHT = 0;
volatile uint32_t end_time_RIGHT = 0;
volatile bool echo_received_RIGHT = false;

volatile uint32_t start_time_FORWARD_A = 0;
volatile uint32_t end_time_FORWARD_A = 0;
volatile bool echo_received_FORWARD_A = false;

volatile uint32_t start_time_FORWARD_B = 0;
volatile uint32_t end_time_FORWARD_B = 0;
volatile bool echo_received_FORWARD_B = false;

void echo_isr_LEFT(uint gpio, uint32_t events) {
    if (gpio == ECHO_PIN_LEFT) {
        if (events & GPIO_IRQ_EDGE_FALL) {
            // Falling edge, end of echo pulse
            end_time_LEFT = time_us_32();
            echo_received_LEFT = true;
        } else {
            // Rising edge, start of echo pulse
            start_time_LEFT = time_us_32();
        }
    }
}

void echo_isr_RIGHT(uint gpio, uint32_t events) {
    if (gpio == ECHO_PIN_RIGHT) {
        if (events & GPIO_IRQ_EDGE_FALL) {
            // Falling edge, end of echo pulse
            end_time_RIGHT = time_us_32();
            echo_received_RIGHT = true;
        } else {
            // Rising edge, start of echo pulse
            start_time_RIGHT = time_us_32();
        }
    }
}

void echo_isr_FORWARD_A(uint gpio, uint32_t events) {
    if (gpio == ECHO_PIN_FORWARD_A) {
        if (events & GPIO_IRQ_EDGE_FALL) {
            // Falling edge, end of echo pulse
            end_time_FORWARD_A = time_us_32();
            echo_received_FORWARD_A = true;
        } else {
            // Rising edge, start of echo pulse
            start_time_FORWARD_A = time_us_32();
        }
    }
}

void echo_isr_FORWARD_B(uint gpio, uint32_t events) {
    if (gpio == ECHO_PIN_FORWARD_B) {
        if (events & GPIO_IRQ_EDGE_FALL) {
            // Falling edge, end of echo pulse
            end_time_FORWARD_B = time_us_32();
            echo_received_FORWARD_B = true;
        } else {
            // Rising edge, start of echo pulse
            start_time_FORWARD_B = time_us_32();
        }
    }
}

float ultrasonic_left() {
    printf("ultrasonic_left()");  // Use printf whenever you need std out
    gpio_init(TRIGGER_PIN_LEFT);
    gpio_set_dir(TRIGGER_PIN_LEFT, GPIO_OUT);
    gpio_init(ECHO_PIN_LEFT);
    gpio_set_dir(ECHO_PIN_LEFT, GPIO_IN);

    gpio_put(TRIGGER_PIN_LEFT, 0);  // Make sure trigger pin is low
    gpio_set_irq_enabled_with_callback(ECHO_PIN_LEFT, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &echo_isr_LEFT);

    // Send a 10us pulse to trigger the sensor
    gpio_put(TRIGGER_PIN_LEFT, 1);
    busy_wait_us_32(5);
    gpio_put(TRIGGER_PIN_LEFT, 0);

    // Wait for echo pulse to be received
    //#echo_received_RIGHT;
    // Calculate duration of echo pulse
    uint32_t pulse_duration_LEFT = end_time_LEFT - start_time_LEFT;

    // Calculate distance in centimeters
    float distance_cm_LEFT = pulse_duration_LEFT * 0.0343 / 2;

    printf("Distance left: %.2f cm\n", distance_cm_LEFT);
    return distance_cm_LEFT;
}

float ultrasonic_right() {
    printf("ultrasonic_right()");  // Use printf whenever you need std out
    gpio_init(TRIGGER_PIN_RIGHT);
    gpio_set_dir(TRIGGER_PIN_RIGHT, GPIO_OUT);
    gpio_init(ECHO_PIN_RIGHT);
    gpio_set_dir(ECHO_PIN_RIGHT, GPIO_IN);

    gpio_put(TRIGGER_PIN_RIGHT, 0);  // Make sure trigger pin is low
    gpio_set_irq_enabled_with_callback(ECHO_PIN_RIGHT, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &echo_isr_RIGHT);

    // Send a 10us pulse to trigger the sensor
    gpio_put(TRIGGER_PIN_RIGHT, 1);
    busy_wait_us_32(10);
    gpio_put(TRIGGER_PIN_RIGHT, 0);

    // Wait for echo pulse to be received
    //#echo_received_RIGHT;
    // Calculate duration of echo pulse
    uint32_t pulse_duration_RIGHT = end_time_RIGHT - start_time_RIGHT;

    // Calculate distance in centimeters
    float distance_cm_RIGHT = pulse_duration_RIGHT * 0.0343 / 2;

    printf("Distance right: %.2f cm\n", distance_cm_RIGHT);

    sleep_ms(500);  // Delay for 500ms

    return distance_cm_RIGHT;
}

float ultrasonic_forward_a() {
    printf("ultrasonic_forward_a()");  // Use printf whenever you need std out
    gpio_init(TRIGGER_PIN_FORWARD_A);
    gpio_set_dir(TRIGGER_PIN_FORWARD_A, GPIO_OUT);
    gpio_init(ECHO_PIN_FORWARD_A);
    gpio_set_dir(ECHO_PIN_FORWARD_A, GPIO_IN);

    gpio_put(TRIGGER_PIN_FORWARD_A, 0);  // Make sure trigger pin is low
    gpio_set_irq_enabled_with_callback(ECHO_PIN_FORWARD_A, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &echo_isr_FORWARD_A);

    // Send a 10us pulse to trigger the sensor
    gpio_put(TRIGGER_PIN_FORWARD_A, 1);
    busy_wait_us_32(10);
    gpio_put(TRIGGER_PIN_FORWARD_A, 0);

    // Wait for echo pulse to be received
    //#echo_received_RIGHT;
    // Calculate duration of echo pulse
    uint32_t pulse_duration_FORWARD_A = end_time_FORWARD_A - start_time_FORWARD_A;

    // Calculate distance in centimeters
    float distance_cm_FORWARD_A = pulse_duration_FORWARD_A* 0.0343 / 2;

    printf("Distance forward a: %.2f cm\n", distance_cm_FORWARD_A);

    sleep_ms(500);  // Delay for 500ms

    return distance_cm_FORWARD_A;
}

float ultrasonic_forward_b() {
	printf("ultrasonic_forward_b()");  // Use printf whenever you need std out
    gpio_init(TRIGGER_PIN_FORWARD_B);
    gpio_set_dir(TRIGGER_PIN_FORWARD_B, GPIO_OUT);
    gpio_init(ECHO_PIN_FORWARD_B);
    gpio_set_dir(ECHO_PIN_FORWARD_B, GPIO_IN);

    gpio_put(TRIGGER_PIN_FORWARD_B, 0);  // Make sure trigger pin is low
    gpio_set_irq_enabled_with_callback(ECHO_PIN_FORWARD_B, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &echo_isr_FORWARD_B);

    // Send a 10us pulse to trigger the sensor
    gpio_put(TRIGGER_PIN_FORWARD_B, 1);
    busy_wait_us_32(10);
    gpio_put(TRIGGER_PIN_FORWARD_B, 0);

    // Wait for echo pulse to be received
    //#echo_received_RIGHT;
    // Calculate duration of echo pulse
    uint32_t pulse_duration_FORWARD_B = end_time_FORWARD_B - start_time_FORWARD_B;

    // Calculate distance in centimeters
    float distance_cm_FORWARD_B = pulse_duration_FORWARD_B* 0.0343 / 2;

    printf("Distance forward b: %.2f cm\n", distance_cm_FORWARD_B);

    sleep_ms(500);  // Delay for 500ms
	
    return distance_cm_FORWARD_B;
}
