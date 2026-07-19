#ifndef MPU6050_H
#define MPU6050_H

#include "main.h"
#include <stdint.h>

/*=========================================================
 * Data Types
 *========================================================*/

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
} MPU6050_Accel_t;

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
} MPU6050_Gyro_t;

typedef struct
{
    int16_t raw;
    float temperature;
} MPU6050_Temp_t;

/*=========================================================
 * Enumerations
 *========================================================*/

typedef enum
{
    MPU6050_ACCEL_RANGE_2G = 0,
    MPU6050_ACCEL_RANGE_4G,
    MPU6050_ACCEL_RANGE_8G,
    MPU6050_ACCEL_RANGE_16G
} MPU6050_AccelRange_t;

typedef enum
{
    MPU6050_GYRO_RANGE_250DPS = 0,
    MPU6050_GYRO_RANGE_500DPS,
    MPU6050_GYRO_RANGE_1000DPS,
    MPU6050_GYRO_RANGE_2000DPS
} MPU6050_GyroRange_t;

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

/*=========================================================
 * Sensor Read Functions
 *========================================================*/

HAL_StatusTypeDef MPU6050_ReadAccel(I2C_HandleTypeDef *hi2c,
                                    MPU6050_Accel_t *accel);

HAL_StatusTypeDef MPU6050_ReadGyro(I2C_HandleTypeDef *hi2c,
                                   MPU6050_Gyro_t *gyro);

HAL_StatusTypeDef MPU6050_ReadTemperature(I2C_HandleTypeDef *hi2c,
                                          MPU6050_Temp_t *temp);




#endif /* MPU6050_H */
