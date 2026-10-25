cmake_minimum_required(VERSION 3.22)

project(stm32-cmake-lesson LANGUAGES C ASM)

set(STM32CUBE_L4_ROOT "" CACHE PATH "STM32CubeL4 firmware package directory")
set(CMSIS "${STM32CUBE_L4_ROOT}/Drivers/CMSIS")
set(DEVICE "${CMSIS}/Device/ST/STM32L4xx")
set(DRIVERS "${STM32CUBE_L4_ROOT}/Drivers/STM32L4xx_HAL_Driver")
set(STARTUP "${DEVICE}/Source/Templates/gcc/startup_stm32l433xx.s")
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/STM32L433xx_FLASH.ld")

if(NOT EXISTS "${STARTUP}")
    message(FATAL_ERROR "Set STM32CUBE_L4_ROOT to the extracted STM32CubeL4 package")
endif()

add_library(stm32_hal OBJECT
    "${DEVICE}/Source/Templates/system_stm32l4xx.c"
    "${DRIVERS}/Src/stm32l4xx_hal.c"
    "${DRIVERS}/Src/stm32l4xx_hal_cortex.c"
    "${DRIVERS}/Src/stm32l4xx_hal_gpio.c"
)
target_include_directories(stm32_hal PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${DRIVERS}/Inc"
    "${DEVICE}/Include"
    "${CMSIS}/Include"
)
target_compile_definitions(stm32_hal PUBLIC STM32L433xx USE_HAL_DRIVER)

add_executable(firmware main.c "${STARTUP}")
target_link_libraries(firmware PRIVATE stm32_hal)
set_target_properties(firmware PROPERTIES
    SUFFIX ".elf"
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    LINK_DEPENDS "${LINKER_SCRIPT}"
)
target_compile_options(firmware PRIVATE $<$<COMPILE_LANGUAGE:C>:-Wall;-Wextra>)
target_link_options(firmware PRIVATE
    "-T${LINKER_SCRIPT}"
    --specs=nano.specs
    --specs=nosys.specs
    "-Wl,-Map=$<TARGET_FILE_DIR:firmware>/firmware.map"
    -Wl,--gc-sections
)
