/******************************************************************************
 * @file    bsp_i2c.c
 * @brief   Board Support Package (BSP) implementation for I2C communication.
 *
 * @details
 * This module provides the implementation of the SkyForge I2C abstraction.
 * It wraps STM32 HAL I2C APIs and converts HAL-specific return values into
 * SkyForge status codes.
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
 * Future Improvements:
 * --------------------
 * - DMA support
 * - Interrupt mode
 * - Configurable timeout
 * - Retry mechanism
 * - Bus recovery
 *
 * Portability Notes:
 * ------------------
 * STM32C0 -> STM32F4
 *      Usually no source changes.
 *
 * STM32 -> ESP32
 *      Replace HAL_I2C_Mem_Read()
 *      Replace HAL_I2C_Mem_Write()
 *
 *      Drivers remain unchanged because they call BSP_I2C_*().
 *
 * @author  Rakesh Bhanavath
 * @project SkyForge
 ******************************************************************************/

/* Includes -----------------------------------------------------------------*/

#include "bsp_i2c.h"

/* Public Functions ----------------------------------------------------------*/

/**
 * @brief Read data from an I2C device register.
 */
SF_Status_t BSP_I2C_Read(
        I2C_HandleTypeDef *hi2c,
        uint16_t deviceAddress,
        uint16_t registerAddress,
        uint8_t *pData,
        uint16_t length)
{
    HAL_StatusTypeDef status;

    /* Execute blocking I2C memory read transaction */
    status = HAL_I2C_Mem_Read(
            hi2c,
            deviceAddress,
            registerAddress,
            I2C_MEMADD_SIZE_8BIT,
            pData,
            length,
            HAL_MAX_DELAY);

    /* Convert HAL status into SkyForge status */
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
 * @brief Write data to an I2C device register.
 */
SF_Status_t BSP_I2C_Write(
        I2C_HandleTypeDef *hi2c,
        uint16_t deviceAddress,
        uint16_t registerAddress,
        uint8_t *pData,
        uint16_t length)
{
    HAL_StatusTypeDef status;

    /* Execute blocking I2C memory write transaction */
    status = HAL_I2C_Mem_Write(
            hi2c,
            deviceAddress,
            registerAddress,
            I2C_MEMADD_SIZE_8BIT,
            pData,
            length,
            HAL_MAX_DELAY);

    /* Convert HAL status into SkyForge status */
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
