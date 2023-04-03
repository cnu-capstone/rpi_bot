cmake_minimum_required(VERSION 3.13)

# Include build functions from Pico SDK
#include(pico-sdk/external/pico_sdk_import.cmake)
# initialize pico-sdk from submodule
# note: this must happen before project()
#include(pico-sdk/pico_sdk_init.cmake)
include(pico_sdk_import.cmake)

set(PICO_BOARD pico_w)
# set(PICO_BOARD pico)

# project(blink C CXX ASM)
# project(input_check C CXX ASM)
# project(parse_input C CXX ASM)
# project(hello_world C CXX ASM)
# project(motor_controller C CXX ASM)
# project(i2c_slave C CXX ASM)
project(usb_comm C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
# add_executable(${PROJECT_NAME}
#         blink/blink.c
#         )

# add_executable(${PROJECT_NAME}
#         input_check/read_input_check.c
#         )

# add_executable(${PROJECT_NAME}
#         parse_input/parse_input.c
#         )

# add_executable(${PROJECT_NAME}
#         hello_world/hello_world.c
#         )

# add_executable(${PROJECT_NAME}
#         motor_controller/motor_controller.c
#         )

# add_executable(${PROJECT_NAME}
#         i2c_slave/i2c_slave.c
#         )

add_executable(${PROJECT_NAME}
        usb_comm/usb_comm.c
        )

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})

# pull in common dependencies
target_link_libraries(${PROJECT_NAME} pico_stdlib)
# target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_i2c)
# target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_gpio hardware_pwm)
