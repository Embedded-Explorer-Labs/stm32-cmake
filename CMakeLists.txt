cmake_minimum_required(VERSION 3.22)

project(stm32-cmake-lesson LANGUAGES C ASM)

set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/STM32L433xx_FLASH.ld")

add_executable(firmware main.c startup_stm32l433.s)
set_target_properties(firmware PROPERTIES
    SUFFIX ".elf"
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    LINK_DEPENDS "${LINKER_SCRIPT}"
)
target_compile_options(firmware PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall;-Wextra>)
target_link_options(firmware PRIVATE
    -nostdlib
    "-T${LINKER_SCRIPT}"
    "-Wl,-Map=$<TARGET_FILE_DIR:firmware>/firmware.map"
    -Wl,--gc-sections
)
