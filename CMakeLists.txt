cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(pico_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(blink)
add_subdirectory(bmp)
add_subdirectory(ultra)
add_subdirectory(terminal)
