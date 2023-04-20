cmake_minimum_required(VERSION 3.13)

# Include build functions from Pico SDK
#include(pico-sdk/external/pico_sdk_import.cmake)
# initialize pico-sdk from submodule
# note: this must happen before project()
#include(pico-sdk/pico_sdk_init.cmake)
include(pico_sdk_import.cmake)

# set(PICO_BOARD pico_w)
set(PICO_BOARD pico)

project(motor_controller C CXX ASM)
# project(usb_comm C CXX ASM)
# project(ultrasonic C CXX ASM)
# project(rotary_encoder C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(${PROJECT_NAME}
        motor_controller/motor_controller.c
        ultrasonic/ultrasonic.c
        rotary_encoder/rotary_encoder.c
        )

# add_executable(${PROJECT_NAME}
#         usb_comm/usb_comm.c
#         )

# add_executable(${PROJECT_NAME}
#        ultrasonic_usb_comm/ultrasonic.c
#        )

# add_executable(${PROJECT_NAME}
#         rotary_encoder_usb_comm/rotary_encoder.c
#         )

# Switches UART output to usb
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})

# pull in common dependencies
# target_link_libraries(${PROJECT_NAME} pico_stdlib)
# target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_i2c)
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_gpio hardware_pwm hardware_timer)
