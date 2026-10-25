cmake_minimum_required(VERSION 3.22)

project(stm32-cmake-lesson LANGUAGES C)

add_library(firmware OBJECT main.c)
set_target_properties(firmware PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
)
target_compile_options(firmware PRIVATE -Wall -Wextra)
