#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <stdio.h>  // COMM STUFF
#include <math.h>  // For POW function
#include <stdlib.h>  // For ABS function
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "ultrasonic.h"
#include "rotary_encoder.h"
#include "constants.h"

// Ultrasonic Sensor Threshold
// Values less than 35 cm are considered possible collisions
#define COLL_THRHLD 50

#define bit_width 3
#define CMD_LEN 8

// COMM PORT CODE
void read_stream(char* buff);

void enqueue(char* data, char* buff);

// MOTOR CODE
void pico_init();

void pico_deinit();

void motor_forward(uint8_t duration);

void motor_reverse(uint8_t duration);

void motor_right();  // Experimentally determined 90 degree turn

void motor_left();  // Experimentally determined 90 degree turn

void motor_stall();

#endif
