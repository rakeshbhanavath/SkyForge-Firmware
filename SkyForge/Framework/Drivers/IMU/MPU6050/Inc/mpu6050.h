/******************************************************************************
 * @file    mpu6050.h
 * @brief   Public interface for the MPU6050 driver.
 *
 * @details
 * This file exposes the public API of the MPU6050 driver.
 * Applications and higher software layers interact with the sensor only
 * through these functions.
 *
 * Responsibilities:
 * -----------------
 * ✔ Driver initialization
 * ✔ Device identification
 * ✔ Sensor data acquisition
 *
 * This file MUST NOT contain:
 * ---------------------------
 * ✘ Register definitions
 * ✘ Driver constants
 * ✘ Function implementations
 *
 * Architecture:
 *
 *        Application
 *              │
 *              ▼
 *         MPU6050 API
 *              │
 *              ▼
 *        Driver Implementation
 *              │
 *              ▼
 *            BSP I2C
 *
 * Why Separate the API?
 * ---------------------
 * The application should know WHAT the driver can do,
 * not HOW it does it.
 *
 * Future Improvements:
 * --------------------
 * - Calibration API
 * - Self-test API
 * - Interrupt configuration
 * - FIFO interface
 * - Motion detection
 *
 * Portability Notes:
 * ------------------
 * If another IMU replaces the MPU6050,
 * only the driver implementation changes.
 * The application can continue using a similar interface.
 *
 * @author  Rakesh Bhanavath
 * @project SkyForge
 ******************************************************************************/

#ifndef MPU6050_H
#define MPU6050_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include "common_types.h"

#include "mpu6050_defs.h"
#include "mpu6050_types.h"
#include "mpu6050_reg.h"

/* Exported Functions -------------------------------------------------------*/

/**
 * @brief Initialize the MPU6050 driver.
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
 * This function verifies communication with the sensor and prepares
 * it for operation.
 */
SF_Status_t MPU6050_Init(
        MPU6050_Handle_t *handle);

/**
 * @brief Read the device identification register.
 *
 * @param handle Pointer to the driver handle.
 * @param deviceID Pointer to the destination variable.
 *
 * @return
 *      SF_OK
 *      SF_ERROR
 *      SF_BUSY
 *      SF_TIMEOUT
 */
SF_Status_t MPU6050_ReadWhoAmI(
        MPU6050_Handle_t *handle,
        uint8_t *deviceID);

/**
 * @brief Read raw sensor data.
 *
 * @param handle Pointer to the driver handle.
 * @param rawData Pointer to the destination structure.
 *
 * @return
 *      SF_OK
 *      SF_ERROR
 *      SF_BUSY
 *      SF_TIMEOUT
 */
SF_Status_t MPU6050_ReadRawData(
        MPU6050_Handle_t *handle,
        MPU6050_RawData_t *rawData);

/**
 * @brief Read converted sensor data.
 *
 * @param handle Pointer to the driver handle.
 * @param sensorData Pointer to the destination structure.
 *
 * @return
 *      SF_OK
 *      SF_ERROR
 *      SF_BUSY
 *      SF_TIMEOUT
 *
 * @note
 * Values are returned in engineering units.
 */
SF_Status_t MPU6050_ReadData(
        MPU6050_Handle_t *handle,
        MPU6050_Data_t *sensorData);

#ifdef __cplusplus
}
#endif

#endif /* MPU6050_H */
