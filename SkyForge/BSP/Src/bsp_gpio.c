/******************************************************************************
 * @file    bsp_gpio.c
 * @brief   GPIO Board Support Package
 ******************************************************************************/

#include "bsp_gpio.h"

/*==============================================================================
 * Public Functions
 *============================================================================*/

/**
 * @brief Write a logic level to a GPIO pin.
 */
void BSP_GPIO_WritePin(GPIO_TypeDef *GPIOx,
                       uint16_t GPIO_Pin,
                       GPIO_PinState PinState)
{
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState);
}

/**
 * @brief Read the logic level of a GPIO pin.
 */
GPIO_PinState BSP_GPIO_ReadPin(GPIO_TypeDef *GPIOx,
                               uint16_t GPIO_Pin)
{
    return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

/**
 * @brief Toggle the state of a GPIO output pin.
 */
void BSP_GPIO_TogglePin(GPIO_TypeDef *GPIOx,
                        uint16_t GPIO_Pin)
{
    HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
}
