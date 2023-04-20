#include "../includes/motor_controller.h"

bool INSTRUCTIONS[bit_width] = {false, false, false};  // Enable, A, B
const uint MOTOR2_ENABLE_PIN = 21;  // Left Motor
const uint MOTOR2_POS_PIN = 20;
const uint MOTOR2_NEG_PIN = 19;

const uint MOTOR1_ENABLE_PIN = 16;  // Right Motor
const uint MOTOR1_POS_PIN = 17;
const uint MOTOR1_NEG_PIN = 18;
// const uint LED_PIN = PICO_DEFAULT_LED_PIN;  // PICO W is pin 22
const uint LED_PIN = 22;  // Uncomment for PICO W usage

uint MOTOR1_SLICE_NUM;
uint MOTOR2_SLICE_NUM;

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
    // gpio_init(MOTOR1_ENABLE_PIN);
    // gpio_set_dir(MOTOR1_ENABLE_PIN, GPIO_OUT);
    gpio_init(MOTOR1_NEG_PIN);
    gpio_set_dir(MOTOR1_NEG_PIN, GPIO_OUT);

    gpio_set_function(MOTOR1_ENABLE_PIN, GPIO_FUNC_PWM);
    MOTOR1_SLICE_NUM = pwm_gpio_to_slice_num(MOTOR1_ENABLE_PIN);
    pwm_set_wrap(MOTOR1_SLICE_NUM, 255);
    // MOTOR2 INIT
    gpio_init(MOTOR2_POS_PIN);
    gpio_set_dir(MOTOR2_POS_PIN, GPIO_OUT);
    // gpio_init(MOTOR2_ENABLE_PIN);
    // gpio_set_dir(MOTOR2_ENABLE_PIN, GPIO_OUT);
    gpio_init(MOTOR2_NEG_PIN);
    gpio_set_dir(MOTOR2_NEG_PIN, GPIO_OUT);

    gpio_set_function(MOTOR2_ENABLE_PIN, GPIO_FUNC_PWM);
    MOTOR2_SLICE_NUM = pwm_gpio_to_slice_num(MOTOR2_ENABLE_PIN);
    pwm_set_wrap(MOTOR2_SLICE_NUM, 255);
    // LED PIN INIT
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void pico_deinit() {
    gpio_put(MOTOR1_POS_PIN, false);
    // gpio_put(MOTOR1_ENABLE_PIN, false);
    pwm_set_enabled(pwm_gpio_to_slice_num(MOTOR1_ENABLE_PIN), false);
    gpio_put(MOTOR1_NEG_PIN, false);
    gpio_put(MOTOR2_POS_PIN, false);
    // gpio_put(MOTOR2_ENABLE_PIN, false);
    pwm_set_enabled(pwm_gpio_to_slice_num(MOTOR2_ENABLE_PIN), false);
    gpio_put(MOTOR2_NEG_PIN, false);
    gpio_put(LED_PIN, false);
    // MOTOR1 DEINIT
    gpio_deinit(MOTOR1_POS_PIN);
    gpio_deinit(MOTOR1_ENABLE_PIN);
    gpio_deinit(MOTOR1_NEG_PIN);
    // MOTOR2 DEINIT
    gpio_deinit(MOTOR2_POS_PIN);
    gpio_deinit(MOTOR2_ENABLE_PIN);
    gpio_deinit(MOTOR1_NEG_PIN);
    // LED PIN DEINIT
    gpio_deinit(LED_PIN);
}

