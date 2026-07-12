/******************************************************************************
 * @file    mpu6050_reg.h
 * @brief   MPU6050 register map definitions.
 *
 * @details
 * This file contains only the register addresses of the MPU6050 IMU.
 * No functions, structures, configuration values or implementation code
 * should be placed here.
 *
 * Architecture:
 *
 *      MPU6050 Driver
 *             │
 *             ▼
 *     Register Definitions
 *
 * Why Separate Register Definitions?
 * ----------------------------------
 * Register addresses are hardware-specific constants.
 * Keeping them isolated improves readability and simplifies maintenance.
 *
 * Future Improvements:
 * --------------------
 * - Add reserved register definitions if required.
 * - Add register bit-field documentation.
 *
 * Portability Notes:
 * ------------------
 * If another IMU is used (e.g. ICM42688 or BMI270),
 * create a separate *_reg.h file instead of modifying this file.
 *
 * @author  Rakesh Bhanavath
 * @project SkyForge
 ******************************************************************************/

#ifndef MPU6050_REG_H
#define MPU6050_REG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Register Map -------------------------------------------------------------*/

/* Sample Rate Divider */
#define MPU6050_REG_SMPLRT_DIV          0x19U

/* Configuration */
#define MPU6050_REG_CONFIG              0x1AU

/* Gyroscope Configuration */
#define MPU6050_REG_GYRO_CONFIG         0x1BU

/* Accelerometer Configuration */
#define MPU6050_REG_ACCEL_CONFIG        0x1CU

/* Accelerometer Output Registers */
#define MPU6050_REG_ACCEL_XOUT_H        0x3BU
#define MPU6050_REG_ACCEL_XOUT_L        0x3CU
#define MPU6050_REG_ACCEL_YOUT_H        0x3DU
#define MPU6050_REG_ACCEL_YOUT_L        0x3EU
#define MPU6050_REG_ACCEL_ZOUT_H        0x3FU
#define MPU6050_REG_ACCEL_ZOUT_L        0x40U

/* Temperature Output Registers */
#define MPU6050_REG_TEMP_OUT_H          0x41U
#define MPU6050_REG_TEMP_OUT_L          0x42U

/* Gyroscope Output Registers */
#define MPU6050_REG_GYRO_XOUT_H         0x43U
#define MPU6050_REG_GYRO_XOUT_L         0x44U
#define MPU6050_REG_GYRO_YOUT_H         0x45U
#define MPU6050_REG_GYRO_YOUT_L         0x46U
#define MPU6050_REG_GYRO_ZOUT_H         0x47U
#define MPU6050_REG_GYRO_ZOUT_L         0x48U

/* Power Management */
#define MPU6050_REG_PWR_MGMT_1          0x6BU
#define MPU6050_REG_PWR_MGMT_2          0x6CU

/* Device Identification */
#define MPU6050_REG_WHO_AM_I            0x75U

#ifdef __cplusplus
}
#endif

#endif /* MPU6050_REG_H */
