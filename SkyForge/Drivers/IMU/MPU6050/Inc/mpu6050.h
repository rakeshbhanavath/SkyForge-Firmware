#ifndef MPU6050_H
#define MPU6050_H

#ifdef __cplusplus
extern "C"
{
#endif

/*=========================================================
 * Includes
 *========================================================*/

#include "main.h"
#include <stdint.h>

#include "mpu6050_defs.h"
#include "mpu6050_types.h"
#include "mpu6050_utils.h"

/*=========================================================
 * Device Control Functions
 *========================================================*/

/**
 * @brief Initialize MPU6050.
 */
HAL_StatusTypeDef MPU6050_Init(I2C_HandleTypeDef *hi2c);

/**
 * @brief Perform software reset.
 */
HAL_StatusTypeDef MPU6050_Reset(I2C_HandleTypeDef *hi2c);

/**
 * @brief Wake the sensor.
 */
HAL_StatusTypeDef MPU6050_WakeUp(I2C_HandleTypeDef *hi2c);

/**
 * @brief Put the sensor into sleep mode.
 */
HAL_StatusTypeDef MPU6050_Sleep(I2C_HandleTypeDef *hi2c);

/*=========================================================
 * Register Access Functions
 *========================================================*/

/**
 * @brief Read one register.
 */
HAL_StatusTypeDef MPU6050_ReadRegister(I2C_HandleTypeDef *hi2c,
                                       uint8_t reg,
                                       uint8_t *data);

/**
 * @brief Write one register.
 */
HAL_StatusTypeDef MPU6050_WriteRegister(I2C_HandleTypeDef *hi2c,
                                        uint8_t reg,
                                        uint8_t data);

/**
 * @brief Read WHO_AM_I register.
 */
HAL_StatusTypeDef MPU6050_ReadWHOAMI(I2C_HandleTypeDef *hi2c,
                                     uint8_t *id);

/*=========================================================
 * Accelerometer Configuration
 *========================================================*/

HAL_StatusTypeDef MPU6050_SetAccelRange(I2C_HandleTypeDef *hi2c,
                                        MPU6050_AccelRange_t range);

HAL_StatusTypeDef MPU6050_GetAccelRange(I2C_HandleTypeDef *hi2c,
                                        MPU6050_AccelRange_t *range);

/*=========================================================
 * Gyroscope Configuration
 *========================================================*/

HAL_StatusTypeDef MPU6050_SetGyroRange(I2C_HandleTypeDef *hi2c,
                                       MPU6050_GyroRange_t range);

HAL_StatusTypeDef MPU6050_GetGyroRange(I2C_HandleTypeDef *hi2c,
                                       MPU6050_GyroRange_t *range);

/*=========================================================
 * Sampling Configuration
 *========================================================*/

HAL_StatusTypeDef MPU6050_SetSampleRateDivider(I2C_HandleTypeDef *hi2c,
                                               uint8_t divider);

HAL_StatusTypeDef MPU6050_GetSampleRateDivider(I2C_HandleTypeDef *hi2c,
                                               uint8_t *divider);

HAL_StatusTypeDef MPU6050_SetDLPF(I2C_HandleTypeDef *hi2c,
                                  MPU6050_DLPF_t dlpf);

HAL_StatusTypeDef MPU6050_GetDLPF(I2C_HandleTypeDef *hi2c,
                                  MPU6050_DLPF_t *dlpf);

HAL_StatusTypeDef MPU6050_SetClockSource(I2C_HandleTypeDef *hi2c,
                                         MPU6050_ClockSource_t source);

HAL_StatusTypeDef MPU6050_GetClockSource(I2C_HandleTypeDef *hi2c,
                                         MPU6050_ClockSource_t *source);

/*=========================================================
 * Interrupt Configuration
 *========================================================*/

HAL_StatusTypeDef MPU6050_EnableDataReadyInterrupt(I2C_HandleTypeDef *hi2c);

HAL_StatusTypeDef MPU6050_DisableDataReadyInterrupt(I2C_HandleTypeDef *hi2c);

HAL_StatusTypeDef MPU6050_GetInterruptStatus(I2C_HandleTypeDef *hi2c,
                                             uint8_t *status);

HAL_StatusTypeDef MPU6050_GetInterruptEnable(I2C_HandleTypeDef *hi2c,
                                             uint8_t *enable);

HAL_StatusTypeDef MPU6050_IsDataReadyInterruptEnabled(I2C_HandleTypeDef *hi2c,
                                                      uint8_t *enabled);

/*=========================================================
 * FIFO Configuration
 *========================================================*/

/**
 * @brief Enable FIFO hardware.
 */
HAL_StatusTypeDef MPU6050_EnableFIFO(I2C_HandleTypeDef *hi2c);

/**
 * @brief Disable FIFO hardware.
 */
HAL_StatusTypeDef MPU6050_DisableFIFO(I2C_HandleTypeDef *hi2c);

/**
 * @brief Reset FIFO buffer.
 */
HAL_StatusTypeDef MPU6050_ResetFIFO(I2C_HandleTypeDef *hi2c);

/**
 * @brief Get FIFO hardware enable status.
 */
HAL_StatusTypeDef MPU6050_GetFIFOEnable(I2C_HandleTypeDef *hi2c,
                                        uint8_t *enable);



/*=========================================================
 * FIFO Data Functions
 *========================================================*/

/**
 * @brief Read the number of bytes currently stored in FIFO.
 */
HAL_StatusTypeDef MPU6050_GetFIFOCount(
    I2C_HandleTypeDef *hi2c,
    uint16_t *count);


/**
 * @brief Read one byte from FIFO.
 */
HAL_StatusTypeDef MPU6050_ReadFIFO(
    I2C_HandleTypeDef *hi2c,
    uint8_t *data);

/**
 * @brief Read multiple bytes from FIFO.
 *
 * @param hi2c   Pointer to I2C handle.
 * @param buffer Destination buffer.
 * @param length Number of bytes to read.
 *
 * @return HAL status.
 */
HAL_StatusTypeDef MPU6050_ReadFIFOBuffer(
    I2C_HandleTypeDef *hi2c,
    uint8_t *buffer,
    uint16_t length);


/**
 * @brief Read one complete sensor packet from FIFO.
 */
HAL_StatusTypeDef MPU6050_ReadFIFOPacket(
    I2C_HandleTypeDef *hi2c,
    MPU6050_FIFOPacket_t *packet);

/*---------------------------------------------------------
 * Accelerometer FIFO Configuration
 *--------------------------------------------------------*/

/**
 * @brief Enable Accelerometer data to be stored in FIFO.
 */
HAL_StatusTypeDef MPU6050_EnableAccelFIFO(I2C_HandleTypeDef *hi2c);

/**
 * @brief Disable Accelerometer data from FIFO.
 */
HAL_StatusTypeDef MPU6050_DisableAccelFIFO(I2C_HandleTypeDef *hi2c);

/**
 * @brief Check whether Accelerometer FIFO is enabled.
 */
HAL_StatusTypeDef MPU6050_IsAccelFIFOEnabled(I2C_HandleTypeDef *hi2c,
                                             uint8_t *enabled);


/*---------------------------------------------------------
 * Gyroscope FIFO Configuration
 *--------------------------------------------------------*/

/**
 * @brief Enable X Gyroscope FIFO.
 */
HAL_StatusTypeDef MPU6050_EnableGyroXFIFO(I2C_HandleTypeDef *hi2c);

/**
 * @brief Disable X Gyroscope FIFO.
 */
HAL_StatusTypeDef MPU6050_DisableGyroXFIFO(I2C_HandleTypeDef *hi2c);

/**
 * @brief Check X Gyroscope FIFO status.
 */
HAL_StatusTypeDef MPU6050_IsGyroXFIFOEnabled(I2C_HandleTypeDef *hi2c,
                                             uint8_t *enabled);

/**
 * @brief Enable Y Gyroscope FIFO.
 */
HAL_StatusTypeDef MPU6050_EnableGyroYFIFO(I2C_HandleTypeDef *hi2c);

/**
 * @brief Disable Y Gyroscope FIFO.
 */
HAL_StatusTypeDef MPU6050_DisableGyroYFIFO(I2C_HandleTypeDef *hi2c);

/**
 * @brief Check Y Gyroscope FIFO status.
 */
HAL_StatusTypeDef MPU6050_IsGyroYFIFOEnabled(I2C_HandleTypeDef *hi2c,
                                             uint8_t *enabled);

/**
 * @brief Enable Z Gyroscope FIFO.
 */
HAL_StatusTypeDef MPU6050_EnableGyroZFIFO(I2C_HandleTypeDef *hi2c);

/**
 * @brief Disable Z Gyroscope FIFO.
 */
HAL_StatusTypeDef MPU6050_DisableGyroZFIFO(I2C_HandleTypeDef *hi2c);

/**
 * @brief Check Z Gyroscope FIFO status.
 */
HAL_StatusTypeDef MPU6050_IsGyroZFIFOEnabled(I2C_HandleTypeDef *hi2c,
                                             uint8_t *enabled);



/*---------------------------------------------------------
 * Temperature FIFO Configuration
 *--------------------------------------------------------*/

/**
 * @brief Enable Temperature FIFO.
 */
HAL_StatusTypeDef MPU6050_EnableTempFIFO(
    I2C_HandleTypeDef *hi2c);

/**
 * @brief Disable Temperature FIFO.
 */
HAL_StatusTypeDef MPU6050_DisableTempFIFO(
    I2C_HandleTypeDef *hi2c);

/**
 * @brief Check Temperature FIFO status.
 */
HAL_StatusTypeDef MPU6050_IsTempFIFOEnabled(
    I2C_HandleTypeDef *hi2c,
    uint8_t *enabled);



/*=========================================================
 * Sensor Data Functions
 *========================================================*/

HAL_StatusTypeDef MPU6050_ReadAccel(I2C_HandleTypeDef *hi2c,
                                    MPU6050_Accel_t *accel);

HAL_StatusTypeDef MPU6050_ReadGyro(I2C_HandleTypeDef *hi2c,
                                   MPU6050_Gyro_t *gyro);

HAL_StatusTypeDef MPU6050_ReadTemperature(I2C_HandleTypeDef *hi2c,
                                          MPU6050_Temp_t *temp);

#ifdef __cplusplus
}
#endif

#endif /* MPU6050_H */
