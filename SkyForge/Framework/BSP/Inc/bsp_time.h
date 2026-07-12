/******************************************************************************
 * @file    bsp_time.h
 * @brief   Board Support Package (BSP) interface for time-related services.
 *
 * @details
 * This module provides a hardware abstraction layer for delays and system
 * tick access. All upper software layers (Drivers, Services and Application)
 * must access timing functions only through this interface.
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
 * Upper software layers should never call HAL_Delay() or HAL_GetTick()
 * directly. This abstraction allows the timing implementation to be replaced
 * without affecting Drivers or Application code.
 *
 * Future Improvements:
 * --------------------
 * - Microsecond delay
 * - Hardware timer support
 * - RTOS integration
 * - High-resolution timestamps
 * - Software timers
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
 * 2. RTOS Integration
 *
 *      Current:
 *          HAL_Delay()
 *          HAL_GetTick()
 *
 *      Future:
 *          vTaskDelay()
 *          xTaskGetTickCount()
 *
 *      Drivers continue using:
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
 *      No changes required in Drivers or Application.
 *
 * @author  Rakesh Bhanavath
 * @project SkyForge
 ******************************************************************************/

#ifndef BSP_TIME_H
#define BSP_TIME_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include <stdint.h>

/* Exported Functions -------------------------------------------------------*/

/**
 * @brief Delay program execution.
 *
 * @param milliseconds Delay duration in milliseconds.
 *
 * @note
 * This function performs a blocking delay.
 */
void BSP_Delay(uint32_t milliseconds);

/**
 * @brief Get the current system tick count.
 *
 * @return
 * Current system tick in milliseconds.
 *
 * @note
 * The tick value wraps around after reaching the maximum value of uint32_t.
 */
uint32_t BSP_GetTick(void);

#ifdef __cplusplus
}
#endif

#endif /* BSP_TIME_H */
