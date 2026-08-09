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



/*

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

*/
HAL_StatusTypeDef MPU6050_ReadAccelRaw(
    I2C_HandleTypeDef *hi2c,
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


/*=========================================================
 * Read Accelerometer
 *
 * Compatibility wrapper.
 * Returns raw accelerometer data.
 *=========================================================*/

HAL_StatusTypeDef MPU6050_ReadAccel(
    I2C_HandleTypeDef *hi2c,
    MPU6050_Accel_t *accel)
{
    return MPU6050_ReadAccelRaw(hi2c, accel);
}



/*=========================================================
 * Read Calibrated Accelerometer
 *
 * Output:
 *     X, Y, Z in g
 *
 * Calibration:
 *
 *     X Offset = +678 raw
 *     Y Offset = -223 raw
 *     Z Offset = -1284 raw
 *
 *     X Scale = 16237.5 raw/g
 *     Y Scale = 16332.7 raw/g
 *     Z Scale = 16420.5 raw/g
 *
 * NOTE:
 * These are provisional calibration values obtained from
 * stationary multi-orientation measurements.
 *=========================================================*/

HAL_StatusTypeDef MPU6050_ReadAccelCalibrated(
    I2C_HandleTypeDef *hi2c,
    MPU6050_AccelCalibrated_t *accel)
{
    MPU6050_Accel_t raw;

    if (MPU6050_ReadAccelRaw(hi2c, &raw) != HAL_OK)
    {
        return HAL_ERROR;
    }

    accel->x =
        ((float)raw.x - 678.0f) / 16237.5f;

    accel->y =
        ((float)raw.y - (-223.0f)) / 16332.7f;

    accel->z =
        ((float)raw.z - (-1284.0f)) / 16420.5f;

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


HAL_StatusTypeDef MPU6050_SetSampleRateDivider(
    I2C_HandleTypeDef *hi2c,
    uint8_t divider)
{
    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_SMPLRT_DIV,
                divider);
}

HAL_StatusTypeDef MPU6050_GetSampleRateDivider(
    I2C_HandleTypeDef *hi2c,
    uint8_t *divider)
{
    return MPU6050_ReadRegister(
                hi2c,
                MPU6050_REG_SMPLRT_DIV,
                divider);
}

HAL_StatusTypeDef MPU6050_SetDLPF(
    I2C_HandleTypeDef *hi2c,
    MPU6050_DLPF_t dlpf)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    /* Read current CONFIG register */
    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_CONFIG,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    /* Clear DLPF bits */
    regValue &= ~MPU6050_DLPF_CFG_Msk;

    /* Set new DLPF configuration */
    regValue |= ((uint8_t)dlpf << MPU6050_DLPF_CFG_Pos);

    /* Write updated register */
    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_CONFIG,
                regValue);
}


HAL_StatusTypeDef MPU6050_GetDLPF(
    I2C_HandleTypeDef *hi2c,
    MPU6050_DLPF_t *dlpf)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    /* Read CONFIG register */
    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_CONFIG,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    /* Extract DLPF bits */
    *dlpf = (MPU6050_DLPF_t)
            ((regValue & MPU6050_DLPF_CFG_Msk)
             >> MPU6050_DLPF_CFG_Pos);

    return HAL_OK;
}

HAL_StatusTypeDef MPU6050_SetClockSource(
    I2C_HandleTypeDef *hi2c,
    MPU6050_ClockSource_t source)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    /* Read current PWR_MGMT_1 register */
    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_PWR_MGMT_1,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    /* Clear CLKSEL bits [2:0] */
    regValue &= ~MPU6050_CLKSEL_Msk;

    /* Set new clock source */
    regValue |= ((uint8_t)source << MPU6050_CLKSEL_Pos);

    /* Write updated register */
    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_PWR_MGMT_1,
                regValue);
}

