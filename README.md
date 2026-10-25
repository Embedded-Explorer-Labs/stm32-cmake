# STM32 CMake lesson: cross-compile an object file

This project accompanies [A Minimal Cross-Compiled CMake Project for STM32](https://www.embeddedexplorer.com/series/stm32-cmake/stm32-minimal-cross-compiled-cmake-project/). It compiles `main.c` for the STM32L433's Cortex-M4 processor without linking firmware.

## Prerequisites

- CMake 3.22 or later
- Ninja
- Arm GNU toolchain (`arm-none-eabi-gcc` and `arm-none-eabi-objdump`)

Make sure these tools are available on your `PATH`. STM32CubeCLT includes them. You do not need a board for this exercise.

## Build and inspect

From this directory, run:

```sh
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/gcc-arm-none-eabi.cmake
cmake --build build
arm-none-eabi-objdump -f build/CMakeFiles/firmware.dir/main.c.obj
```

The object file should report `elf32-littlearm` and `architecture: armv7e-m`. It is **not flashable firmware**: this project has no startup code or linker script. Use a fresh build directory if you change toolchains, because CMake caches its compiler choice.
