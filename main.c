#include "stm32l4xx_hal.h"

void SysTick_Handler(void)
{
    HAL_IncTick();
}

int main(void)
{
    if (HAL_Init() != HAL_OK) {
        while (1) {
        }
    }

    while (1) {
    }
}
