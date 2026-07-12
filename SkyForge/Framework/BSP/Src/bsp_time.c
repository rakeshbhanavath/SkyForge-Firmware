/******************************************************************************
 * @file    bsp_time.c
 * @brief   Board Support Package (BSP) implementation for time services.
 *
 * @details
 * This module implements the SkyForge timing abstraction layer.
 * It wraps STM32 HAL timing functions and provides a common interface for
 * delays and system tick retrieval.
 *
 * Architecture:
 *
 *  Application
 *        │
 *        ▼
 * Drivers / Services
 *        │
 *        ▼
 *     BSP_TIME
 *        │
 *        ▼
 *    STM32 HAL
 *        │
 *        ▼
 *   System Timer
 *
 * Why BSP?
 * --------
 * Drivers should never call HAL_Delay() or HAL_GetTick() directly.
 * This allows the timing implementation to change without affecting
 * upper software layers.
 *
 * Future Improvements:
 * --------------------
 * - Microsecond delay support
 * - Hardware timer backend
 * - RTOS integration
 * - High-resolution timestamp
 * - Software timer services
 *
 * Portability Notes:
 * ------------------
 * 1. Different STM32 MCU
 *      Usually no source code changes.
 *
 *      Example:
 *          STM32C031 -> STM32F411
 *
 *      Only CubeMX clock configuration changes.
 *
 * 2. RTOS Migration
 *
 *      Current:
 *          HAL_Delay()
 *          HAL_GetTick()
 *
 *      Future:
 *          vTaskDelay()
 *          xTaskGetTickCount()
 *
 *      Drivers remain unchanged because they call:
 *
 *          BSP_Delay()
 *          BSP_GetTick()
 *
 * 3. Different MCU Vendor
 *
 *      Current:
 *          HAL_Delay()
 *          HAL_GetTick()
 *
 *      Future:
 *          ESP-IDF timer API
 *          MCUXpresso timer API
 *
 *      Only this file changes.
 *
 * @author  Rakesh Bhanavath
 * @project SkyForge
 ******************************************************************************/

/* Includes -----------------------------------------------------------------*/

#include "bsp_time.h"

#include "stm32c0xx_hal.h"

/* Public Functions ---------------------------------------------------------*/

/**
 * @brief Delay program execution.
 *
 * @param milliseconds Delay duration in milliseconds.
 *
 * @note
 * This function performs a blocking delay.
 */
void BSP_Delay(uint32_t milliseconds)
{
    /* Execute blocking delay using the platform timer */
    HAL_Delay(milliseconds);
}

/**
 * @brief Get the current system tick.
 *
 * @return
 * Current system tick in milliseconds.
 *
 * @note
 * The tick value wraps around after reaching the maximum value of uint32_t.
 */
uint32_t BSP_GetTick(void)
{
    /* Return the current system tick */
    return HAL_GetTick();
}
