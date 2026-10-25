# STM32 CMake lesson

This project accompanies [Blink the LED and Flash the STM32 Board](https://www.embeddedexplorer.com/series/stm32-cmake/stm32-blink-ld4-and-flash-the-board/). It builds firmware for an STM32L433RCT6P Nucleo board that toggles its green LD4 LED on PB13 every 500 ms. Earlier versions are available at the `lesson-02` through `lesson-05` tags.

## Prerequisites

- CMake 3.22 or later
- Ninja
- Arm GNU toolchain (`arm-none-eabi-gcc`)
- STM32CubeL4 firmware package (tested with `STM32Cube_FW_L4_V1.18.2`), separate from STM32CubeCLT
- STM32L433RCT6P Nucleo board, ST-LINK USB cable, and `STM32_Programmer_CLI` for flashing and observing LD4

Make sure the tools are available on your `PATH`. STM32CubeCLT includes the build and programming tools, but not the STM32CubeL4 firmware package. You can build without a board, but need it for the flashing step. Set `STM32CUBE_L4_ROOT` to the directory containing the package's `Drivers/` folder:

```sh
export STM32CUBE_L4_ROOT="$HOME/STM32Cube/Repository/STM32Cube_FW_L4_V1.18.2"
```

## Build

From this directory, run:

```sh
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/gcc-arm-none-eabi.cmake -DSTM32CUBE_L4_ROOT="$STM32CUBE_L4_ROOT"
cmake --build build
```

If you already configured the project for lesson 5, run `cmake -S . -B build` instead of the first command to reuse the cached toolchain, Ninja generator, and firmware package path. Use a fresh build directory if you change toolchains, because CMake caches its compiler choice.

The build produces `build/firmware.elf`. Since lesson 5, the complete startup code has come from STM32CubeL4 instead of the earlier two-entry teaching example.

## Blink LD4 and flash the board

Connect the board through its ST-LINK USB port, then run:

```sh
STM32_Programmer_CLI -c port=SWD -w build/firmware.elf -v -rst
```

LD4 should change state about every 500 ms. Check your board's LED pin before using this example with a different STM32 board.
