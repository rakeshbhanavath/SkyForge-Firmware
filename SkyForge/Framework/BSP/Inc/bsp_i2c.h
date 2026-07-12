/******************************************************************************
 * @file    bsp_i2c.h
 * @brief   Board Support Package (BSP) interface for I2C communication.
 *
 * @details
 * This module provides a hardware abstraction layer for I2C communication.
 * All upper software layers (Drivers, Services and Application) must access
 * I2C peripherals only through this interface.
 *
 * Architecture:
 *
 *  Application
 *        │
 *        ▼
 *   Sensor Drivers
 *        │
 *        ▼
 *     BSP_I2C
 *        │
 *        ▼
 *    STM32 HAL
 *        │
 *        ▼
 *     I2C Hardware
 *
 * Why BSP?
 * --------
 * Drivers should never call HAL APIs directly. The BSP isolates hardware-
 * specific implementations from the rest of the framework.
 *
 * Future Improvements:
 * --------------------
 * - DMA support
 * - Interrupt-based transfers
 * - Configurable timeout
 * - Bus recovery mechanism
 * - Multiple I2C peripheral support
 *
 * Portability Notes:
 * ------------------
 * 1. Different STM32 MCU
 *      No API changes required.
 *      Only HAL configuration or peripheral handles may change.
 *
 *      Example:
 *          STM32C031  -> STM32F411
 *          hi2c1      -> hi2c2
 *
 * 2. Different Vendor (ESP32, NXP, TI)
 *      Only bsp_i2c.c changes.
 *
 *      Current:
 *          HAL_I2C_Mem_Read()
 *
 *      Future:
 *          ESP-IDF I2C API
 *          MCUXpresso I2C API
 *
 *      Sensor drivers remain unchanged because they only call:
 *
 *          BSP_I2C_Read()
 *
 * @author  Rakesh Bhanavath
 * @project SkyForge
 ******************************************************************************/

#ifndef BSP_I2C_H
#define BSP_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include "stm32c0xx_hal.h"
#include "common_types.h"

/* Exported Functions -------------------------------------------------------*/

/**
 * @brief Read data from an I2C device register.
 *
 * @param hi2c             Pointer to the I2C peripheral handle.
 * @param deviceAddress    7-bit I2C slave address (left shifted by HAL).
 * @param registerAddress  Register address to read from.
 * @param pData            Pointer to receive buffer.
 * @param length           Number of bytes to read.
 *
 * @return
 *      SF_OK                  Operation successful.
 *      SF_BUSY                Peripheral busy.
 *      SF_TIMEOUT             Communication timeout.
 *      SF_ERROR               General communication failure.
 *
 * @note
 * This function performs a blocking memory read operation.
 */
SF_Status_t BSP_I2C_Read(
        I2C_HandleTypeDef *hi2c,
        uint16_t deviceAddress,
        uint16_t registerAddress,
        uint8_t *pData,
        uint16_t length);

/**
 * @brief Write data to an I2C device register.
 *
 * @param hi2c             Pointer to the I2C peripheral handle.
 * @param deviceAddress    7-bit I2C slave address (left shifted by HAL).
 * @param registerAddress  Register address to write.
 * @param pData            Pointer to transmit buffer.
 * @param length           Number of bytes to write.
 *
 * @return
 *      SF_OK                  Operation successful.
 *      SF_BUSY                Peripheral busy.
 *      SF_TIMEOUT             Communication timeout.
 *      SF_ERROR               General communication failure.
 *
 * @note
 * This function performs a blocking memory write operation.
 */
SF_Status_t BSP_I2C_Write(
        I2C_HandleTypeDef *hi2c,
        uint16_t deviceAddress,
        uint16_t registerAddress,
        uint8_t *pData,
        uint16_t length);

#ifdef __cplusplus
}
#endif

#endif /* BSP_I2C_H */