void motor_forward(uint8_t instr_distance) {
    // SET MOTOR DIRECTION FORWARD
    gpio_put(MOTOR1_POS_PIN, true);
    gpio_put(MOTOR1_NEG_PIN, false);
    gpio_put(MOTOR2_POS_PIN, true);
    gpio_put(MOTOR2_NEG_PIN, false);
    // SET MOTOR STATE TO ON
    // Drive until our distance (change duration to distance) has been met.
    // Check for collisions in loop and resume when obstacle is gone.
    // During driving state, check rotary encoder deltas to ensure bot is moving straight
    // Duty Cycle adjustment is % delta from target duty cycle
    /*
    Distance L Motor = # Of cycles * conversion factor
    Distance R Motor = # of cycles * conversion factor
    L Motor % above or below target distance (or average of two distances)
    R Motor % above or below target distance or avg
    Duty Cycle Adjustment = fractional delta from current duty cycle
    */
    // As speed decreases, increase duty cycle

    float distance_traveled = 0;
    int ticks_initial_right = encoder_right();
    // int ticks_initial_left = encoder_left();

    int right_motor_cycles = 96;
    int left_motor_cycles = 86;

    while (distance_traveled < instr_distance) {
        if (!collision_imminent_check(FORWARD, COLL_THRHLD)) {
            // if (right_motor_cycles > 255) {
            //     right_motor_cycles = 255;
            // }
            // if (left_motor_cycles > 255) {
            //     left_motor_cycles = 255;
            // }
            // Drive for some time
            // Set 50% duty cycle
            pwm_set_chan_level(MOTOR1_SLICE_NUM, PWM_CHAN_A, right_motor_cycles);
            pwm_set_chan_level(MOTOR1_SLICE_NUM, PWM_CHAN_B, 256 - right_motor_cycles);

            pwm_set_chan_level(MOTOR2_SLICE_NUM, PWM_CHAN_B, left_motor_cycles);
            pwm_set_chan_level(MOTOR2_SLICE_NUM, PWM_CHAN_A, 256 - left_motor_cycles);

            pwm_set_enabled(MOTOR1_SLICE_NUM, true);
            pwm_set_enabled(MOTOR2_SLICE_NUM, true);

            // gpio_put(MOTOR1_ENABLE_PIN, true);
            // gpio_put(MOTOR2_ENABLE_PIN, true);
            // Check how far we drove
            int ticks_final_right = encoder_right();
            // int ticks_final_left = encoder_left();
            // printf("Tick Initial: %i \tTick Final: %i \nTick Delta: %i \n", ticks_initial, ticks_final, ticks_final - ticks_initial);

            int ticks_delta_right = ticks_final_right - ticks_initial_right;
            // int ticks_delta_left = ticks_final_left - ticks_initial_left;
            
            // int ticks_delta_target = (ticks_delta_right + ticks_delta_left) / 2;    

            // printf("Left: %i\tRight: %i\tAVG: %i\n", ticks_delta_left, ticks_delta_right, ticks_delta_target);        

            float leg_distance_traveled = ticks_to_cm(ticks_final_right - ticks_initial_right);
            
            // printf("Leg of Distance: %f \n", leg_distance_traveled);
            ticks_initial_right = ticks_final_right;  // Setup calculation for next iteration
            // ticks_initial_left = ticks_final_left;
            distance_traveled += leg_distance_traveled / 10;  // Centimeters to Decimeters
        }
        else {
            motor_stall();
        }
        // printf("Distance Traveled: %f \n", distance_traveled);
        sleep_ms(100);
    }     

    // while (!collision_imminent_check(FORWARD, COLL_THRHLD)) {  // Drive until there is a collision detected
    //     gpio_put(MOTOR1_ENABLE_PIN, true);
    //     gpio_put(MOTOR2_ENABLE_PIN, true);
    // }
}

void motor_reverse(uint8_t instr_distance) {  // No rear ultrasonic
    // SET MOTOR DIRECTION BACKWARD
    gpio_put(MOTOR1_POS_PIN, false);
    gpio_put(MOTOR1_NEG_PIN, true);
    gpio_put(MOTOR2_POS_PIN, false);
    gpio_put(MOTOR2_NEG_PIN, true);
    // SET MOTOR STATE TO ON

    float distance_traveled = 0;
    int ticks_initial = encoder_right();

    while (distance_traveled < instr_distance) {
        // Drive for some time
        // Set 50% duty cycle
        pwm_set_chan_level(MOTOR1_SLICE_NUM, PWM_CHAN_A, 80);
        pwm_set_chan_level(MOTOR1_SLICE_NUM, PWM_CHAN_B, 176);

        pwm_set_chan_level(MOTOR2_SLICE_NUM, PWM_CHAN_B, 40);
        pwm_set_chan_level(MOTOR2_SLICE_NUM, PWM_CHAN_A, 226);

        pwm_set_enabled(MOTOR1_SLICE_NUM, true);
        pwm_set_enabled(MOTOR2_SLICE_NUM, true);

        // gpio_put(MOTOR1_ENABLE_PIN, true);
        // gpio_put(MOTOR2_ENABLE_PIN, true);
        // Check how far we drove
        int ticks_final = encoder_right();
        float leg_distance_traveled = ticks_to_cm(abs(ticks_final - ticks_initial))/-1.0;
        ticks_initial = ticks_final;  // Setup calculation for next iteration
        distance_traveled += leg_distance_traveled / 10;  // Centimeters to Decimeters
        sleep_ms(100);
    }   

    gpio_put(MOTOR1_ENABLE_PIN, true);
    gpio_put(MOTOR2_ENABLE_PIN, true);
    sleep_ms(instr_distance * 1000);
}

