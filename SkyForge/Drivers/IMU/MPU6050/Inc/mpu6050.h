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
 * Function Prototypes
 *========================================================*/

HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c);

HAL_StatusTypeDef MPU6050_ReadRegister(I2C_HandleTypeDef *hi2c,
                                       uint8_t reg,
                                       uint8_t *data);

HAL_StatusTypeDef MPU6050_WriteRegister(I2C_HandleTypeDef *hi2c,
                                        uint8_t reg,
                                        uint8_t data);

HAL_StatusTypeDef MPU6050_ReadWHOAMI(I2C_HandleTypeDef *hi2c,
                                     uint8_t *id);

HAL_StatusTypeDef MPU6050_ReadAccel(I2C_HandleTypeDef *hi2c,
                                    MPU6050_Accel_t *accel);

HAL_StatusTypeDef MPU6050_ReadGyro(I2C_HandleTypeDef *hi2c,
                                   MPU6050_Gyro_t *gyro);

HAL_StatusTypeDef MPU6050_ReadTemperature(I2C_HandleTypeDef *hi2c,
                                          MPU6050_Temp_t *temp);

#endif
