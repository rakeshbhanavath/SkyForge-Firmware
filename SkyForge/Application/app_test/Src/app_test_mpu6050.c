/*==============================================================================
 * MPU6050 Driver Test Application
 *==============================================================================
 *
 * Test List
 *
 * TEST 1 : Accelerometer Range Configuration
 * TEST 2 : Gyroscope Data Test
 * TEST 3 : Sample Rate Divider
 * TEST 4 : Digital Low Pass Filter (DLPF)
 * TEST 5 : Clock Source Configuration
 * TEST 6 : Interrupt Configuration
 * TEST 7 : Sensor Calibration
 * TEST 8 : Self-Test
 * TEST 9 : FIFO
 * TEST 10: Motion Detection
 *
 * Enable ONLY one test at a time by changing
 *
 *      #if 1   -> Enable
 *      #if 0   -> Disable
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
/*==============================================================================
 * TEST 1 : MPU6050 Accelerometer Range Configuration
 *==============================================================================
 *
 * Objective
 * ---------
 * Configure the accelerometer full-scale range to ±8g, verify the
 * configuration register, and continuously read acceleration data.
 *
 * Expected UART Output
 * --------------------
 * Initializing MPU6050...
 * MPU6050 Initialization Successful
 *
 * Setting Accelerometer Range to +/-8g...
 * Accelerometer Range Configured
 *
 * Setting Gyroscope Range to +/-500 dps...
 * Gyroscope Range Configured
 *
 * Current Gyro Range : +/-500 dps
 * Current Accel Range : +/-8g
 *
 * Accel X : xxxx
 * Accel Y : xxxx
 * Accel Z : xxxx
 *
 *===========================================================================*/
#if 0

    MPU6050_Accel_t accel;
    MPU6050_AccelRange_t accelRange;
    MPU6050_GyroRange_t gyroRange;

    char message[128];

    const char *rangeStr = "Unknown";
    const char *gyroRangeStr = "Unknown";

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

