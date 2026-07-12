/******************************************************************************
 * @file    mpu6050_defs.h
 * @brief   MPU6050 driver constant definitions.
 *
 * @details
 * This file contains all constant values used by the MPU6050 driver.
 * It includes device identification values, I2C address, communication
 * timeout, and sensor conversion constants.
 *
 * Responsibilities:
 * -----------------
 * ✔ Device constants
 * ✔ Sensor conversion constants
 * ✔ Driver default configuration
 *
 * This file MUST NOT contain:
 * ---------------------------
 * ✘ Register addresses
 * ✘ Function implementations
 * ✘ Data structures
 *
 * Architecture:
 *
 *                  MPU6050 Driver
 *                        │
 *                        ▼
 *                 Driver Constants
 *
 * Why Separate Constants?
 * -----------------------
 * Constants change independently of driver logic.
 * For example:
 *
 *      MPU6050
 *      MPU6500
 *      MPU9250
 *
 * may have different sensitivity values or device IDs while sharing
 * similar driver implementation.
 *
 * Future Improvements:
 * --------------------
 * - Digital Low Pass Filter constants
 * - Clock source definitions
 * - FIFO configuration values
 * - Interrupt configuration values
 * - Motion detection thresholds
 *
 * Portability Notes:
 * ------------------
 *
 * Example 1:
 *
 *      AD0 = LOW
 *          Address = 0x68
 *
 *      AD0 = HIGH
 *          Address = 0x69
 *
 *      Only MPU6050_I2C_ADDRESS changes.
 *
 * Example 2:
 *
 *      MPU6050
 *          Device ID = 0x68
 *
 *      Future IMU
 *          Device ID = Different
 *
 *      Driver implementation remains unchanged.
 *
 * Datasheet:
 * ----------
 * MPU-6000 / MPU-6050 Register Map and Product Specification
 *
 * @author  Rakesh Bhanavath
 * @project SkyForge
 ******************************************************************************/

#ifndef MPU6050_DEFS_H
#define MPU6050_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================================
 * Device Address
 *============================================================================*/

/******************************************************************************
 * MPU6050 I2C Address
 *
 * Datasheet Address (7-bit):
 *
 *      AD0 = LOW
 *          0x68
 *
 *      AD0 = HIGH
 *          0x69
 *
 * STM32 HAL expects the 7-bit address shifted left by one bit.
 *
 * Formula:
 *
 *      HAL Address = Datasheet Address << 1
 *
 * Example:
 *
 *      Datasheet Address = 0x68
 *
 *      HAL Address
 *          = 0x68 << 1
 *          = 0xD0
 *
 * Future Portability:
 *
 *      STM32 HAL
 *          Uses shifted address
 *
 *      Some SDKs (ESP-IDF, Zephyr)
 *          Use unshifted address
 *
 * Only this macro should be modified.
 ******************************************************************************/
#define MPU6050_I2C_ADDRESS             (0x68U << 1)

/*=============================================================================
 * Device Identification
 *============================================================================*/

/******************************************************************************
 * WHO_AM_I Register Expected Value
 *
 * Register:
 *      WHO_AM_I (0x75)
 *
 * Expected Value:
 *      0x68
 *
 * Usage:
 *
 *      During initialization the driver verifies
 *      the connected device before continuing.
 ******************************************************************************/
#define MPU6050_DEVICE_ID               0x68U

/*=============================================================================
 * Driver Configuration
 *============================================================================*/

/******************************************************************************
 * Default Communication Timeout
 *
 * Unit:
 *      Milliseconds
 *
 * Future:
 *      This will later replace HAL_MAX_DELAY
 *      allowing configurable driver timeout.
 ******************************************************************************/
#define MPU6050_DEFAULT_TIMEOUT         100U

/*=============================================================================
 * Accelerometer Sensitivity
 *============================================================================*/

/******************************************************************************
 * Accelerometer Sensitivity
 *
 * Unit:
 *      LSB/g
 *
 * Formula:
 *
 *      Acceleration(g)
 *          =
 *      Raw Accelerometer Value
 *          /
 *      Sensitivity
 *
 * Example:
 *
 *      Raw Value
 *          = 8192
 *
 *      Sensitivity
 *          = 16384 LSB/g
 *
 *      Acceleration
 *          = 8192 / 16384
 *          = 0.5 g
 *
 * Datasheet:
 *      ACCEL_CONFIG Register
 ******************************************************************************/

#define MPU6050_ACCEL_SENS_2G           16384.0f
#define MPU6050_ACCEL_SENS_4G            8192.0f
#define MPU6050_ACCEL_SENS_8G            4096.0f
#define MPU6050_ACCEL_SENS_16G           2048.0f

/*=============================================================================
 * Gyroscope Sensitivity
 *============================================================================*/

/******************************************************************************
 * Gyroscope Sensitivity
 *
 * Unit:
 *      LSB/(°/s)
 *
 * Formula:
 *
 *      Angular Velocity (°/s)
 *          =
 *      Raw Gyroscope Value
 *          /
 *      Sensitivity
 *
 * Example:
 *
 *      Raw Value
 *          = 131
 *
 *      Angular Velocity
 *          = 131 / 131
 *          = 1 °/s
 *
 * Datasheet:
 *      GYRO_CONFIG Register
 ******************************************************************************/

#define MPU6050_GYRO_SENS_250DPS         131.0f
#define MPU6050_GYRO_SENS_500DPS          65.5f
#define MPU6050_GYRO_SENS_1000DPS         32.8f
#define MPU6050_GYRO_SENS_2000DPS         16.4f

/*=============================================================================
 * Temperature Conversion
 *============================================================================*/

/******************************************************************************
 * Internal Temperature Sensor
 *
 * Formula:
 *
 *      Temperature (°C)
 *          =
 *      (Raw Temperature / 340)
 *          +
 *      36.53
 *
 * Example:
 *
 *      Raw Temperature
 *          = 340
 *
 *      Temperature
 *          = (340 / 340)
 *          + 36.53
 *
 *          = 37.53 °C
 *
 * Datasheet:
 *      Temperature Sensor Specification
 ******************************************************************************/

#define MPU6050_TEMP_SENSITIVITY        340.0f
#define MPU6050_TEMP_OFFSET              36.53f

#ifdef __cplusplus
}
#endif

#endif /* MPU6050_DEFS_H */
