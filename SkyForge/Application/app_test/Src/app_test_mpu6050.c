/*==============================================================================
 * TEST 1 : MPU6050 Accelerometer Range Configuration
 *==============================================================================
 *
 * Expected Output:
 *
 * Initializing MPU6050...
 * MPU6050 Initialization Successful
 *
 * Setting Accelerometer Range to +/-8g...
 * Accelerometer Range Configured
 *
 * Current Accel Range : +/-8g
 *
 * Accel X : xxxx
 * Accel Y : xxxx
 * Accel Z : xxxx
 *
 *===========================================================================*/

#include "app_test_mpu6050.h"

#include "main.h"
#include "bsp_uart.h"
#include "mpu6050.h"

#include <stdio.h>

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

void APP_Test_MPU6050(void)
{
    MPU6050_Accel_t accel;
    MPU6050_AccelRange_t accelRange;

    char message[128];
    const char *rangeStr = "Unknown";

    /*---------------------------------------------------------
     * Initialize MPU6050
     *--------------------------------------------------------*/

    BSP_UART_TransmitString(&huart2,
                            "\r\nInitializing MPU6050...\r\n");

    if (MPU6050_Init(&hi2c1) != HAL_OK)
    {
        BSP_UART_TransmitString(&huart2,
                                "MPU6050 Initialization Failed\r\n");

        while (1);
    }

    BSP_UART_TransmitString(&huart2,
                            "MPU6050 Initialization Successful\r\n");

    /*---------------------------------------------------------
     * Configure Accelerometer Range
     *--------------------------------------------------------*/

    BSP_UART_TransmitString(&huart2,
                            "Setting Accelerometer Range to +/-8g...\r\n");

    if (MPU6050_SetAccelRange(&hi2c1,
                              MPU6050_ACCEL_RANGE_8G) != HAL_OK)
    {
        BSP_UART_TransmitString(&huart2,
                                "Accelerometer Range Configuration Failed\r\n");

        while (1);
    }

    BSP_UART_TransmitString(&huart2,
                            "Accelerometer Range Configured\r\n");



    /*---------------------------------------------------------
     * Configure Gyroscope Range
     *--------------------------------------------------------*/

    BSP_UART_TransmitString(&huart2,
                            "Setting Gyroscope Range to +/-500 dps...\r\n");

    if (MPU6050_SetGyroRange(&hi2c1,
                             MPU6050_GYRO_RANGE_500DPS) != HAL_OK)
    {
        BSP_UART_TransmitString(&huart2,
                                "Gyroscope Range Configuration Failed\r\n");

        while (1);
    }

    BSP_UART_TransmitString(&huart2,
                            "Gyroscope Range Configured\r\n");


    /*---------------------------------------------------------
     * Verify Gyroscope Range
     *--------------------------------------------------------*/

    MPU6050_GyroRange_t gyroRange;
    const char *gyroRangeStr = "Unknown";

    if (MPU6050_GetGyroRange(&hi2c1,
                             &gyroRange) != HAL_OK)
    {
        BSP_UART_TransmitString(&huart2,
                                "Failed to Read Gyroscope Range\r\n");

        while (1);
    }

    switch (gyroRange)
    {
        case MPU6050_GYRO_RANGE_250DPS:
            gyroRangeStr = "+/-250 dps";
            break;

        case MPU6050_GYRO_RANGE_500DPS:
            gyroRangeStr = "+/-500 dps";
            break;

        case MPU6050_GYRO_RANGE_1000DPS:
            gyroRangeStr = "+/-1000 dps";
            break;

        case MPU6050_GYRO_RANGE_2000DPS:
            gyroRangeStr = "+/-2000 dps";
            break;

        default:
            break;
    }

    sprintf(message,
            "Current Gyro Range : %s\r\n",
            gyroRangeStr);

    BSP_UART_TransmitString(&huart2,
                            message);

    /*---------------------------------------------------------
     * Verify Accelerometer Range
     *--------------------------------------------------------*/

    if (MPU6050_GetAccelRange(&hi2c1,
                              &accelRange) != HAL_OK)
    {
        BSP_UART_TransmitString(&huart2,
                                "Failed to Read Accelerometer Range\r\n");

        while (1);
    }

    switch (accelRange)
    {
        case MPU6050_ACCEL_RANGE_2G:
            rangeStr = "+/-2g";
            break;

        case MPU6050_ACCEL_RANGE_4G:
            rangeStr = "+/-4g";
            break;

        case MPU6050_ACCEL_RANGE_8G:
            rangeStr = "+/-8g";
            break;

        case MPU6050_ACCEL_RANGE_16G:
            rangeStr = "+/-16g";
            break;

        default:
            rangeStr = "Unknown";
            break;
    }

    sprintf(message,
            "Current Accel Range : %s\r\n",
            rangeStr);

    BSP_UART_TransmitString(&huart2,
                            message);

    /*---------------------------------------------------------
     * Read Accelerometer Data
     *--------------------------------------------------------*/

    while (1)
    {
        if (MPU6050_ReadAccel(&hi2c1,
                              &accel) == HAL_OK)
        {
            sprintf(message,
                    "\r\n"
                    "Accel X : %6d\r\n"
                    "Accel Y : %6d\r\n"
                    "Accel Z : %6d\r\n",
                    accel.x,
                    accel.y,
                    accel.z);

            BSP_UART_TransmitString(&huart2,
                                    message);
        }
        else
        {
            BSP_UART_TransmitString(&huart2,
                                    "Accelerometer Read Failed\r\n");
        }

        HAL_Delay(500);
    }
}
