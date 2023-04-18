#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Pin assignments for encoder inputs
#define ENCODER_PIN_A 14
#define ENCODER_PIN_B 15
#define ENCODER_PIN_A_RIGHT 18  // TODO: Change pin (18 is used by motors)
#define ENCODER_PIN_B_RIGHT 19  // TODO: Change pin (19 is used by motors)

// Interrupt handler for encoder input A
void encoder_isr_A(uint gpio, uint32_t events);

// Interrupt handler for encoder input A
void encoder_isr_A_RIGHT(uint gpio, uint32_t events);

/*
Read encoder rotation count from left motor rotary encoder
return: int number of rotations of rotary encoder
*/
int encoder_left();

/*
Read encoder rotation count from right motor rotary encoder
return: int number of rotations of rotary encoder
*/
int encoder_right();

#endif