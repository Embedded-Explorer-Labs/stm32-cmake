# STM32 CMake lesson: add CMSIS and the STM32 HAL

This project accompanies [Add CMSIS and the STM32 HAL to a CMake Project](https://www.embeddedexplorer.com/series/stm32-cmake/stm32-add-cmsis-and-hal/). It uses ST's complete startup, CMSIS, and a minimal set of HAL sources to build an STM32L433 ELF that calls `HAL_Init()`. Earlier versions are available at the `lesson-02`, `lesson-03`, and `lesson-04` tags.

## Prerequisites

- CMake 3.22 or later
- Ninja
- Arm GNU toolchain (`arm-none-eabi-gcc`, `arm-none-eabi-size`, `arm-none-eabi-objdump`, and `arm-none-eabi-nm`)
- STM32CubeL4 firmware package (tested with `STM32Cube_FW_L4_V1.18.2`), separate from STM32CubeCLT

Make sure the tools are available on your `PATH`. STM32CubeCLT includes the build tools, but not the STM32CubeL4 firmware package. You do not need a board for this exercise. Set `STM32CUBE_L4_ROOT` to the directory containing the package's `Drivers/` folder:

```sh
export STM32CUBE_L4_ROOT="$HOME/STM32Cube/Repository/STM32Cube_FW_L4_V1.18.2"
```

## Build and inspect

From this directory, run:

```sh
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/gcc-arm-none-eabi.cmake -DSTM32CUBE_L4_ROOT="$STM32CUBE_L4_ROOT"
cmake --build build
arm-none-eabi-size build/firmware.elf
arm-none-eabi-objdump -h build/firmware.elf
```

If you already configured the project for an earlier lesson, run `cmake -S . -B build -DSTM32CUBE_L4_ROOT="$STM32CUBE_L4_ROOT"` instead of the first command to reuse that build directory. Use a fresh build directory if you change toolchains, because CMake caches its compiler choice.

The ELF should contain ST's full vector table, with code and runtime sections in Flash and `.data` and `.bss` in RAM. You can inspect `build/firmware.map` for the full layout. The educational two-entry `startup_stm32l433.s` remains in the directory for reference but is not compiled.

**Do not flash this ELF yet.** This lesson initializes the HAL but has no GPIO setup or visible output; the next lesson adds a blinking LED.
