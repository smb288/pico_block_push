cmake_minimum_required(VERSION 3.20)

include(pico_sdk_import.cmake)

project(block_push)

pico_sdk_init()

add_executable(push push.c)

target_link_libraries(push pico_stdlib 
    hardware_uart 
    hardware_gpio 
    hardware_pwm 
    hardware_timer
    pico_multicore)

pico_enable_stdio_usb(push 1)
pico_enable_stdio_uart(push 0)

pico_add_extra_outputs(push)