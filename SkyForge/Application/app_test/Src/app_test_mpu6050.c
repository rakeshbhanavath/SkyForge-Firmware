/*==============================================================================
 * TEST 1 : MPU6050 Driver Test
 *==============================================================================
 *
 * Expected Output:
 *
 * Initializing MPU6050...
 * MPU6050 Initialization Successful
 *
 * Accel X : xxxx
 * Accel Y : xxxx
 * Accel Z : xxxx
 *
 * Gyro X  : xxxx
 * Gyro Y  : xxxx
 * Gyro Z  : xxxx
 *
 * Temperature : xx.xx C
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
    MPU6050_Gyro_t gyro;
    MPU6050_Temp_t temp;

    char message[128];

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

    while (1)
    {
        MPU6050_ReadAccel(&hi2c1, &accel);

        MPU6050_ReadGyro(&hi2c1, &gyro);

        MPU6050_ReadTemperature(&hi2c1, &temp);

        sprintf(message,
                "\r\n"
                "Accel X : %6d\r\n"
                "Accel Y : %6d\r\n"
                "Accel Z : %6d\r\n"
                "\r\n"
                "Gyro X  : %6d\r\n"
                "Gyro Y  : %6d\r\n"
                "Gyro Z  : %6d\r\n"
                "\r\n"
                "Temperature : %.2f C\r\n",
                accel.x,
                accel.y,
                accel.z,
                gyro.x,
                gyro.y,
                gyro.z,
                temp.temperature);

        BSP_UART_TransmitString(&huart2,
                                message);

        HAL_Delay(500);
    }
}







/*
#include "main.h"


#define MPU6050_ADDR (0x68 << 1)
#define PWR_MGMT_1 0x6B
#define ACCL_START 0x3B


uint8_t raw_data[14];


void mpu_wakeup(void) {
	uint8_t wake = 0x0;
	HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, PWR_MGMT_1, 1, &wake, 1, 100);
}


void read_raw_data(void) {
	HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, ACCL_START, 1, &raw_data, 14, 100);
}
*/