void motor_right() {  // 0 Degree Turn
    // SET LEFT MOTOR FORWARD and RIGHT MOTOR BACKWARD
    gpio_put(MOTOR2_POS_PIN, true);
    gpio_put(MOTOR2_NEG_PIN, false);
    gpio_put(MOTOR1_POS_PIN, false);
    gpio_put(MOTOR1_NEG_PIN, true);
    // SET MOTOR STATE TO ON
    float distance_traveled = 0;
    int ticks_initial = encoder_left();

    while (distance_traveled < 4.3) {  // Experimental turn value
        // if (!collision_imminent_check(RIGHT, COLL_THRHLD)) {
            // Drive for some time
            // Set 50% duty cycle
            pwm_set_chan_level(MOTOR1_SLICE_NUM, PWM_CHAN_A, 0);
            pwm_set_chan_level(MOTOR1_SLICE_NUM, PWM_CHAN_B, 255);

            pwm_set_chan_level(MOTOR2_SLICE_NUM, PWM_CHAN_B, 255);
            pwm_set_chan_level(MOTOR2_SLICE_NUM, PWM_CHAN_A, 0);

            pwm_set_enabled(MOTOR1_SLICE_NUM, true);
            pwm_set_enabled(MOTOR2_SLICE_NUM, true);

            // gpio_put(MOTOR1_ENABLE_PIN, true);
            // gpio_put(MOTOR2_ENABLE_PIN, true);
            // Check how far we drove
            int ticks_final = encoder_left();
            float leg_distance_traveled = ticks_to_cm(ticks_final - ticks_initial);
            ticks_initial = ticks_final;  // Setup calculation for next iteration
            distance_traveled += leg_distance_traveled / 10;  // Centimeters to Decimeters
        // }
        // else {
        //     motor_stall();
        // }
        // printf("Distance Traveled: %f \n", distance_traveled);
        sleep_ms(100);
    }   
    
    // while (!collision_imminent_check(RIGHT, COLL_THRHLD)) {
    //     gpio_put(MOTOR2_ENABLE_PIN, true);
    //     gpio_put(MOTOR1_ENABLE_PIN, true);
    // }
    // sleep_ms(900);
}

void motor_left() {  // 0 Degree Turn
    // SET RIGHT MOTOR FORWARD and LEFT MOTOR BACKWARD
    gpio_put(MOTOR2_POS_PIN, false);
    gpio_put(MOTOR2_NEG_PIN, true);
    gpio_put(MOTOR1_POS_PIN, true);
    gpio_put(MOTOR1_NEG_PIN, false);
    // SET MOTOR STATE TO ON
    float distance_traveled = 0;
    int ticks_initial = encoder_right();

    while (distance_traveled < 4.3) {  // Experimental turn value
        // if (!collision_imminent_check(LEFT, COLL_THRHLD)) {
        // Drive for some time
        // Set 50% duty cycle
        pwm_set_chan_level(MOTOR1_SLICE_NUM, PWM_CHAN_A, 255);
        pwm_set_chan_level(MOTOR1_SLICE_NUM, PWM_CHAN_B, 0);

        pwm_set_chan_level(MOTOR2_SLICE_NUM, PWM_CHAN_B, 0);
        pwm_set_chan_level(MOTOR2_SLICE_NUM, PWM_CHAN_A, 255);

        pwm_set_enabled(MOTOR1_SLICE_NUM, true);
        pwm_set_enabled(MOTOR2_SLICE_NUM, true);

        // gpio_put(MOTOR1_ENABLE_PIN, true);
        // gpio_put(MOTOR2_ENABLE_PIN, true);
        // Check how far we drove
        int ticks_final = encoder_right();
        float leg_distance_traveled = ticks_to_cm(ticks_final - ticks_initial);
        ticks_initial = ticks_final;  // Setup calculation for next iteration
        distance_traveled += leg_distance_traveled / 10;  // Centimeters to Decimeters
        // }
        // else {
        //     motor_stall();
        // }
        // printf("Distance Traveled: %f \n", distance_traveled);
        // sleep_ms(100);
    } 

    // while (!collision_imminent_check(LEFT, COLL_THRHLD)) {
    //     gpio_put(MOTOR2_ENABLE_PIN, true);
    //     gpio_put(MOTOR1_ENABLE_PIN, true);
    // }
    // sleep_ms(900);
}

