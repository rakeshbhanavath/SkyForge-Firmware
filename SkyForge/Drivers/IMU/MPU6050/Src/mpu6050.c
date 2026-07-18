#include "mpu6050.h"
#include "mpu6050_reg.h"


HAL_StatusTypeDef MPU6050_ReadRegister(I2C_HandleTypeDef *hi2c,
                                       uint8_t reg,
                                       uint8_t *data)
{
    return HAL_I2C_Mem_Read(hi2c,
                            MPU6050_I2C_ADDR_LOW,
                            reg,
                            I2C_MEMADD_SIZE_8BIT,
                            data,
                            1,
                            HAL_MAX_DELAY);
}

HAL_StatusTypeDef MPU6050_WriteRegister(I2C_HandleTypeDef *hi2c,
                                        uint8_t reg,
                                        uint8_t data)
{
    return HAL_I2C_Mem_Write(hi2c,
                             MPU6050_I2C_ADDR_LOW,
                             reg,
                             I2C_MEMADD_SIZE_8BIT,
                             &data,
                             1,
                             HAL_MAX_DELAY);
}

HAL_StatusTypeDef MPU6050_ReadWHOAMI(I2C_HandleTypeDef *hi2c,
                                     uint8_t *id)
{
    return MPU6050_ReadRegister(hi2c,
                                MPU6050_REG_WHO_AM_I,
                                id);
}

HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c)
{
    uint8_t id;

    if (MPU6050_ReadWHOAMI(hi2c, &id) != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (id != 0x68)
    {
        return HAL_ERROR;
    }

    if (MPU6050_WriteRegister(hi2c,
                              MPU6050_REG_PWR_MGMT_1,
                              0x00) != HAL_OK)
    {
        return HAL_ERROR;
    }

    HAL_Delay(100);

    return HAL_OK;
}

HAL_StatusTypeDef MPU6050_ReadAccel(I2C_HandleTypeDef *hi2c,
                                    MPU6050_Accel_t *accel)
{
    uint8_t buffer[6];

    if (HAL_I2C_Mem_Read(hi2c,
                         MPU6050_I2C_ADDR_LOW,
                         MPU6050_REG_ACCEL_XOUT_H,
                         I2C_MEMADD_SIZE_8BIT,
                         buffer,
                         6,
                         HAL_MAX_DELAY) != HAL_OK)
    {
        return HAL_ERROR;
    }

    accel->x = (int16_t)((buffer[0] << 8) | buffer[1]);
    accel->y = (int16_t)((buffer[2] << 8) | buffer[3]);
    accel->z = (int16_t)((buffer[4] << 8) | buffer[5]);

    return HAL_OK;
}

HAL_StatusTypeDef MPU6050_ReadGyro(I2C_HandleTypeDef *hi2c,
                                   MPU6050_Gyro_t *gyro)
{
    uint8_t buffer[6];

    if (HAL_I2C_Mem_Read(hi2c,
                         MPU6050_I2C_ADDR_LOW,
                         MPU6050_REG_GYRO_XOUT_H,
                         I2C_MEMADD_SIZE_8BIT,
                         buffer,
                         6,
                         HAL_MAX_DELAY) != HAL_OK)
    {
        return HAL_ERROR;
    }

    gyro->x = (int16_t)((buffer[0] << 8) | buffer[1]);
    gyro->y = (int16_t)((buffer[2] << 8) | buffer[3]);
    gyro->z = (int16_t)((buffer[4] << 8) | buffer[5]);

    return HAL_OK;
}

HAL_StatusTypeDef MPU6050_ReadTemperature(I2C_HandleTypeDef *hi2c,
                                          MPU6050_Temp_t *temp)
{
    uint8_t buffer[2];

    if (HAL_I2C_Mem_Read(hi2c,
                         MPU6050_I2C_ADDR_LOW,
                         MPU6050_REG_TEMP_OUT_H,
                         I2C_MEMADD_SIZE_8BIT,
                         buffer,
                         2,
                         HAL_MAX_DELAY) != HAL_OK)
    {
        return HAL_ERROR;
    }

    temp->raw = (int16_t)((buffer[0] << 8) | buffer[1]);

    temp->temperature =
        ((float)temp->raw / 340.0f) + 36.53f;

    return HAL_OK;
}
