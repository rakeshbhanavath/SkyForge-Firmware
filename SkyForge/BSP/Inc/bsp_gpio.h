/******************************************************************************
 * @file    bsp_gpio.h
 * @brief   GPIO Board Support Package
 *
 * @details
 * This module provides common GPIO services used throughout the SkyForge
 * firmware. GPIO initialization is performed by STM32CubeMX through
 * MX_GPIO_Init(). This BSP only provides common GPIO operations.
 *
 ******************************************************************************/

#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/*==============================================================================
 * Includes
 *============================================================================*/

#include "main.h"

/*==============================================================================
 * Public Function Prototypes
 *============================================================================*/

/**
 * @brief Write a logic level to a GPIO pin.
 *
 * @param[in] GPIOx      GPIO peripheral (GPIOA, GPIOB, ...)
 * @param[in] GPIO_Pin   GPIO pin (GPIO_PIN_x)
 * @param[in] PinState   GPIO_PIN_SET or GPIO_PIN_RESET
 */
void BSP_GPIO_WritePin(GPIO_TypeDef *GPIOx,
                       uint16_t GPIO_Pin,
                       GPIO_PinState PinState);

/**
 * @brief Read the logic level of a GPIO pin.
 *
 * @param[in] GPIOx      GPIO peripheral (GPIOA, GPIOB, ...)
 * @param[in] GPIO_Pin   GPIO pin (GPIO_PIN_x)
 *
 * @retval GPIO_PinState
 */
GPIO_PinState BSP_GPIO_ReadPin(GPIO_TypeDef *GPIOx,
                               uint16_t GPIO_Pin);

/**
 * @brief Toggle the state of a GPIO output pin.
 *
 * @param[in] GPIOx      GPIO peripheral (GPIOA, GPIOB, ...)
 * @param[in] GPIO_Pin   GPIO pin (GPIO_PIN_x)
 */
void BSP_GPIO_TogglePin(GPIO_TypeDef *GPIOx,
                        uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif /* BSP_GPIO_H */
