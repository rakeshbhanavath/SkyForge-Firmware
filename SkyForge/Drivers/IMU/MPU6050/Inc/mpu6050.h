#ifndef MPU6050_H
#define MPU6050_H

#include "main.h"
#include <stdint.h>

#include "mpu6050_defs.h"
#include "mpu6050_types.h"
//#include "mpu6050_reg.h"
#include "mpu6050_utils.h"

/*=========================================================
 * Initialization Functions
 *========================================================*/

HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef MPU6050_Reset(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef MPU6050_WakeUp(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef MPU6050_Sleep(I2C_HandleTypeDef *hi2c);

/*=========================================================
 * Register Access Functions
 *========================================================*/

HAL_StatusTypeDef MPU6050_ReadRegister(I2C_HandleTypeDef *hi2c,
                                       uint8_t reg,
                                       uint8_t *data);

HAL_StatusTypeDef MPU6050_WriteRegister(I2C_HandleTypeDef *hi2c,
                                        uint8_t reg,
                                        uint8_t data);

HAL_StatusTypeDef MPU6050_ReadWHOAMI(I2C_HandleTypeDef *hi2c,
                                     uint8_t *id);

/*=========================================================
 * Configuration Functions
 *========================================================*/

HAL_StatusTypeDef MPU6050_GetAccelRange(I2C_HandleTypeDef *hi2c,
                                        MPU6050_AccelRange_t *range);

HAL_StatusTypeDef MPU6050_SetAccelRange(I2C_HandleTypeDef *hi2c,
                                        MPU6050_AccelRange_t range);

HAL_StatusTypeDef MPU6050_SetGyroRange(I2C_HandleTypeDef *hi2c,
                                       MPU6050_GyroRange_t range);

HAL_StatusTypeDef MPU6050_GetGyroRange(I2C_HandleTypeDef *hi2c,
                                       MPU6050_GyroRange_t *range);

HAL_StatusTypeDef MPU6050_SetSampleRateDivider(I2C_HandleTypeDef *hi2c,
                                               uint8_t divider);

HAL_StatusTypeDef MPU6050_GetSampleRateDivider(I2C_HandleTypeDef *hi2c,
                                               uint8_t *divider);

HAL_StatusTypeDef MPU6050_SetDLPF(I2C_HandleTypeDef *hi2c,
                                  MPU6050_DLPF_t dlpf);

HAL_StatusTypeDef MPU6050_GetDLPF(I2C_HandleTypeDef *hi2c,
                                  MPU6050_DLPF_t *dlpf);

HAL_StatusTypeDef MPU6050_SetClockSource(
    I2C_HandleTypeDef *hi2c,
    MPU6050_ClockSource_t source);

HAL_StatusTypeDef MPU6050_GetClockSource(
    I2C_HandleTypeDef *hi2c,
    MPU6050_ClockSource_t *source);

/*=========================================================
 * Sensor Read Functions
 *========================================================*/

HAL_StatusTypeDef MPU6050_ReadAccel(I2C_HandleTypeDef *hi2c,
                                    MPU6050_Accel_t *accel);

HAL_StatusTypeDef MPU6050_ReadGyro(I2C_HandleTypeDef *hi2c,
                                   MPU6050_Gyro_t *gyro);

HAL_StatusTypeDef MPU6050_ReadTemperature(I2C_HandleTypeDef *hi2c,
                                          MPU6050_Temp_t *temp);

#endif
