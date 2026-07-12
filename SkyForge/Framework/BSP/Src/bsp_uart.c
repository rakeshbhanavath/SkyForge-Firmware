/******************************************************************************
 * @file    bsp_uart.c
 * @brief   Board Support Package (BSP) implementation for UART communication.
 *
 * @details
 * This module implements the SkyForge UART abstraction layer.
 * It wraps STM32 HAL UART APIs and converts HAL-specific return values into
 * SkyForge status codes.
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
 * The BSP isolates vendor-specific HAL APIs from the rest of the project.
 * Upper software layers never call HAL directly.
 *
 * Future Improvements:
 * --------------------
 * - DMA transmission/reception
 * - Interrupt mode
 * - Configurable timeout
 * - Ring buffer support
 * - Multiple UART instances
 *
 * Portability Notes:
 * ------------------
 * 1. Different STM32 MCU
 *      Usually no source code changes.
 *
 *      Example:
 *          STM32C031
 *              USART2
 *
 *          STM32F411
 *              USART1
 *
 *      Only CubeMX configuration and UART handle change.
 *
 * 2. Different MCU Vendor
 *
 *      Current:
 *          HAL_UART_Transmit()
 *          HAL_UART_Receive()
 *
 *      Future:
 *          ESP-IDF UART Driver
 *          MCUXpresso UART Driver
 *
 *      No changes required in Drivers or Application.
 *
 * @author  Rakesh Bhanavath
 * @project SkyForge
 ******************************************************************************/

/* Includes -----------------------------------------------------------------*/

#include "bsp_uart.h"

/* Public Functions ---------------------------------------------------------*/

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
 */
SF_Status_t BSP_UART_Transmit(
        UART_HandleTypeDef *huart,
        const uint8_t *pData,
        uint16_t length)
{
    HAL_StatusTypeDef status;

    /* Execute blocking UART transmission */
    status = HAL_UART_Transmit(
            huart,
            (uint8_t *)pData,
            length,
            HAL_MAX_DELAY);

    /* Convert HAL status to SkyForge status */
    switch (status)
    {
        case HAL_OK:
            return SF_OK;

        case HAL_BUSY:
            return SF_BUSY;

        case HAL_TIMEOUT:
            return SF_TIMEOUT;

        default:
            return SF_ERROR;
    }
}

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
 */
SF_Status_t BSP_UART_Receive(
        UART_HandleTypeDef *huart,
        uint8_t *pData,
        uint16_t length)
{
    HAL_StatusTypeDef status;

    /* Execute blocking UART reception */
    status = HAL_UART_Receive(
            huart,
            pData,
            length,
            HAL_MAX_DELAY);

    /* Convert HAL status to SkyForge status */
    switch (status)
    {
        case HAL_OK:
            return SF_OK;

        case HAL_BUSY:
            return SF_BUSY;

        case HAL_TIMEOUT:
            return SF_TIMEOUT;

        default:
            return SF_ERROR;
    }
}
