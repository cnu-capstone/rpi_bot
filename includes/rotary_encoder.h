#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "constants.h"

// Pin assignments for encoder inputs
#define ENCODER_PIN_A 10
#define ENCODER_PIN_B 11
#define ENCODER_PIN_A_RIGHT 14  // TODO: Change pin (18 is used by motors)
#define ENCODER_PIN_B_RIGHT 15  // TODO: Change pin (19 is used by motors)

#define METER_ROTATIONS_CONV 27.928814548042  // Circumference of wheels in cm
#define TICKS_PER_ROTATION 1196  // Number of rotary encoder ticks per rotation of wheels

// Interrupt handler for encoder input A
void encoder_isr_A(uint gpio, uint32_t events);

// Interrupt handler for encoder input A
void encoder_isr_A_RIGHT(uint gpio, uint32_t events);

/*
Read encoder tick count from left motor rotary encoder
return: int number of ticks of rotary encoder
*/
int encoder_left();

/*
Read encoder tick count from right motor rotary encoder
return: int number of ticks of rotary encoder
*/
int encoder_right();

/*
Calculates distance traveled in centimeters given number of ticks
return: float distance in centimeters
*/
float ticks_to_cm(int num_ticks);

// struct pair encoder_all();

#endif