/******************************************************************************
 * @file    bsp_uart.h
 * @brief   Board Support Package (BSP) interface for UART communication.
 *
 * @details
 * This module provides a hardware abstraction layer for UART communication.
 * All upper software layers (Drivers, Services and Application) must access
 * UART peripherals only through this interface.
 *
 * Architecture:
 *
 *  Application
 *        │
 *        ▼
 * Drivers / Logger / CLI
 *        │
 *        ▼
 *     BSP_UART
 *        │
 *        ▼
 *    STM32 HAL
 *        │
 *        ▼
 *    UART Hardware
 *
 * Why BSP?
 * --------
 * Upper software layers must never call STM32 HAL UART APIs directly.
 * This abstraction allows the project to migrate to another STM32 family
 * or even another MCU vendor with minimal changes.
 *
 * Future Improvements:
 * --------------------
 * - Interrupt mode
 * - DMA support
 * - Configurable timeout
 * - Ring buffer
 * - Multiple UART instances
 *
 * Portability Notes:
 * ------------------
 * 1. Different STM32 MCU
 *      Usually only UART peripheral or GPIO configuration changes.
 *
 *      Example:
 *          STM32C031
 *              USART2 (PA2/PA3)
 *
 *          STM32F411
 *              USART1 (PA9/PA10)
 *
 *      No changes required in Drivers or Application.
 *
 * 2. Different Vendor (ESP32, NXP, TI)
 *      Only bsp_uart.c changes.
 *
 *      Current:
 *          HAL_UART_Transmit()
 *          HAL_UART_Receive()
 *
 *      Future:
 *          ESP-IDF UART API
 *          MCUXpresso UART API
 *
 *      Upper layers continue using:
 *
 *          BSP_UART_Transmit()
 *          BSP_UART_Receive()
 *
 * @author  Rakesh Bhanavath
 * @project SkyForge
 ******************************************************************************/

#ifndef BSP_UART_H
#define BSP_UART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include "stm32c0xx_hal.h"
#include "common_types.h"

/* Exported Functions -------------------------------------------------------*/

/**
 * @brief Transmit data over UART.
 *
 * @param huart   Pointer to the UART peripheral handle.
 * @param pData   Pointer to the transmit buffer.
 * @param length  Number of bytes to transmit.
 *
 * @return
 *      SF_OK
 *      SF_BUSY
 *      SF_TIMEOUT
 *      SF_ERROR
 *
 * @note
 * Performs a blocking UART transmission.
 */
SF_Status_t BSP_UART_Transmit(
        UART_HandleTypeDef *huart,
        const uint8_t *pData,
        uint16_t length);

/**
 * @brief Receive data over UART.
 *
 * @param huart   Pointer to the UART peripheral handle.
 * @param pData   Pointer to the receive buffer.
 * @param length  Number of bytes to receive.
 *
 * @return
 *      SF_OK
 *      SF_BUSY
 *      SF_TIMEOUT
 *      SF_ERROR
 *
 * @note
 * Performs a blocking UART reception.
 */
SF_Status_t BSP_UART_Receive(
        UART_HandleTypeDef *huart,
        uint8_t *pData,
        uint16_t length);

#ifdef __cplusplus
}
#endif

#endif /* BSP_UART_H */
