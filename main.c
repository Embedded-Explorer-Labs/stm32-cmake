#include "stm32l4xx_hal.h"

void SysTick_Handler(void)
{
    HAL_IncTick();
}

int main(void)
{
    GPIO_InitTypeDef gpio = {0};

    if (HAL_Init() != HAL_OK) {
        while (1) {
        }
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
    gpio.Pin = GPIO_PIN_13;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &gpio);

    while (1) {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
        HAL_Delay(500);
    }
}