void motor_stall() {
    pwm_set_chan_level(MOTOR1_SLICE_NUM, PWM_CHAN_A, 0);
    pwm_set_chan_level(MOTOR1_SLICE_NUM, PWM_CHAN_B, 255);
    pwm_set_chan_level(MOTOR2_SLICE_NUM, PWM_CHAN_B, 0);
    pwm_set_chan_level(MOTOR2_SLICE_NUM, PWM_CHAN_A, 255);

    pwm_set_enabled(MOTOR1_SLICE_NUM, true);
    pwm_set_enabled(MOTOR2_SLICE_NUM, true);
    // gpio_put(MOTOR1_ENABLE_PIN, false);
    // gpio_put(MOTOR2_ENABLE_PIN, false);
    sleep_ms(100);  // Lowering from 1000 to 100
}

// int main() {
//     stdio_init_all();  // INIT COMM
//     pico_init();  // INIT GPIO

//     char cmd[CMD_LEN];

//     while(1) {
//         read_stream(cmd);

//         for (int i = 0; i < bit_width; i ++) {
//             INSTRUCTIONS[i] = cmd[i] == '1';
//         }

//         uint8_t cmd_duration = 1;
//         // Calculate distance
//         for (int i = 3; i < CMD_LEN; i++) {
//             // int cmd_val = 0;
//             if (cmd[i] == '1') {
//                 // cmd_val = 1;
//                 cmd_duration += pow(2, (CMD_LEN - (i+1)));
//             }
//             // cmd_duration += cmd_val * pow(2, (CMD_LEN - (i+1)));
//         }

//         if (INSTRUCTIONS[0] && INSTRUCTIONS[1] && INSTRUCTIONS[2]) {  // 111
//             motor_forward(cmd_duration);
//         }
//         else if (INSTRUCTIONS[0] && !INSTRUCTIONS[1] && INSTRUCTIONS[2]) {  // 101
//             motor_left();
//         }
//         else if (INSTRUCTIONS[0] && INSTRUCTIONS[1] && !INSTRUCTIONS[2]) {  // 110
//             motor_right();
//         }
//         else if (!INSTRUCTIONS[0] && INSTRUCTIONS[1] && INSTRUCTIONS[2]) {  // 011
//             motor_reverse(cmd_duration);
//         }
//         else {
//             motor_stall();
//         }
//         motor_stall();
//     }

//     pico_deinit();
//     return SUCCESS;
// }

int main() {
    stdio_init_all();  // INIT COMM
    pico_init();  // INIT GPIO

    motor_forward(32);
    motor_stall();
    sleep_ms(500);

    motor_forward(6);
    motor_stall();
    sleep_ms(500);

    motor_left();
    motor_stall();
    sleep_ms(500);

    motor_forward(32);
    motor_stall();
    sleep_ms(500);

    motor_forward(17);
    motor_stall();
    sleep_ms(500);

    motor_right();

    motor_right();
    
    motor_stall();

    pico_deinit();
    return SUCCESS;
}

// int main() {
//     stdio_init_all();  // INIT COMM
//     pico_init();  // INIT GPIO

//     sleep_ms(10000);

//     motor_forward(32);

//     pico_deinit();
//     return SUCCESS;
// }