HAL_StatusTypeDef MPU6050_GetClockSource(
    I2C_HandleTypeDef *hi2c,
    MPU6050_ClockSource_t *source)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    /* Read PWR_MGMT_1 register */
    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_PWR_MGMT_1,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    /* Extract CLKSEL bits [2:0] */
    *source = (MPU6050_ClockSource_t)
              ((regValue & MPU6050_CLKSEL_Msk) >>
               MPU6050_CLKSEL_Pos);

    return HAL_OK;
}


/*=========================================================
 * Enable Data Ready Interrupt
 *========================================================*/

HAL_StatusTypeDef MPU6050_EnableDataReadyInterrupt(
    I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    /* Read current INT_ENABLE register */
    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_INT_ENABLE,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    /* Enable DATA_RDY interrupt */
    regValue |= MPU6050_DATA_RDY_INT_Msk;

    /* Write updated register */
    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_INT_ENABLE,
                regValue);
}

/*=========================================================
 * Disable Data Ready Interrupt
 *========================================================*/

HAL_StatusTypeDef MPU6050_DisableDataReadyInterrupt(
    I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    /* Read current INT_ENABLE register */
    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_INT_ENABLE,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    /* Disable DATA_RDY interrupt */
    regValue &= ~MPU6050_DATA_RDY_INT_Msk;

    /* Write updated register */
    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_INT_ENABLE,
                regValue);
}


/*=========================================================
 * Read Interrupt Status
 *========================================================*/

HAL_StatusTypeDef MPU6050_GetInterruptStatus(
    I2C_HandleTypeDef *hi2c,
    uint8_t *status)
{
    return MPU6050_ReadRegister(
                hi2c,
                MPU6050_REG_INT_STATUS,
                status);
}

HAL_StatusTypeDef MPU6050_GetInterruptEnable(
    I2C_HandleTypeDef *hi2c,
    uint8_t *enable)
{
    return MPU6050_ReadRegister(
                hi2c,
                MPU6050_REG_INT_ENABLE,
                enable);
}

/*=========================================================
 * Check DATA_RDY Interrupt Enable Status
 *========================================================*/

HAL_StatusTypeDef MPU6050_IsDataReadyInterruptEnabled(
    I2C_HandleTypeDef *hi2c,
    uint8_t *enabled)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_INT_ENABLE,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    *enabled =
        (regValue & MPU6050_DATA_RDY_INT_Msk) ? 1U : 0U;

    return HAL_OK;
}


/*=========================================================
 * Enable FIFO
 *========================================================*/

HAL_StatusTypeDef MPU6050_EnableFIFO(
    I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_USER_CTRL,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    regValue |= MPU6050_FIFO_EN_Msk;

    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_USER_CTRL,
                regValue);
}


/*=========================================================
 * Disable FIFO
 *========================================================*/

HAL_StatusTypeDef MPU6050_DisableFIFO(
    I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_USER_CTRL,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    regValue &= ~MPU6050_FIFO_EN_Msk;

    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_USER_CTRL,
                regValue);
}


/*=========================================================
 * Reset FIFO
 *========================================================*/

HAL_StatusTypeDef MPU6050_ResetFIFO(
    I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_USER_CTRL,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    regValue |= MPU6050_FIFO_RESET_Msk;

    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_USER_CTRL,
                regValue);
}



/*=========================================================
 * Get FIFO Enable Status
 *========================================================*/

HAL_StatusTypeDef MPU6050_GetFIFOEnable(
    I2C_HandleTypeDef *hi2c,
    uint8_t *enable)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_USER_CTRL,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    *enable =
        (regValue & MPU6050_FIFO_EN_Msk) ? 1U : 0U;

    return HAL_OK;
}



/*=========================================================
 * Enable Accelerometer FIFO
 *========================================================*/

HAL_StatusTypeDef MPU6050_EnableAccelFIFO(
    I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_EN,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    regValue |= MPU6050_FIFO_ACCEL_Msk;

    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_FIFO_EN,
                regValue);
}


/*=========================================================
 * Disable Accelerometer FIFO
 *========================================================*/

HAL_StatusTypeDef MPU6050_DisableAccelFIFO(
    I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_EN,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    regValue &= ~MPU6050_FIFO_ACCEL_Msk;

    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_FIFO_EN,
                regValue);
}



