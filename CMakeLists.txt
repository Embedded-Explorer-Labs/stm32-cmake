cmake_minimum_required(VERSION 3.22)

project(stm32-cmake-lesson LANGUAGES C ASM)

add_library(firmware OBJECT main.c startup_stm32l433.s)
set_target_properties(firmware PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
)
target_compile_options(firmware PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall;-Wextra>)
