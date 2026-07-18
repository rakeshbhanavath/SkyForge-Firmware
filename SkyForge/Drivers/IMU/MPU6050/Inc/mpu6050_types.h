/******************************************************************************
 * @file    mpu6050_types.h
 * @brief   MPU6050 driver data type definitions.
 *
 * @details
 * This file defines all data structures used by the MPU6050 driver.
 * It contains sensor data containers, configuration structures and
 * driver handle definitions.
 *
 * Responsibilities:
 * -----------------
 * ✔ Driver handle
 * ✔ Sensor data structures
 * ✔ Driver configuration structures
 *
 * This file MUST NOT contain:
 * ---------------------------
 * ✘ Register definitions
 * ✘ Driver constants
 * ✘ Function implementations
 *
 * Architecture:
 *
 *                MPU6050 Driver
 *                       │
 *                       ▼
 *                Driver Data Types
 *
 * Why Separate Types?
 * -------------------
 * Separating data structures from implementation improves readability
 * and allows applications to use the driver without exposing internal
 * implementation details.
 *
 * Future Improvements:
 * --------------------
 * - Calibration structures
 * - Self-test results
 * - FIFO packet structures
 * - Interrupt status structures
 *
 * Portability Notes:
 * ------------------
 * If another IMU is introduced (ICM42688, BMI270, etc.), only the driver
 * implementation changes. The application can continue using similar
 * vector structures.
 *
 * @author  Rakesh Bhanavath
 * @project SkyForge
 ******************************************************************************/

#ifndef MPU6050_TYPES_H
#define MPU6050_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/

#include "stm32c0xx_hal.h"

/* Exported Types -----------------------------------------------------------*/

/******************************************************************************
 * @brief Three-axis vector.
 *
 * @details
 * Represents any three-dimensional sensor quantity.
 *
 * Units:
 *      Depends on usage.
 *
 * Examples:
 *      Acceleration (g)
 *      Angular Velocity (°/s)
 *      Magnetic Field (µT)
 ******************************************************************************/
typedef struct
{
    float x;

    float y;

    float z;

} MPU6050_Vector3f_t;

/******************************************************************************
 * @brief Raw accelerometer and gyroscope values.
 *
 * @details
 * These values are read directly from the sensor registers before
 * conversion into engineering units.
 *
 * Formula:
 *
 *      Engineering Value
 *          =
 *      Raw Value
 *          /
 *      Sensitivity
 ******************************************************************************/
typedef struct
{
    int16_t accelX;

    int16_t accelY;

    int16_t accelZ;

    int16_t gyroX;

    int16_t gyroY;

    int16_t gyroZ;

    int16_t temperature;

} MPU6050_RawData_t;

/******************************************************************************
 * @brief Converted sensor values.
 *
 * @details
 * Contains values converted into engineering units.
 *
 * Units:
 *      Acceleration : g
 *      Gyroscope    : °/s
 *      Temperature  : °C
 ******************************************************************************/
typedef struct
{
    MPU6050_Vector3f_t acceleration;

    MPU6050_Vector3f_t gyroscope;

    float temperature;

} MPU6050_Data_t;

/******************************************************************************
 * @brief Driver configuration.
 *
 * Future versions will allow configuration of:
 *
 *      Accelerometer Range
 *      Gyroscope Range
 *      Digital Low Pass Filter
 *      Sample Rate
 ******************************************************************************/
typedef struct
{

} MPU6050_Config_t;

/******************************************************************************
 * @brief MPU6050 driver handle.
 *
 * @details
 * Contains all information required by the driver.
 *
 * Future additions:
 *      Driver state
 *      Configuration
 *      Calibration
 ******************************************************************************/
typedef struct
{
    I2C_HandleTypeDef *hi2c;

    uint16_t deviceAddress;

} MPU6050_Handle_t;

#ifdef __cplusplus
}
#endif

#endif /* MPU6050_TYPES_H */