/*=========================================================
 * Check Accelerometer FIFO Status
 *========================================================*/

HAL_StatusTypeDef MPU6050_IsAccelFIFOEnabled(
    I2C_HandleTypeDef *hi2c,
    uint8_t *enabled)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_EN,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    *enabled =
        (regValue & MPU6050_FIFO_ACCEL_Msk) ? 1U : 0U;

    return HAL_OK;
}



/*=========================================================
 * Enable X Gyroscope FIFO
 *========================================================*/

HAL_StatusTypeDef MPU6050_EnableGyroXFIFO(
    I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_EN,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    regValue |= MPU6050_FIFO_XG_Msk;

    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_FIFO_EN,
                regValue);
}


/*=========================================================
 * Disable X Gyroscope FIFO
 *========================================================*/

HAL_StatusTypeDef MPU6050_DisableGyroXFIFO(
    I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_EN,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    regValue &= ~MPU6050_FIFO_XG_Msk;

    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_FIFO_EN,
                regValue);
}


/*=========================================================
 * Check X Gyroscope FIFO Status
 *========================================================*/

HAL_StatusTypeDef MPU6050_IsGyroXFIFOEnabled(
    I2C_HandleTypeDef *hi2c,
    uint8_t *enabled)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_EN,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    *enabled =
        (regValue & MPU6050_FIFO_XG_Msk) ? 1U : 0U;

    return HAL_OK;
}







/*=========================================================
 * Enable Y Gyroscope FIFO
 *========================================================*/

HAL_StatusTypeDef MPU6050_EnableGyroYFIFO(
    I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_EN,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    regValue |= MPU6050_FIFO_YG_Msk;

    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_FIFO_EN,
                regValue);
}


/*=========================================================
 * Disable Y Gyroscope FIFO
 *========================================================*/

HAL_StatusTypeDef MPU6050_DisableGyroYFIFO(
    I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_EN,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    regValue &= ~MPU6050_FIFO_YG_Msk;

    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_FIFO_EN,
                regValue);
}


/*=========================================================
 * Check Y Gyroscope FIFO Status
 *========================================================*/

HAL_StatusTypeDef MPU6050_IsGyroYFIFOEnabled(
    I2C_HandleTypeDef *hi2c,
    uint8_t *enabled)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_EN,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    *enabled =
        (regValue & MPU6050_FIFO_YG_Msk) ? 1U : 0U;

    return HAL_OK;
}







/*=========================================================
 * Enable Z Gyroscope FIFO
 *========================================================*/

HAL_StatusTypeDef MPU6050_EnableGyroZFIFO(
    I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_EN,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    regValue |= MPU6050_FIFO_ZG_Msk;

    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_FIFO_EN,
                regValue);
}


/*=========================================================
 * Disable Z Gyroscope FIFO
 *========================================================*/

HAL_StatusTypeDef MPU6050_DisableGyroZFIFO(
    I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_EN,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    regValue &= ~MPU6050_FIFO_ZG_Msk;

    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_FIFO_EN,
                regValue);
}


/*=========================================================
 * Check Z Gyroscope FIFO Status
 *========================================================*/

HAL_StatusTypeDef MPU6050_IsGyroZFIFOEnabled(
    I2C_HandleTypeDef *hi2c,
    uint8_t *enabled)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_EN,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    *enabled =
        (regValue & MPU6050_FIFO_ZG_Msk) ? 1U : 0U;

    return HAL_OK;
}




/*=========================================================
 * Enable Temperature FIFO
 *========================================================*/

HAL_StatusTypeDef MPU6050_EnableTempFIFO(
    I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_EN,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    regValue |= MPU6050_FIFO_TEMP_Msk;

    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_FIFO_EN,
                regValue);
}



/*=========================================================
 * Disable Temperature FIFO
 *========================================================*/

