# STM32 CMake lesson: link firmware into Flash and RAM

This project accompanies [Link STM32 Firmware into Flash and RAM](https://www.embeddedexplorer.com/series/stm32-cmake/stm32-link-firmware-into-flash-and-ram/). It links the C and startup assembly from lesson 3 into an ELF using a memory layout for the STM32L433RCT6P. Earlier versions are available at the `lesson-02` and `lesson-03` tags.

## Prerequisites

- CMake 3.22 or later
- Ninja
- Arm GNU toolchain (`arm-none-eabi-gcc`, `arm-none-eabi-size`, `arm-none-eabi-objdump`, and `arm-none-eabi-nm`)

Make sure these tools are available on your `PATH`. STM32CubeCLT includes them. You do not need a board for this exercise.

## Build and inspect

From this directory, run:

```sh
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/gcc-arm-none-eabi.cmake
cmake --build build
arm-none-eabi-size build/firmware.elf
arm-none-eabi-objdump -h build/firmware.elf
arm-none-eabi-nm -n build/firmware.elf
```

If you already configured the project for an earlier lesson, run `cmake -S . -B build` instead of the first command to reuse that build directory. Use a fresh build directory if you change toolchains, because CMake caches its compiler choice.

The ELF should place the vector table and code in Flash, initialized `.data` in RAM with its initial bytes in Flash, and `.bss` in RAM. `nm` should show addresses for `_estack`, `_sidata`, and the other symbols that were unresolved in lesson 3. You can inspect `build/firmware.map` for the full layout.

**Do not flash this ELF.** Its vector table has only two entries; this is a linking exercise, not a usable firmware image.
