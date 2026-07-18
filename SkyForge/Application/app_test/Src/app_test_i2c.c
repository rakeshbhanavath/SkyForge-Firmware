/*==============================================================================
 * TEST 1 : I2C Bus Scan
 *==============================================================================
 *
 * Expected Output:
 *
 * SkyForge I2C Scanner
 * Scanning...
 * Found Device : 0x68
 * Scan Complete
 *
 *===========================================================================*/

#include "app_test_i2c.h"

#include "main.h"
#include "app_test_uart.h"
#include "bsp_uart.h"

#include <stdio.h>
#include <string.h>

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

void APP_Test_I2C(void)
{
	/*
    char message[64];

    HAL_UART_Transmit(&huart2,
                      (uint8_t *)"\r\nSkyForge I2C Scanner\r\n",
                      25,
                      HAL_MAX_DELAY);

    HAL_UART_Transmit(&huart2,
                      (uint8_t *)"Scanning...\r\n",
                      13,
                      HAL_MAX_DELAY);

    for (uint8_t address = 1; address < 128; address++)
    {
        if (HAL_I2C_IsDeviceReady(&hi2c1,
                                  address << 1,
                                  2,
                                  10) == HAL_OK)
        {
            sprintf(message,
                    "Found device at 0x%02X\r\n",
                    address);

            HAL_UART_Transmit(&huart2,
                              (uint8_t *)message,
                              strlen(message),
                              HAL_MAX_DELAY);
        }
    }

    HAL_UART_Transmit(&huart2,
                      (uint8_t *)"Scan Complete\r\n",
                      15,
                      HAL_MAX_DELAY);

    HAL_Delay(3000);


    */
/*
	 char message[64];

	    BSP_UART_TransmitString(&huart2,
	                            "\r\nSkyForge I2C Scanner\r\n");

	    BSP_UART_TransmitString(&huart2,
	                            "Scanning...\r\n");

	    for (uint8_t address = 1; address < 128; address++)
	    {
	        if (HAL_I2C_IsDeviceReady(&hi2c1,
	                                  address << 1,
	                                  2,
	                                  10) == HAL_OK)
	        {
	            sprintf(message,
	                    "Found Device : 0x%02X\r\n",
	                    address);

	            BSP_UART_TransmitString(&huart2,
	                                    message);
	        }
	    }

	    BSP_UART_TransmitString(&huart2,
	                            "Scan Complete\r\n");

	    HAL_Delay(3000);
	    */


	uint8_t check = 0;

	if (HAL_I2C_Mem_Read(&hi2c1,
	                     (0x68 << 1),
	                     0x75,
	                     I2C_MEMADD_SIZE_8BIT,
	                     &check,
	                     1,
	                     1000) == HAL_OK)
	{
	    char msg[32];

	    sprintf(msg, "WHO_AM_I = 0x%02X\r\n", check);

	    BSP_UART_TransmitString(&huart2, msg);
	}
	else
	{
	    BSP_UART_TransmitString(&huart2,
	                            "Read Failed\r\n");
	}

	HAL_Delay(1000);
}




