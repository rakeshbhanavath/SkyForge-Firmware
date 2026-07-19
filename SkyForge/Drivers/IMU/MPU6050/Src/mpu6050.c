#include "mpu6050.h"
#include "mpu6050_reg.h"



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

  /*  if (MPU6050_WriteRegister(hi2c,
                              MPU6050_REG_PWR_MGMT_1,
                              0x00) != HAL_OK)
    {
        return HAL_ERROR;
    } */
    if (MPU6050_WakeUp(hi2c) != HAL_OK)
    {
        return HAL_ERROR;
    }

    HAL_Delay(100);

    return HAL_OK;
}


/*=========================================================
 * Reset Device
 *========================================================*/

HAL_StatusTypeDef MPU6050_Reset(I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;

    status = MPU6050_WriteRegister(hi2c,
                                   MPU6050_REG_PWR_MGMT_1,
                                   MPU6050_DEVICE_RESET);

    if (status != HAL_OK)
    {
        return status;
    }

    HAL_Delay(100);

    return MPU6050_WakeUp(hi2c);
}

/*=========================================================
 * Wake Up Device
 *========================================================*/

HAL_StatusTypeDef MPU6050_WakeUp(I2C_HandleTypeDef *hi2c)
{
    return MPU6050_WriteRegister(hi2c,
                                 MPU6050_REG_PWR_MGMT_1,
                                 0x00);
}

/*=========================================================
 * Put Device into Sleep Mode
 *========================================================*/

HAL_StatusTypeDef MPU6050_Sleep(I2C_HandleTypeDef *hi2c)
{
    return MPU6050_WriteRegister(hi2c,
                                 MPU6050_REG_PWR_MGMT_1,
                                 MPU6050_SLEEP);
}




/*=========================================================
 * Configure Accelerometer Full Scale Range
 *========================================================*/

HAL_StatusTypeDef MPU6050_SetAccelRange(I2C_HandleTypeDef *hi2c,
                                        MPU6050_AccelRange_t range)
{
    HAL_StatusTypeDef status;
    uint8_t reg;

    /* Read current ACCEL_CONFIG register */
    status = MPU6050_ReadRegister(hi2c,
                                  MPU6050_REG_ACCEL_CONFIG,
                                  &reg);

    if (status != HAL_OK)
    {
        return status;
    }

    /* Clear FS_SEL bits (Bits 4:3) */
    reg &= ~MPU6050_ACCEL_FS_SEL_Msk;

    /* Set new range */
    reg |= ((uint8_t)range << MPU6050_ACCEL_FS_SEL_Pos);

    /* Write updated register */
    return MPU6050_WriteRegister(hi2c,
                                 MPU6050_REG_ACCEL_CONFIG,
                                 reg);
}


HAL_StatusTypeDef MPU6050_GetAccelRange(I2C_HandleTypeDef *hi2c,
                                        MPU6050_AccelRange_t *range)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(hi2c,
                                  MPU6050_REG_ACCEL_CONFIG,
                                  &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    /* Extract AFS_SEL bits [4:3] */
//    *range = (MPU6050_AccelRange_t)((regValue >> 3U) & 0x03U);
    *range = (MPU6050_AccelRange_t)
             ((regValue & MPU6050_ACCEL_FS_SEL_Msk) >>
              MPU6050_ACCEL_FS_SEL_Pos);

    return HAL_OK;
}



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



HAL_StatusTypeDef MPU6050_SetGyroRange(I2C_HandleTypeDef *hi2c,
                                       MPU6050_GyroRange_t range)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(hi2c,
                                  MPU6050_REG_GYRO_CONFIG,
                                  &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    regValue &= ~MPU6050_GYRO_FS_SEL_Msk;

    regValue |= ((uint8_t)range << MPU6050_GYRO_FS_SEL_Pos);

    return MPU6050_WriteRegister(hi2c,
                                 MPU6050_REG_GYRO_CONFIG,
                                 regValue);
}



HAL_StatusTypeDef MPU6050_GetGyroRange(I2C_HandleTypeDef *hi2c,
                                       MPU6050_GyroRange_t *range)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(hi2c,
                                  MPU6050_REG_GYRO_CONFIG,
                                  &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    *range = (MPU6050_GyroRange_t)
             ((regValue & MPU6050_GYRO_FS_SEL_Msk) >>
              MPU6050_GYRO_FS_SEL_Pos);

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


/*=========================================================
 * Reset Device
 *========================================================*/
/*

HAL_StatusTypeDef MPU6050_Reset(I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;

    status = MPU6050_WriteRegister(hi2c,
                                   MPU6050_REG_PWR_MGMT_1,
                                   MPU6050_DEVICE_RESET);

    if (status != HAL_OK)
    {
        return status;
    }

    HAL_Delay(100);

    return HAL_OK;
}


HAL_StatusTypeDef MPU6050_Reset(I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;

    status = MPU6050_WriteRegister(hi2c,
                                   MPU6050_REG_PWR_MGMT_1,
                                   MPU6050_DEVICE_RESET);

    HAL_Delay(200);

    return status;
}
*/
