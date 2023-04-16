#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#include "constants.h"

#define TRIGGER_PIN_LEFT 2  // GPIO pin number for trigger
#define ECHO_PIN_LEFT 3   // GPIO pin number for echo

#define TRIGGER_PIN_RIGHT 0  // GPIO pin number for trigger
#define ECHO_PIN_RIGHT 1    // GPIO pin number for echo

#define TRIGGER_PIN_FORWARD_A 4  // GPIO pin number for trigger
#define ECHO_PIN_FORWARD_A 5   // GPIO pin number for echo
#define TRIGGER_PIN_FORWARD_B 6  // GPIO pin number for trigger
#define ECHO_PIN_FORWARD_B 7   // GPIO pin number for echo

void echo_isr_LEFT(uint gpio, uint32_t events);

void echo_isr_RIGHT(uint gpio, uint32_t events);

void echo_isr_FORWARD_A(uint gpio, uint32_t events);

void echo_isr_FORWARD_B(uint gpio, uint32_t events);

/*
Read Left Ultrasonic Sensor and calculate distance in centimeters (cm).
return: distance in cm of closest impedance.
*/
float ultrasonic_left();

/*
Read Right Ultrasonic Sensor and calculate distance in centimeters (cm).
return: distance in cm of closest impedance.
*/
float ultrasonic_right();

/*
Read Left Forward Ultrasonic Sensor and calculate distance in centimeters (cm).
return: distance in cm of closest impedance.
*/
float ultrasonic_forward_a();

/*
Read Right Forward Ultrasonic Sensor and calculate distance in centimeters (cm).
return: distance in cm of closest impedance.
*/
float ultrasonic_forward_b();

bool collision_imminent_check(enum DIR dir, float threshold);

#endif
