# STM32 CMake lesson: what runs before `main()`

This project accompanies [What Runs Before main() on an STM32?](https://www.embeddedexplorer.com/series/stm32-cmake/stm32-what-runs-before-main/). It compiles C and a small startup routine for the STM32L433's Cortex-M4 processor without linking firmware. The earlier, C-only project is available at the `lesson-02` tag.

## Prerequisites

- CMake 3.22 or later
- Ninja
- Arm GNU toolchain (`arm-none-eabi-gcc` and `arm-none-eabi-nm`)

Make sure these tools are available on your `PATH`. STM32CubeCLT includes them. You do not need a board for this exercise.

## Build and inspect

From this directory, run:

```sh
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/gcc-arm-none-eabi.cmake
cmake --build build
arm-none-eabi-nm build/CMakeFiles/firmware.dir/startup_stm32l433.s.obj
```

If you already configured the project for lesson 2, run `cmake -S . -B build` instead of the first command to reuse that build directory. Use a fresh build directory if you change toolchains, because CMake caches its compiler choice.

The `nm` output should show `Reset_Handler` defined (`T`) and symbols such as `_estack`, `_sidata`, and `main` unresolved (`U`). The linker will resolve them in a later lesson. This project produces **object files, not flashable firmware**: the vector table is incomplete, and there is no linker script yet.
