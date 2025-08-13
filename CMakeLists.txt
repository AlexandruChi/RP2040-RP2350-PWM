cmake_minimum_required(VERSION 3.13)
set(LIBRARY_NAME pwmlib)

set(SRC_DIR src)
set(INCLUDE_DIR include)

project(${LIBRARY_NAME} 
    VERSION 0.0.1
    LANGUAGES C CXX ASM
    DESCRIPTION "PWM library for the C SDK on RP2040/RP2350"
)

file(GLOB SRC "${SRC_DIR}/*.c")
add_library(${LIBRARY_NAME} STATIC ${SRC})

target_include_directories(${LIBRARY_NAME} PUBLIC ${INCLUDE_DIR})
target_link_libraries(${LIBRARY_NAME} PUBLIC 
    hardware_pwm
    hardware_clocks
)
