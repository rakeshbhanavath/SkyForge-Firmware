/******************************************************************************
 * @file    mpu6050.c
 * @brief   MPU6050 driver implementation.
 *
 * @details
 * This module implements the public API of the MPU6050 driver.
 * Communication with the sensor is performed through the BSP I2C layer.
 *
 * Architecture:
 *
 *      Application
 *            │
 *            ▼
 *      MPU6050 Driver
 *            │
 *            ▼
 *        BSP_I2C
 *            │
 *            ▼
 *      STM32 HAL
 *            │
 *            ▼
 *        MPU6050
 *
 * Development Roadmap:
 * --------------------
 * ✔ Read WHO_AM_I
 * □ Device Initialization
 * □ Read Raw Sensor Data
 * □ Data Conversion
 * □ Calibration
 * □ Self Test
 *
 * Future Improvements:
 * --------------------
 * - FIFO support
 * - Interrupt support
 * - Motion detection
 * - Sleep mode
 * - DMA transfers
 *
 * @author  Rakesh Bhanavath
 * @project SkyForge
 ******************************************************************************/

/* Includes -----------------------------------------------------------------*/

#include "mpu6050.h"

#include "bsp_i2c.h"

#include "common_defs.h"
/* Public Functions ---------------------------------------------------------*/

/**
 * @brief Read the MPU6050 WHO_AM_I register.
 *
 * @param handle    Pointer to the driver handle.
 * @param deviceID  Pointer to receive the device ID.
 *
 * @return
 *      SF_OK
 *      SF_BUSY
 *      SF_TIMEOUT
 *      SF_ERROR
 */
SF_Status_t MPU6050_ReadWhoAmI(
        MPU6050_Handle_t *handle,
        uint8_t *deviceID)
{
    /* Read the WHO_AM_I register from the device */
    return BSP_I2C_Read(
            handle->hi2c,
            handle->deviceAddress,
            MPU6050_REG_WHO_AM_I,
            deviceID,
            1U);
}

/**
 * @brief Initialize the MPU6050.
 *
 * @param handle Pointer to the driver handle.
 *
 * @return
 *      SF_OK
 *      SF_ERROR
 *      SF_BUSY
 *      SF_TIMEOUT
 *
 * @note
 * Currently verifies only device communication.
 * Sensor configuration will be added in the next stage.
 */
SF_Status_t MPU6050_Init(
        MPU6050_Handle_t *handle)
{
    uint8_t deviceID;

    SF_Status_t status;

    /* Verify communication with the sensor */
    status = MPU6050_ReadWhoAmI(
            handle,
            &deviceID);

    if (status != SF_OK)
    {
        return status;
    }

    /* Verify that the connected device is an MPU6050 */
    if (deviceID != MPU6050_DEVICE_ID)
    {
        return SF_ERROR;
    }

    return SF_OK;
}

/**
 * @brief Read raw sensor data.
 *
 * @note
 * Not implemented yet.
 */
SF_Status_t MPU6050_ReadRawData(
        MPU6050_Handle_t *handle,
        MPU6050_RawData_t *rawData)
{
    UNUSED(handle);
    UNUSED(rawData);

    return SF_NOT_SUPPORTED;
}

/**
 * @brief Read converted sensor data.
 *
 * @note
 * Not implemented yet.
 */
SF_Status_t MPU6050_ReadData(
        MPU6050_Handle_t *handle,
        MPU6050_Data_t *sensorData)
{
    UNUSED(handle);
    UNUSED(sensorData);

    return SF_NOT_SUPPORTED;
}