#endif







    /*==============================================================================
     * TEST 2 : MPU6050 Gyroscope Data Test
     *==============================================================================
     *
     * Objective
     * ---------
     * Configure the gyroscope full-scale range to ±500 dps,
     * verify the configuration register, and continuously
     * read gyroscope data.
     *
     * Expected UART Output
     * --------------------
     *
     * Initializing MPU6050...
     * MPU6050 Initialization Successful
     *
     * Setting Gyroscope Range to +/-500 dps...
     * Gyroscope Range Configured
     *
     * Current Gyro Range : +/-500 dps
     *
     * Gyro X : xxxx
     * Gyro Y : xxxx
     * Gyro Z : xxxx
     *
     *===========================================================================*/

    #if 0

        MPU6050_Gyro_t gyro;
        MPU6050_GyroRange_t gyroRange;

        char message[128];

        const char *gyroRangeStr = "Unknown";

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
         * Read Gyroscope Data
         *--------------------------------------------------------*/

        while (1)
        {
            if (MPU6050_ReadGyro(&hi2c1,
                                 &gyro) == HAL_OK)
            {
                sprintf(message,
                        "\r\n"
                        "Gyro X : %6d\r\n"
                        "Gyro Y : %6d\r\n"
                        "Gyro Z : %6d\r\n",
                        gyro.x,
                        gyro.y,
                        gyro.z);

                BSP_UART_TransmitString(&huart2,
                                        message);
            }
            else
            {
                BSP_UART_TransmitString(&huart2,
                                        "Gyroscope Read Failed\r\n");
            }

            HAL_Delay(500);
        }

    #endif








        /*==============================================================================
         * TEST 3 : Sample Rate Divider Configuration
         *==============================================================================
         *
         * Objective
         * ---------
         * Verify the Sample Rate Divider register by writing different divider values
         * and reading them back.
         *
         *===========================================================================*/

        #if 0

            uint8_t divider;
            char message[128];

            const uint8_t dividerList[] =
            {
                0,
                7,
                39,
                79,
                255
            };

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
                for (uint8_t i = 0;
                     i < sizeof(dividerList);
                     i++)
                {
                    sprintf(message,
                            "\r\nSetting Sample Rate Divider : %u\r\n",
                            dividerList[i]);

                    BSP_UART_TransmitString(&huart2,
                                            message);

                    if (MPU6050_SetSampleRateDivider(&hi2c1,
                                                     dividerList[i]) != HAL_OK)
                    {
                        BSP_UART_TransmitString(&huart2,
                                                "Write Failed\r\n");

                        continue;
                    }

                    if (MPU6050_GetSampleRateDivider(&hi2c1,
                                                     &divider) != HAL_OK)
                    {
                        BSP_UART_TransmitString(&huart2,
                                                "Read Failed\r\n");

                        continue;
                    }

                    sprintf(message,
                            "Divider Read Back : %u\r\n",
                            divider);

                    BSP_UART_TransmitString(&huart2,
                                            message);

                    if (divider == dividerList[i])
                    {
                        BSP_UART_TransmitString(&huart2,
                                                "Verification PASSED\r\n");
                    }
                    else
                    {
                        BSP_UART_TransmitString(&huart2,
                                                "Verification FAILED\r\n");
                    }

                    HAL_Delay(2000);
                }
            }

        #endif



            /*==============================================================================
             * TEST 4 : Digital Low Pass Filter (DLPF)
             *==============================================================================
             *
             * Objective
             * ---------
             * Configure each supported DLPF bandwidth, read it back,
             * and verify the configuration.
             *
             *===========================================================================*/

            #if 0

                MPU6050_DLPF_t dlpf;
                char message[128];

                const MPU6050_DLPF_t dlpfList[] =
                {
                    MPU6050_DLPF_BW_260HZ,
                    MPU6050_DLPF_BW_184HZ,
                    MPU6050_DLPF_BW_94HZ,
                    MPU6050_DLPF_BW_44HZ,
                    MPU6050_DLPF_BW_21HZ,
                    MPU6050_DLPF_BW_10HZ,
                    MPU6050_DLPF_BW_5HZ
                };

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
                    for (uint8_t i = 0; i < (sizeof(dlpfList) / sizeof(dlpfList[0])); i++)
                    {
                        sprintf(message,
                                "\r\nSetting DLPF : %s\r\n",
                                MPU6050_GetDLPFString(dlpfList[i]));

                        BSP_UART_TransmitString(&huart2,
                                                message);

                        if (MPU6050_SetDLPF(&hi2c1,
                                            dlpfList[i]) != HAL_OK)
                        {
                            BSP_UART_TransmitString(&huart2,
                                                    "Write Failed\r\n");
                            continue;
                        }

                        if (MPU6050_GetDLPF(&hi2c1,
                                            &dlpf) != HAL_OK)
                        {
                            BSP_UART_TransmitString(&huart2,
                                                    "Read Failed\r\n");
                            continue;
                        }

                        sprintf(message,
                                "Read Back : %s\r\n",
                                MPU6050_GetDLPFString(dlpf));

                        BSP_UART_TransmitString(&huart2,
                                                message);

                        if (dlpf == dlpfList[i])
                        {
                            BSP_UART_TransmitString(&huart2,
                                                    "Verification PASSED\r\n");
                        }
                        else
                        {
                            BSP_UART_TransmitString(&huart2,
                                                    "Verification FAILED\r\n");
                        }

                        HAL_Delay(2000);
                    }
                }

            #endif

                /*==============================================================================
                 * TEST 5 : Clock Source Configuration
                 *==============================================================================
                 *
                 * Objective
                 * ---------
                 * Configure each supported clock source, read it back,
                 * and verify the configuration.
                 *
                 *===========================================================================*/

                #if 1

                    MPU6050_ClockSource_t clockSource;
                    char message[128];

                    const MPU6050_ClockSource_t clockList[] =
                    {
                        MPU6050_CLOCK_INTERNAL,
                        MPU6050_CLOCK_PLL_XGYRO,
                        MPU6050_CLOCK_PLL_YGYRO,
                        MPU6050_CLOCK_PLL_ZGYRO,
                        MPU6050_CLOCK_PLL_EXT32K,
                        MPU6050_CLOCK_PLL_EXT19M,
                        MPU6050_CLOCK_STOP
                    };

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
                        for (uint8_t i = 0;
                             i < (sizeof(clockList) / sizeof(clockList[0]));
                             i++)
                        {
                            sprintf(message,
                                    "\r\nSetting Clock Source : %s\r\n",
                                    MPU6050_GetClockSourceString(clockList[i]));

                            BSP_UART_TransmitString(&huart2,
                                                    message);

                            if (MPU6050_SetClockSource(&hi2c1,
                                                       clockList[i]) != HAL_OK)
                            {
                                BSP_UART_TransmitString(&huart2,
                                                        "Write Failed\r\n");
                                continue;
                            }

                            if (MPU6050_GetClockSource(&hi2c1,
                                                       &clockSource) != HAL_OK)
                            {
                                BSP_UART_TransmitString(&huart2,
                                                        "Read Failed\r\n");
                                continue;
                            }

                            sprintf(message,
                                    "Read Back : %s\r\n",
                                    MPU6050_GetClockSourceString(clockSource));

                            BSP_UART_TransmitString(&huart2,
                                                    message);

                            if (clockSource == clockList[i])
                            {
                                BSP_UART_TransmitString(&huart2,
                                                        "Verification PASSED\r\n");
                            }
                            else
                            {
                                BSP_UART_TransmitString(&huart2,
                                                        "Verification FAILED\r\n");
                            }

                            HAL_Delay(2000);
                        }
                    }

                #endif

}