HAL_StatusTypeDef MPU6050_DisableTempFIFO(
    I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_EN,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    regValue &= ~MPU6050_FIFO_TEMP_Msk;

    return MPU6050_WriteRegister(
                hi2c,
                MPU6050_REG_FIFO_EN,
                regValue);
}


/*=========================================================
 * Check Temperature FIFO Status
 *========================================================*/

HAL_StatusTypeDef MPU6050_IsTempFIFOEnabled(
    I2C_HandleTypeDef *hi2c,
    uint8_t *enabled)
{
    HAL_StatusTypeDef status;
    uint8_t regValue;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_EN,
                    &regValue);

    if (status != HAL_OK)
    {
        return status;
    }

    *enabled =
        (regValue & MPU6050_FIFO_TEMP_Msk) ? 1U : 0U;

    return HAL_OK;
}



/*=========================================================
 * Read FIFO Count
 *========================================================*/

HAL_StatusTypeDef MPU6050_GetFIFOCount(
    I2C_HandleTypeDef *hi2c,
    uint16_t *count)
{
    HAL_StatusTypeDef status;

    uint8_t fifoCountHigh;
    uint8_t fifoCountLow;

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_COUNTH,
                    &fifoCountHigh);

    if (status != HAL_OK)
    {
        return status;
    }

    status = MPU6050_ReadRegister(
                    hi2c,
                    MPU6050_REG_FIFO_COUNTL,
                    &fifoCountLow);

    if (status != HAL_OK)
    {
        return status;
    }

    *count =
        ((uint16_t)fifoCountHigh << 8) |
         (uint16_t)fifoCountLow;

    return HAL_OK;
}



/*=========================================================
 * Read FIFO Byte
 *========================================================*/

HAL_StatusTypeDef MPU6050_ReadFIFO(
    I2C_HandleTypeDef *hi2c,
    uint8_t *data)
{
    return MPU6050_ReadRegister(
                hi2c,
                MPU6050_REG_FIFO_R_W,
                data);
}


/*=========================================================
 * Read FIFO Buffer
 *========================================================*/

HAL_StatusTypeDef MPU6050_ReadFIFOBuffer(
    I2C_HandleTypeDef *hi2c,
    uint8_t *buffer,
    uint16_t length)
{
    return HAL_I2C_Mem_Read(
                hi2c,
                MPU6050_I2C_ADDR_LOW,
                MPU6050_REG_FIFO_R_W,
                I2C_MEMADD_SIZE_8BIT,
                buffer,
                length,
                HAL_MAX_DELAY);
}





/*=========================================================
 * Read FIFO Packet
 *========================================================*/

HAL_StatusTypeDef MPU6050_ReadFIFOPacket(
    I2C_HandleTypeDef *hi2c,
    MPU6050_FIFOPacket_t *packet)
{
    HAL_StatusTypeDef status;

    uint8_t buffer[14];

    status = MPU6050_ReadFIFOBuffer(
                    hi2c,
                    buffer,
                    sizeof(buffer));

    if (status != HAL_OK)
    {
        return status;
    }

    /*---------------------------------------------------------
     * Accelerometer
     *--------------------------------------------------------*/

    packet->accel.x =
        (int16_t)((buffer[0] << 8) | buffer[1]);

    packet->accel.y =
        (int16_t)((buffer[2] << 8) | buffer[3]);

    packet->accel.z =
        (int16_t)((buffer[4] << 8) | buffer[5]);

    /*---------------------------------------------------------
     * Temperature
     *--------------------------------------------------------*/

    packet->temp.raw =
        (int16_t)((buffer[6] << 8) | buffer[7]);

    packet->temp.temperature =
        (packet->temp.raw / 340.0f) + 36.53f;

    /*---------------------------------------------------------
     * Gyroscope
     *--------------------------------------------------------*/

    packet->gyro.x =
        (int16_t)((buffer[8] << 8) | buffer[9]);

    packet->gyro.y =
        (int16_t)((buffer[10] << 8) | buffer[11]);

    packet->gyro.z =
        (int16_t)((buffer[12] << 8) | buffer[13]);

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
