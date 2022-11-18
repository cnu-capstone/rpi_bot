cmake_minimum_required(VERSION 3.13)

# Include build functions from Pico SDK
#include(pico-sdk/external/pico_sdk_import.cmake)
# initialize pico-sdk from submodule
# note: this must happen before project()
#include(pico-sdk/pico_sdk_init.cmake)
include(pico_sdk_import.cmake)

set(PICO_BOARD pico_w)

# project(blink C CXX ASM)
project(input_check C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
# add_executable(${PROJECT_NAME}
#         blink/blink.c
#         )

add_executable(${PROJECT_NAME}
        input_check/read_input_check.c
        )

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT_NAME})

# pull in common dependencies
target_link_libraries(${PROJECT_NAME} pico_stdlib)
