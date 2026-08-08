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

                #if 0

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


                    /*==============================================================================
                     * TEST 6 : Data Ready Interrupt Configuration
                     *==============================================================================
                     *
                     * Objective
                     * ---------
                     * Enable the DATA_RDY interrupt, verify that it is enabled,
                     * then disable it and verify that it is disabled.
                     *
                     *===========================================================================*/

                    #if 0

                        uint8_t status;
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
                            /*-----------------------------------------------------
                             * Enable Interrupt
                             *----------------------------------------------------*/

                            BSP_UART_TransmitString(&huart2,
                                                    "\r\nEnabling DATA_RDY Interrupt...\r\n");

                            if (MPU6050_EnableDataReadyInterrupt(&hi2c1) != HAL_OK)
                            {
                                BSP_UART_TransmitString(&huart2,
                                                        "Enable Failed\r\n");

                                continue;
                            }

                            if (MPU6050_GetInterruptEnable(&hi2c1,
                                                           &status) != HAL_OK)
                            {
                                BSP_UART_TransmitString(&huart2,
                                                        "Read Failed\r\n");

                                continue;
                            }

                            sprintf(message,
                                    "INT_ENABLE = 0x%02X\r\n",
                                    status);

                            BSP_UART_TransmitString(&huart2,
                                                    message);

                            uint8_t enabled;

                            if (MPU6050_IsDataReadyInterruptEnabled(&hi2c1,
                                                                    &enabled) != HAL_OK)
                            {
                                BSP_UART_TransmitString(&huart2,
                                                        "Read Failed\r\n");

                                continue;
                            }

                            if (enabled)

                            HAL_Delay(2000);

                            /*-----------------------------------------------------
                             * Disable Interrupt
                             *----------------------------------------------------*/

                            BSP_UART_TransmitString(&huart2,
                                                    "\r\nDisabling DATA_RDY Interrupt...\r\n");

                            if (MPU6050_DisableDataReadyInterrupt(&hi2c1) != HAL_OK)
                            {
                                BSP_UART_TransmitString(&huart2,
                                                        "Disable Failed\r\n");

                                continue;
                            }

                            if (MPU6050_GetInterruptEnable(&hi2c1,
                                                           &status) != HAL_OK)
                            {
                                BSP_UART_TransmitString(&huart2,
                                                        "Read Failed\r\n");

                                continue;
                            }

                            sprintf(message,
                                    "INT_ENABLE = 0x%02X\r\n",
                                    status);

                            BSP_UART_TransmitString(&huart2,
                                                    message);

                            if (MPU6050_IsDataReadyInterruptEnabled(&hi2c1,
                                                                    &enabled) != HAL_OK)
                            {
                                BSP_UART_TransmitString(&huart2,
                                                        "Read Failed\r\n");

                                continue;
                            }

                            if (!enabled)
                            HAL_Delay(2000);
                        }

                    #endif



                        /*==============================================================================
                         * TEST 7 : FIFO Enable / Disable
                         *==============================================================================
                         *
                         * Objective
                         * ---------
                         * Enable the FIFO, verify it is enabled,
                         * disable the FIFO, and verify it is disabled.
                         *
                         *===========================================================================*/

                        #if 0

                            uint8_t enabled;

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
                                /*---------------------------------------------------------
                                 * Reset FIFO
                                 *--------------------------------------------------------*/

                                BSP_UART_TransmitString(&huart2,
                                                        "\r\nResetting FIFO...\r\n");

                                if (MPU6050_ResetFIFO(&hi2c1) != HAL_OK)
                                {
                                    BSP_UART_TransmitString(&huart2,
                                                            "FIFO Reset Failed\r\n");

                                    continue;
                                }

                                BSP_UART_TransmitString(&huart2,
                                                        "FIFO Reset Successful\r\n");

                                HAL_Delay(500);

                                /*---------------------------------------------------------
                                 * Enable FIFO
                                 *--------------------------------------------------------*/

                                BSP_UART_TransmitString(&huart2,
                                                        "Enabling FIFO...\r\n");

                                if (MPU6050_EnableFIFO(&hi2c1) != HAL_OK)
                                {
                                    BSP_UART_TransmitString(&huart2,
                                                            "FIFO Enable Failed\r\n");

                                    continue;
                                }

                                if (MPU6050_GetFIFOEnable(&hi2c1,
                                                          &enabled) != HAL_OK)
                                {
                                    BSP_UART_TransmitString(&huart2,
                                                            "Verification Failed\r\n");

                                    continue;
                                }

                                if (enabled)
                                {
                                    BSP_UART_TransmitString(&huart2,
                                                            "FIFO Enabled : PASSED\r\n");
                                }
                                else
                                {
                                    BSP_UART_TransmitString(&huart2,
                                                            "FIFO Enabled : FAILED\r\n");
                                }

                                HAL_Delay(2000);

                                /*---------------------------------------------------------
                                 * Disable FIFO
                                 *--------------------------------------------------------*/

                                BSP_UART_TransmitString(&huart2,
                                                        "\r\nDisabling FIFO...\r\n");

                                if (MPU6050_DisableFIFO(&hi2c1) != HAL_OK)
                                {
                                    BSP_UART_TransmitString(&huart2,
                                                            "FIFO Disable Failed\r\n");

                                    continue;
                                }

                                if (MPU6050_GetFIFOEnable(&hi2c1,
                                                          &enabled) != HAL_OK)
                                {
                                    BSP_UART_TransmitString(&huart2,
                                                            "Verification Failed\r\n");

                                    continue;
                                }

                                if (!enabled)
                                {
                                    BSP_UART_TransmitString(&huart2,
                                                            "FIFO Disabled : PASSED\r\n");
                                }
                                else
                                {
                                    BSP_UART_TransmitString(&huart2,
                                                            "FIFO Disabled : FAILED\r\n");
                                }

                                HAL_Delay(2000);
                            }

                        #endif


                            /*==============================================================================
                             * TEST 7.2 : Accelerometer FIFO Configuration
                             *==============================================================================
                             *
                             * Objective
                             * ---------
                             * Enable Accelerometer FIFO,
                             * verify it,
                             * disable it,
                             * verify it.
                             *
                             *===========================================================================*/

                            #if 0

                                uint8_t enabled;

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
                                    /*---------------------------------------------------------
                                     * Enable Accelerometer FIFO
                                     *--------------------------------------------------------*/

                                    BSP_UART_TransmitString(&huart2,
                                                            "\r\nEnabling Accelerometer FIFO...\r\n");

                                    if (MPU6050_EnableAccelFIFO(&hi2c1) != HAL_OK)
                                    {
                                        BSP_UART_TransmitString(&huart2,
                                                                "Enable Failed\r\n");

                                        continue;
                                    }

                                    if (MPU6050_IsAccelFIFOEnabled(&hi2c1,
                                                                   &enabled) != HAL_OK)
                                    {
                                        BSP_UART_TransmitString(&huart2,
                                                                "Verification Failed\r\n");

                                        continue;
                                    }

                                    if (enabled)
                                    {
                                        BSP_UART_TransmitString(&huart2,
                                                                "Accelerometer FIFO : PASSED\r\n");
                                    }
                                    else
                                    {
                                        BSP_UART_TransmitString(&huart2,
                                                                "Accelerometer FIFO : FAILED\r\n");
                                    }

                                    HAL_Delay(2000);

                                    /*---------------------------------------------------------
                                     * Disable Accelerometer FIFO
                                     *--------------------------------------------------------*/

                                    BSP_UART_TransmitString(&huart2,
                                                            "\r\nDisabling Accelerometer FIFO...\r\n");

                                    if (MPU6050_DisableAccelFIFO(&hi2c1) != HAL_OK)
                                    {
                                        BSP_UART_TransmitString(&huart2,
                                                                "Disable Failed\r\n");

                                        continue;
                                    }

                                    if (MPU6050_IsAccelFIFOEnabled(&hi2c1,
                                                                   &enabled) != HAL_OK)
                                    {
                                        BSP_UART_TransmitString(&huart2,
                                                                "Verification Failed\r\n");

                                        continue;
                                    }

                                    if (!enabled)
                                    {
                                        BSP_UART_TransmitString(&huart2,
                                                                "Accelerometer FIFO : PASSED\r\n");
                                    }
                                    else
                                    {
                                        BSP_UART_TransmitString(&huart2,
                                                                "Accelerometer FIFO : FAILED\r\n");
                                    }

                                    HAL_Delay(2000);
                                }

                            #endif





                                /*==============================================================================
                                 * TEST 7.3 : Gyroscope FIFO Configuration
                                 *==============================================================================
                                 *
                                 * Objective
                                 * ---------
                                 * Verify X, Y and Z Gyroscope FIFO Configuration.
                                 *
                                 *===========================================================================*/

                                #if 0

                                    uint8_t enabled;

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
                                        /*---------------------------------------------------------
                                         * X Gyroscope FIFO
                                         *--------------------------------------------------------*/

                                        BSP_UART_TransmitString(&huart2,
                                                                "\r\nEnabling X Gyroscope FIFO...\r\n");

                                        MPU6050_EnableGyroXFIFO(&hi2c1);

                                        MPU6050_IsGyroXFIFOEnabled(&hi2c1,
                                                                   &enabled);

                                        if (enabled)
                                        {
                                            BSP_UART_TransmitString(&huart2,
                                                                    "X Gyroscope FIFO : PASSED\r\n");
                                        }
                                        else
                                        {
                                            BSP_UART_TransmitString(&huart2,
                                                                    "X Gyroscope FIFO : FAILED\r\n");
                                        }

                                        HAL_Delay(1000);

                                        BSP_UART_TransmitString(&huart2,
                                                                "Disabling X Gyroscope FIFO...\r\n");

                                        MPU6050_DisableGyroXFIFO(&hi2c1);

                                        MPU6050_IsGyroXFIFOEnabled(&hi2c1,
                                                                   &enabled);

                                        if (!enabled)
                                        {
                                            BSP_UART_TransmitString(&huart2,
                                                                    "X Gyroscope FIFO : PASSED\r\n");
                                        }
                                        else
                                        {
                                            BSP_UART_TransmitString(&huart2,
                                                                    "X Gyroscope FIFO : FAILED\r\n");
                                        }

                                        HAL_Delay(1000);

                                        /*---------------------------------------------------------
                                         * Y Gyroscope FIFO
                                         *--------------------------------------------------------*/

                                        BSP_UART_TransmitString(&huart2,
                                                                "\r\nEnabling Y Gyroscope FIFO...\r\n");

                                        MPU6050_EnableGyroYFIFO(&hi2c1);

                                        MPU6050_IsGyroYFIFOEnabled(&hi2c1,
                                                                   &enabled);

                                        if (enabled)
                                        {
                                            BSP_UART_TransmitString(&huart2,
                                                                    "Y Gyroscope FIFO : PASSED\r\n");
                                        }
                                        else
                                        {
                                            BSP_UART_TransmitString(&huart2,
                                                                    "Y Gyroscope FIFO : FAILED\r\n");
                                        }

                                        HAL_Delay(1000);

                                        BSP_UART_TransmitString(&huart2,
                                                                "Disabling Y Gyroscope FIFO...\r\n");

                                        MPU6050_DisableGyroYFIFO(&hi2c1);

                                        MPU6050_IsGyroYFIFOEnabled(&hi2c1,
                                                                   &enabled);

                                        if (!enabled)
                                        {
                                            BSP_UART_TransmitString(&huart2,
                                                                    "Y Gyroscope FIFO : PASSED\r\n");
                                        }
                                        else
                                        {
                                            BSP_UART_TransmitString(&huart2,
                                                                    "Y Gyroscope FIFO : FAILED\r\n");
                                        }

                                        HAL_Delay(1000);

                                        /*---------------------------------------------------------
                                         * Z Gyroscope FIFO
                                         *--------------------------------------------------------*/

                                        BSP_UART_TransmitString(&huart2,
                                                                "\r\nEnabling Z Gyroscope FIFO...\r\n");

                                        MPU6050_EnableGyroZFIFO(&hi2c1);

                                        MPU6050_IsGyroZFIFOEnabled(&hi2c1,
                                                                   &enabled);

                                        if (enabled)
                                        {
                                            BSP_UART_TransmitString(&huart2,
                                                                    "Z Gyroscope FIFO : PASSED\r\n");
                                        }
                                        else
                                        {
                                            BSP_UART_TransmitString(&huart2,
                                                                    "Z Gyroscope FIFO : FAILED\r\n");
                                        }

                                        HAL_Delay(1000);

                                        BSP_UART_TransmitString(&huart2,
                                                                "Disabling Z Gyroscope FIFO...\r\n");

                                        MPU6050_DisableGyroZFIFO(&hi2c1);

                                        MPU6050_IsGyroZFIFOEnabled(&hi2c1,
                                                                   &enabled);

                                        if (!enabled)
                                        {
                                            BSP_UART_TransmitString(&huart2,
                                                                    "Z Gyroscope FIFO : PASSED\r\n");
                                        }
                                        else
                                        {
                                            BSP_UART_TransmitString(&huart2,
                                                                    "Z Gyroscope FIFO : FAILED\r\n");
                                        }

                                        HAL_Delay(2000);
                                    }

                                #endif










                                    /*==============================================================================
                                     * TEST 7.4 : Temperature FIFO Configuration
                                     *==============================================================================
                                     *
                                     * Objective
                                     * ---------
                                     * Verify Temperature FIFO configuration.
                                     *
                                     *===========================================================================*/

                                    #if 0

                                        uint8_t enabled;

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
                                            /*---------------------------------------------------------
                                             * Enable Temperature FIFO
                                             *--------------------------------------------------------*/

                                            BSP_UART_TransmitString(&huart2,
                                                                    "\r\nEnabling Temperature FIFO...\r\n");

                                            if (MPU6050_EnableTempFIFO(&hi2c1) != HAL_OK)
                                            {
                                                BSP_UART_TransmitString(&huart2,
                                                                        "Enable Failed\r\n");

                                                continue;
                                            }

                                            if (MPU6050_IsTempFIFOEnabled(&hi2c1,
                                                                          &enabled) != HAL_OK)
                                            {
                                                BSP_UART_TransmitString(&huart2,
                                                                        "Verification Failed\r\n");

                                                continue;
                                            }

                                            if (enabled)
                                            {
                                                BSP_UART_TransmitString(&huart2,
                                                                        "Temperature FIFO : PASSED\r\n");
                                            }
                                            else
                                            {
                                                BSP_UART_TransmitString(&huart2,
                                                                        "Temperature FIFO : FAILED\r\n");
                                            }

                                            HAL_Delay(1000);

                                            /*---------------------------------------------------------
                                             * Disable Temperature FIFO
                                             *--------------------------------------------------------*/

                                            BSP_UART_TransmitString(&huart2,
                                                                    "\r\nDisabling Temperature FIFO...\r\n");

                                            if (MPU6050_DisableTempFIFO(&hi2c1) != HAL_OK)
                                            {
                                                BSP_UART_TransmitString(&huart2,
                                                                        "Disable Failed\r\n");

                                                continue;
                                            }

                                            if (MPU6050_IsTempFIFOEnabled(&hi2c1,
                                                                          &enabled) != HAL_OK)
                                            {
                                                BSP_UART_TransmitString(&huart2,
                                                                        "Verification Failed\r\n");

                                                continue;
                                            }

                                            if (!enabled)
                                            {
                                                BSP_UART_TransmitString(&huart2,
                                                                        "Temperature FIFO : PASSED\r\n");
                                            }
                                            else
                                            {
                                                BSP_UART_TransmitString(&huart2,
                                                                        "Temperature FIFO : FAILED\r\n");
                                            }

                                            HAL_Delay(2000);
                                        }

                                    #endif




                                        /*==============================================================================
                                         * TEST 7.5 : FIFO Count
                                         *==============================================================================
                                         *
                                         * Objective
                                         * ---------
                                         * Read and display the current FIFO byte count.
                                         *
                                         *===========================================================================*/

                                        #if 0

                                            uint16_t fifoCount;
                                            char message[64];

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
                                             * Enable FIFO
                                             *--------------------------------------------------------*/

                                            MPU6050_EnableFIFO(&hi2c1);

                                            MPU6050_EnableAccelFIFO(&hi2c1);

                                            MPU6050_EnableGyroXFIFO(&hi2c1);
                                            MPU6050_EnableGyroYFIFO(&hi2c1);
                                            MPU6050_EnableGyroZFIFO(&hi2c1);

                                            MPU6050_EnableTempFIFO(&hi2c1);

                                            while (1)
                                            {
                                                if (MPU6050_GetFIFOCount(&hi2c1,
                                                                         &fifoCount) == HAL_OK)
                                                {
                                                    sprintf(message,
                                                            "\r\nFIFO Count : %u bytes\r\n",
                                                            fifoCount);

                                                    BSP_UART_TransmitString(&huart2,
                                                                            message);
                                                }
                                                else
                                                {
                                                    BSP_UART_TransmitString(&huart2,
                                                                            "FIFO Count Read Failed\r\n");
                                                }

                                                HAL_Delay(1000);
                                            }

                                        #endif


                                            /*==============================================================================
                                             * TEST 7.6 : FIFO Read Verification
                                             *==============================================================================
                                             *
                                             * Objective
                                             * ---------
                                             * Verify FIFO read operation by checking that FIFO count
                                             * decreases after reading one byte.
                                             *
                                             *===========================================================================*/

                                            #if 0

                                                uint16_t fifoCountBefore;
                                                uint16_t fifoCountAfter;

                                                uint8_t fifoData;

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


                                                /*---------------------------------------------------------
                                                 * Enable FIFO
                                                 *--------------------------------------------------------*/

                                                MPU6050_EnableFIFO(&hi2c1);

                                                MPU6050_EnableAccelFIFO(&hi2c1);

                                                MPU6050_EnableGyroXFIFO(&hi2c1);
                                                MPU6050_EnableGyroYFIFO(&hi2c1);
                                                MPU6050_EnableGyroZFIFO(&hi2c1);

                                                MPU6050_EnableTempFIFO(&hi2c1);

                                                HAL_Delay(500);

                                                /* Stop filling FIFO */

                                                MPU6050_DisableAccelFIFO(&hi2c1);

                                                MPU6050_DisableGyroXFIFO(&hi2c1);
                                                MPU6050_DisableGyroYFIFO(&hi2c1);
                                                MPU6050_DisableGyroZFIFO(&hi2c1);

                                                MPU6050_DisableTempFIFO(&hi2c1);

                                                while (1)
                                                {
                                                    /*---------------------------------------------------------
                                                     * FIFO Count Before Read
                                                     *--------------------------------------------------------*/

                                                    MPU6050_GetFIFOCount(&hi2c1,
                                                                         &fifoCountBefore);

                                                    sprintf(message,
                                                            "\r\nFIFO Count Before : %u bytes\r\n",
                                                            fifoCountBefore);

                                                    BSP_UART_TransmitString(&huart2,
                                                                            message);

                                                    /*---------------------------------------------------------
                                                     * Read One FIFO Byte
                                                     *--------------------------------------------------------*/

                                                    if (MPU6050_ReadFIFO(&hi2c1,
                                                                         &fifoData) != HAL_OK)
                                                    {
                                                        BSP_UART_TransmitString(&huart2,
                                                                                "FIFO Read Failed\r\n");

                                                        continue;
                                                    }

                                                    sprintf(message,
                                                            "Read Byte         : 0x%02X\r\n",
                                                            fifoData);

                                                    BSP_UART_TransmitString(&huart2,
                                                                            message);

                                                    /*---------------------------------------------------------
                                                     * FIFO Count After Read
                                                     *--------------------------------------------------------*/

                                                    MPU6050_GetFIFOCount(&hi2c1,
                                                                         &fifoCountAfter);

                                                    sprintf(message,
                                                            "FIFO Count After  : %u bytes\r\n",
                                                            fifoCountAfter);

                                                    BSP_UART_TransmitString(&huart2,
                                                                            message);

                                                    /*---------------------------------------------------------
                                                     * Verification
                                                     *--------------------------------------------------------*/

                                                    if (fifoCountAfter == (fifoCountBefore - 1))
                                                    {
                                                        BSP_UART_TransmitString(&huart2,
                                                                                "Verification : PASSED\r\n");
                                                    }
                                                    else
                                                    {
                                                        BSP_UART_TransmitString(&huart2,
                                                                                "Verification : FAILED\r\n");
                                                    }

                                                    BSP_UART_TransmitString(&huart2,
                                                                            "--------------------------------\r\n");

                                                    HAL_Delay(1000);
                                                }

                                            #endif



                                                /*==============================================================================
                                                 * TEST 7.7 : FIFO Buffer Read Verification
                                                 *==============================================================================
                                                 *
                                                 * Objective
                                                 * ---------
                                                 * Verify reading multiple bytes from the FIFO.
                                                 *
                                                 *===========================================================================*/

                                                #if 0

                                                    uint16_t fifoCountBefore;
                                                    uint16_t fifoCountAfter;

                                                    uint8_t fifoBuffer[16];

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

                                                    /*---------------------------------------------------------
                                                     * Enable FIFO
                                                     *--------------------------------------------------------*/

                                                    MPU6050_EnableFIFO(&hi2c1);

                                                    MPU6050_EnableAccelFIFO(&hi2c1);

                                                    MPU6050_EnableGyroXFIFO(&hi2c1);
                                                    MPU6050_EnableGyroYFIFO(&hi2c1);
                                                    MPU6050_EnableGyroZFIFO(&hi2c1);

                                                    MPU6050_EnableTempFIFO(&hi2c1);

                                                    HAL_Delay(500);

                                                    /*---------------------------------------------------------
                                                     * Stop FIFO filling
                                                     *--------------------------------------------------------*/

                                                    MPU6050_DisableAccelFIFO(&hi2c1);

                                                    MPU6050_DisableGyroXFIFO(&hi2c1);
                                                    MPU6050_DisableGyroYFIFO(&hi2c1);
                                                    MPU6050_DisableGyroZFIFO(&hi2c1);

                                                    MPU6050_DisableTempFIFO(&hi2c1);

                                                    while (1)
                                                    {
                                                        /*---------------------------------------------------------
                                                         * FIFO Count Before
                                                         *--------------------------------------------------------*/

                                                        MPU6050_GetFIFOCount(&hi2c1,
                                                                             &fifoCountBefore);

                                                        sprintf(message,
                                                                "\r\nFIFO Count Before : %u bytes\r\n",
                                                                fifoCountBefore);

                                                        BSP_UART_TransmitString(&huart2,
                                                                                message);

                                                        /*---------------------------------------------------------
                                                         * Read 16 Bytes
                                                         *--------------------------------------------------------*/

                                                        if (MPU6050_ReadFIFOBuffer(&hi2c1,
                                                                                   fifoBuffer,
                                                                                   sizeof(fifoBuffer)) != HAL_OK)
                                                        {
                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "FIFO Buffer Read Failed\r\n");

                                                            continue;
                                                        }

                                                        BSP_UART_TransmitString(&huart2,
                                                                                "FIFO Data : ");

                                                        for (uint8_t i = 0; i < sizeof(fifoBuffer); i++)
                                                        {
                                                            sprintf(message,
                                                                    "%02X ",
                                                                    fifoBuffer[i]);

                                                            BSP_UART_TransmitString(&huart2,
                                                                                    message);
                                                        }

                                                        BSP_UART_TransmitString(&huart2,
                                                                                "\r\n");

                                                        /*---------------------------------------------------------
                                                         * FIFO Count After
                                                         *--------------------------------------------------------*/

                                                        MPU6050_GetFIFOCount(&hi2c1,
                                                                             &fifoCountAfter);

                                                        sprintf(message,
                                                                "FIFO Count After  : %u bytes\r\n",
                                                                fifoCountAfter);

                                                        BSP_UART_TransmitString(&huart2,
                                                                                message);

                                                        /*---------------------------------------------------------
                                                         * Verification
                                                         *--------------------------------------------------------*/

                                                        if (fifoCountAfter == (fifoCountBefore - sizeof(fifoBuffer)))
                                                        {
                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "Verification : PASSED\r\n");
                                                        }
                                                        else
                                                        {
                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "Verification : FAILED\r\n");
                                                        }

                                                        BSP_UART_TransmitString(&huart2,
                                                                                "--------------------------------\r\n");

                                                        HAL_Delay(1000);
                                                    }

                                                #endif



                                                    /*==============================================================================
                                                     * TEST 7.9 : FIFO Overflow and Raw Packet Diagnostic
                                                     *==============================================================================
                                                     *
                                                     * Objective
                                                     * ---------
                                                     * 1. Verify FIFO overflow status.
                                                     * 2. Verify complete 14-byte FIFO packet reads.
                                                     * 3. Inspect raw FIFO packet bytes.
                                                     * 4. Verify packet data changes when the sensor is moved.
                                                     *
                                                     * Packet Format
                                                     * -------------
                                                     *
                                                     * Byte  0-1   : Accel X
                                                     * Byte  2-3   : Accel Y
                                                     * Byte  4-5   : Accel Z
                                                     * Byte  6-7   : Temperature
                                                     * Byte  8-9   : Gyro X
                                                     * Byte 10-11  : Gyro Y
                                                     * Byte 12-13  : Gyro Z
                                                     *
                                                     * Total       : 14 bytes
                                                     *
                                                     *===========================================================================*/

                                                    #if 0

                                                        uint16_t fifoCount;

                                                        uint8_t intStatus;

                                                        uint8_t fifoBuffer[14];

                                                        char message[128];

                                                        BSP_UART_TransmitString(&huart2,
                                                                                "\r\n================================\r\n");

                                                        BSP_UART_TransmitString(&huart2,
                                                                                "FIFO Diagnostic Test\r\n");

                                                        BSP_UART_TransmitString(&huart2,
                                                                                "================================\r\n");


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


                                                        /*---------------------------------------------------------
                                                         * Configure Sampling
                                                         *--------------------------------------------------------*/

                                                        if (MPU6050_SetDLPF(&hi2c1,
                                                                            MPU6050_DLPF_BW_94HZ) != HAL_OK)
                                                        {
                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "DLPF Configuration Failed\r\n");

                                                            while (1);
                                                        }

                                                        if (MPU6050_SetSampleRateDivider(&hi2c1,
                                                                                         9U) != HAL_OK)
                                                        {
                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "Sample Rate Configuration Failed\r\n");

                                                            while (1);
                                                        }

                                                        BSP_UART_TransmitString(&huart2,
                                                                                "Sampling Configuration Successful\r\n");


                                                        BSP_UART_TransmitString(&huart2,
                                                                                "MPU6050 Initialization Successful\r\n");


                                                        /*---------------------------------------------------------
                                                         * Enable FIFO
                                                         *--------------------------------------------------------*/

                                                        if (MPU6050_EnableFIFO(&hi2c1) != HAL_OK)
                                                        {
                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "FIFO Enable Failed\r\n");

                                                            while (1);
                                                        }


                                                        /*---------------------------------------------------------
                                                         * Enable FIFO Sources
                                                         *--------------------------------------------------------*/

                                                        if (MPU6050_EnableAccelFIFO(&hi2c1) != HAL_OK)
                                                        {
                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "Accel FIFO Enable Failed\r\n");

                                                            while (1);
                                                        }

                                                        if (MPU6050_EnableGyroXFIFO(&hi2c1) != HAL_OK)
                                                        {
                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "Gyro X FIFO Enable Failed\r\n");

                                                            while (1);
                                                        }

                                                        if (MPU6050_EnableGyroYFIFO(&hi2c1) != HAL_OK)
                                                        {
                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "Gyro Y FIFO Enable Failed\r\n");

                                                            while (1);
                                                        }

                                                        if (MPU6050_EnableGyroZFIFO(&hi2c1) != HAL_OK)
                                                        {
                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "Gyro Z FIFO Enable Failed\r\n");

                                                            while (1);
                                                        }

                                                        if (MPU6050_EnableTempFIFO(&hi2c1) != HAL_OK)
                                                        {
                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "Temperature FIFO Enable Failed\r\n");

                                                            while (1);
                                                        }


                                                        /*---------------------------------------------------------
                                                         * Reset FIFO
                                                         *--------------------------------------------------------*/

                                                        if (MPU6050_ResetFIFO(&hi2c1) != HAL_OK)
                                                        {
                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "FIFO Reset Failed\r\n");

                                                            while (1);
                                                        }

                                                        BSP_UART_TransmitString(&huart2,
                                                                                "FIFO Reset Successful\r\n");


                                                        /*---------------------------------------------------------
                                                         * Allow FIFO to collect some samples
                                                         *--------------------------------------------------------*/

                                                        HAL_Delay(50);


                                                        while (1)
                                                        {
                                                            /*-----------------------------------------------------
                                                             * Read FIFO Count
                                                             *----------------------------------------------------*/

                                                            if (MPU6050_GetFIFOCount(&hi2c1,
                                                                                     &fifoCount) != HAL_OK)
                                                            {
                                                                BSP_UART_TransmitString(&huart2,
                                                                                        "FIFO Count Read Failed\r\n");

                                                                continue;
                                                            }


                                                            /*-----------------------------------------------------
                                                             * Read Interrupt Status
                                                             *----------------------------------------------------*/

                                                            if (MPU6050_GetInterruptStatus(&hi2c1,
                                                                                           &intStatus) != HAL_OK)
                                                            {
                                                                BSP_UART_TransmitString(&huart2,
                                                                                        "INT_STATUS Read Failed\r\n");

                                                                continue;
                                                            }


                                                            /*-----------------------------------------------------
                                                             * Check FIFO Overflow
                                                             *----------------------------------------------------*/

                                                            if (intStatus & MPU6050_FIFO_OFLOW_INT_Msk)
                                                            {
                                                                BSP_UART_TransmitString(&huart2,
                                                                                        "\r\n*** FIFO OVERFLOW DETECTED ***\r\n");

                                                                sprintf(message,
                                                                        "FIFO Count : %u bytes\r\n",
                                                                        fifoCount);

                                                                BSP_UART_TransmitString(&huart2,
                                                                                        message);

                                                                /*---------------------------------------------
                                                                 * Clear FIFO after overflow
                                                                 *--------------------------------------------*/

                                                                MPU6050_ResetFIFO(&hi2c1);

                                                                HAL_Delay(10);

                                                                continue;
                                                            }


                                                            /*-----------------------------------------------------
                                                             * Need One Complete Packet
                                                             *----------------------------------------------------*/

                                                            if (fifoCount < 14U)
                                                            {
                                                                HAL_Delay(1);

                                                                continue;
                                                            }


                                                            /*-----------------------------------------------------
                                                             * Read Exactly 14 Raw Bytes
                                                             *----------------------------------------------------*/

                                                            if (MPU6050_ReadFIFOBuffer(&hi2c1,
                                                                                       fifoBuffer,
                                                                                       14U) != HAL_OK)
                                                            {
                                                                BSP_UART_TransmitString(&huart2,
                                                                                        "FIFO Raw Read Failed\r\n");

                                                                continue;
                                                            }


                                                            /*-----------------------------------------------------
                                                             * Print FIFO Count
                                                             *----------------------------------------------------*/

                                                            sprintf(message,
                                                                    "\r\nFIFO Count : %u bytes\r\n",
                                                                    fifoCount);

                                                            BSP_UART_TransmitString(&huart2,
                                                                                    message);


                                                            /*-----------------------------------------------------
                                                             * Print Raw FIFO Bytes
                                                             *----------------------------------------------------*/

                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "FIFO RAW : ");

                                                            for (uint8_t i = 0; i < 14U; i++)
                                                            {
                                                                sprintf(message,
                                                                        "%02X ",
                                                                        fifoBuffer[i]);

                                                                BSP_UART_TransmitString(&huart2,
                                                                                        message);
                                                            }

                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "\r\n");


                                                            /*-----------------------------------------------------
                                                             * Print Packet Boundaries
                                                             *----------------------------------------------------*/

                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "Format  : "
                                                                                    "AX AY AZ TEMP GX GY GZ\r\n");


                                                            /*-----------------------------------------------------
                                                             * Delay Before Next Diagnostic Packet
                                                             *
                                                             * Keep this short so FIFO does not fill.
                                                             *----------------------------------------------------*/

                                                            HAL_Delay(50);
                                                        }

                                                    #endif


                                                        /*==============================================================================
                                                         * TEST 7.10 : High-Speed FIFO Drain Verification
                                                         *==============================================================================
                                                         *
                                                         * Objective
                                                         * ---------
                                                         * Continuously drain complete 14-byte FIFO packets without allowing UART
                                                         * printing to become the bottleneck.
                                                         *
                                                         * One FIFO packet:
                                                         *
                                                         *   Accelerometer : 6 bytes
                                                         *   Temperature   : 2 bytes
                                                         *   Gyroscope     : 6 bytes
                                                         *   --------------------------
                                                         *   Total         : 14 bytes
                                                         *
                                                         * UART output is generated only once every 100 packets.
                                                         *
                                                         *===========================================================================*/

                                                        #if 0

                                                            uint16_t fifoCount;

                                                            uint8_t intStatus;

                                                            uint8_t fifoBuffer[14];

                                                            uint32_t packetCount = 0U;
                                                            uint32_t overflowCount = 0U;

                                                            char message[128];


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
                                                             * Configure Sampling
                                                             *
                                                             * DLPF     : 94 Hz
                                                             * Sample   : 100 Hz
                                                             * Divider  : 9
                                                             *
                                                             * Sample Rate = 1000 / (1 + 9)
                                                             *             = 100 Hz
                                                             *--------------------------------------------------------*/

                                                            if (MPU6050_SetDLPF(&hi2c1,
                                                                                MPU6050_DLPF_BW_94HZ) != HAL_OK)
                                                            {
                                                                BSP_UART_TransmitString(&huart2,
                                                                                        "DLPF Configuration Failed\r\n");

                                                                while (1);
                                                            }


                                                            if (MPU6050_SetSampleRateDivider(&hi2c1,
                                                                                             9U) != HAL_OK)
                                                            {
                                                                BSP_UART_TransmitString(&huart2,
                                                                                        "Sample Rate Configuration Failed\r\n");

                                                                while (1);
                                                            }


                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "Sampling Configuration Successful\r\n");


                                                            /*---------------------------------------------------------
                                                             * Enable FIFO
                                                             *--------------------------------------------------------*/

                                                            if (MPU6050_EnableFIFO(&hi2c1) != HAL_OK)
                                                            {
                                                                BSP_UART_TransmitString(&huart2,
                                                                                        "FIFO Enable Failed\r\n");

                                                                while (1);
                                                            }


                                                            /*---------------------------------------------------------
                                                             * Enable FIFO Sources
                                                             *--------------------------------------------------------*/

                                                            if (MPU6050_EnableAccelFIFO(&hi2c1) != HAL_OK)
                                                            {
                                                                BSP_UART_TransmitString(&huart2,
                                                                                        "Accel FIFO Enable Failed\r\n");

                                                                while (1);
                                                            }

                                                            if (MPU6050_EnableGyroXFIFO(&hi2c1) != HAL_OK)
                                                            {
                                                                BSP_UART_TransmitString(&huart2,
                                                                                        "Gyro X FIFO Enable Failed\r\n");

                                                                while (1);
                                                            }

                                                            if (MPU6050_EnableGyroYFIFO(&hi2c1) != HAL_OK)
                                                            {
                                                                BSP_UART_TransmitString(&huart2,
                                                                                        "Gyro Y FIFO Enable Failed\r\n");

                                                                while (1);
                                                            }

                                                            if (MPU6050_EnableGyroZFIFO(&hi2c1) != HAL_OK)
                                                            {
                                                                BSP_UART_TransmitString(&huart2,
                                                                                        "Gyro Z FIFO Enable Failed\r\n");

                                                                while (1);
                                                            }

                                                            if (MPU6050_EnableTempFIFO(&hi2c1) != HAL_OK)
                                                            {
                                                                BSP_UART_TransmitString(&huart2,
                                                                                        "Temperature FIFO Enable Failed\r\n");

                                                                while (1);
                                                            }


                                                            /*---------------------------------------------------------
                                                             * Reset FIFO
                                                             *--------------------------------------------------------*/

                                                            if (MPU6050_ResetFIFO(&hi2c1) != HAL_OK)
                                                            {
                                                                BSP_UART_TransmitString(&huart2,
                                                                                        "FIFO Reset Failed\r\n");

                                                                while (1);
                                                            }

                                                            BSP_UART_TransmitString(&huart2,
                                                                                    "FIFO Ready\r\n");


                                                            /*---------------------------------------------------------
                                                             * High-Speed FIFO Drain
                                                             *--------------------------------------------------------*/

                                                            while (1)
                                                            {
                                                                /*-----------------------------------------------------
                                                                 * Read FIFO Count
                                                                 *----------------------------------------------------*/

                                                                if (MPU6050_GetFIFOCount(&hi2c1,
                                                                                         &fifoCount) != HAL_OK)
                                                                {
                                                                    continue;
                                                                }


                                                                /*-----------------------------------------------------
                                                                 * Check FIFO Overflow
                                                                 *----------------------------------------------------*/

                                                                if (MPU6050_GetInterruptStatus(&hi2c1,
                                                                                               &intStatus) != HAL_OK)
                                                                {
                                                                    continue;
                                                                }


                                                                if (intStatus & MPU6050_FIFO_OFLOW_INT_Msk)
                                                                {
                                                                    overflowCount++;

                                                                    MPU6050_ResetFIFO(&hi2c1);

                                                                    continue;
                                                                }


                                                                /*-----------------------------------------------------
                                                                 * Wait Until Complete Packet Available
                                                                 *----------------------------------------------------*/

                                                                if (fifoCount < 14U)
                                                                {
                                                                    continue;
                                                                }


                                                                /*-----------------------------------------------------
                                                                 * Read One Complete Packet
                                                                 *----------------------------------------------------*/

                                                                if (MPU6050_ReadFIFOBuffer(&hi2c1,
                                                                                           fifoBuffer,
                                                                                           14U) != HAL_OK)
                                                                {
                                                                    continue;
                                                                }


                                                                packetCount++;


                                                                /*-----------------------------------------------------
                                                                 * Print Only Every 100 Packets
                                                                 *----------------------------------------------------*/

                                                                if ((packetCount % 100U) == 0U)
                                                                {
                                                                    sprintf(message,
                                                                            "\r\nPackets Read : %lu\r\n",
                                                                            packetCount);

                                                                    BSP_UART_TransmitString(&huart2,
                                                                                            message);


                                                                    sprintf(message,
                                                                            "FIFO Count   : %u bytes\r\n",
                                                                            fifoCount);

                                                                    BSP_UART_TransmitString(&huart2,
                                                                                            message);


                                                                    sprintf(message,
                                                                            "Overflow Count: %lu\r\n",
                                                                            overflowCount);

                                                                    BSP_UART_TransmitString(&huart2,
                                                                                            message);


                                                                    BSP_UART_TransmitString(&huart2,
                                                                                            "FIFO RAW     : ");

                                                                    for (uint8_t i = 0U; i < 14U; i++)
                                                                    {
                                                                        sprintf(message,
                                                                                "%02X ",
                                                                                fifoBuffer[i]);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);
                                                                    }

                                                                    BSP_UART_TransmitString(&huart2,
                                                                                            "\r\n");
                                                                }
                                                            }

                                                        #endif





                                                            /*==============================================================================
                                                             * TEST 7.11 : Live FIFO Sensor Monitor
                                                             *==============================================================================
                                                             *
                                                             * Objective
                                                             * ---------
                                                             * Continuously drain the FIFO while periodically displaying decoded
                                                             * accelerometer, temperature and gyroscope values.
                                                             *
                                                             * FIFO packet:
                                                             *
                                                             *   Accelerometer : 6 bytes
                                                             *   Temperature   : 2 bytes
                                                             *   Gyroscope     : 6 bytes
                                                             *   --------------------------
                                                             *   Total         : 14 bytes
                                                             *
                                                             * The FIFO is drained continuously.
                                                             * UART output is limited to approximately 10 packets/second.
                                                             *
                                                             *===========================================================================*/

                                                            #if 0

                                                                MPU6050_FIFOPacket_t packet;

                                                                uint16_t fifoCount;

                                                                uint8_t intStatus;

                                                                uint32_t packetCount = 0U;
                                                                uint32_t overflowCount = 0U;

                                                                uint32_t lastPrintTime = 0U;

                                                                char message[128];


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
                                                                 * Configure DLPF
                                                                 *
                                                                 * DLPF = 94 Hz
                                                                 *--------------------------------------------------------*/

                                                                if (MPU6050_SetDLPF(&hi2c1,
                                                                                    MPU6050_DLPF_BW_94HZ) != HAL_OK)
                                                                {
                                                                    BSP_UART_TransmitString(&huart2,
                                                                                            "DLPF Configuration Failed\r\n");

                                                                    while (1);
                                                                }


                                                                /*---------------------------------------------------------
                                                                 * Configure Sample Rate
                                                                 *
                                                                 * Sample Rate = 1000 / (1 + divider)
                                                                 *
                                                                 * divider = 9
                                                                 *
                                                                 * Sample Rate = 100 Hz
                                                                 *--------------------------------------------------------*/

                                                                if (MPU6050_SetSampleRateDivider(&hi2c1,
                                                                                                 9U) != HAL_OK)
                                                                {
                                                                    BSP_UART_TransmitString(&huart2,
                                                                                            "Sample Rate Configuration Failed\r\n");

                                                                    while (1);
                                                                }


                                                                BSP_UART_TransmitString(&huart2,
                                                                                        "Sampling Configuration Successful\r\n");


                                                                /*---------------------------------------------------------
                                                                 * Enable FIFO
                                                                 *--------------------------------------------------------*/

                                                                if (MPU6050_EnableFIFO(&hi2c1) != HAL_OK)
                                                                {
                                                                    BSP_UART_TransmitString(&huart2,
                                                                                            "FIFO Enable Failed\r\n");

                                                                    while (1);
                                                                }


                                                                /*---------------------------------------------------------
                                                                 * Enable FIFO Sources
                                                                 *--------------------------------------------------------*/

                                                                if (MPU6050_EnableAccelFIFO(&hi2c1) != HAL_OK)
                                                                {
                                                                    BSP_UART_TransmitString(&huart2,
                                                                                            "Accel FIFO Enable Failed\r\n");

                                                                    while (1);
                                                                }

                                                                if (MPU6050_EnableGyroXFIFO(&hi2c1) != HAL_OK)
                                                                {
                                                                    BSP_UART_TransmitString(&huart2,
                                                                                            "Gyro X FIFO Enable Failed\r\n");

                                                                    while (1);
                                                                }

                                                                if (MPU6050_EnableGyroYFIFO(&hi2c1) != HAL_OK)
                                                                {
                                                                    BSP_UART_TransmitString(&huart2,
                                                                                            "Gyro Y FIFO Enable Failed\r\n");

                                                                    while (1);
                                                                }

                                                                if (MPU6050_EnableGyroZFIFO(&hi2c1) != HAL_OK)
                                                                {
                                                                    BSP_UART_TransmitString(&huart2,
                                                                                            "Gyro Z FIFO Enable Failed\r\n");

                                                                    while (1);
                                                                }

                                                                if (MPU6050_EnableTempFIFO(&hi2c1) != HAL_OK)
                                                                {
                                                                    BSP_UART_TransmitString(&huart2,
                                                                                            "Temperature FIFO Enable Failed\r\n");

                                                                    while (1);
                                                                }


                                                                /*---------------------------------------------------------
                                                                 * Reset FIFO
                                                                 *--------------------------------------------------------*/

                                                                if (MPU6050_ResetFIFO(&hi2c1) != HAL_OK)
                                                                {
                                                                    BSP_UART_TransmitString(&huart2,
                                                                                            "FIFO Reset Failed\r\n");

                                                                    while (1);
                                                                }


                                                                BSP_UART_TransmitString(&huart2,
                                                                                        "FIFO Ready\r\n");


                                                                /*---------------------------------------------------------
                                                                 * Start Timer
                                                                 *--------------------------------------------------------*/

                                                                lastPrintTime = HAL_GetTick();


                                                                /*---------------------------------------------------------
                                                                 * Main FIFO Processing Loop
                                                                 *--------------------------------------------------------*/

                                                                while (1)
                                                                {
                                                                    /*-----------------------------------------------------
                                                                     * Read FIFO Count
                                                                     *----------------------------------------------------*/

                                                                    if (MPU6050_GetFIFOCount(&hi2c1,
                                                                                             &fifoCount) != HAL_OK)
                                                                    {
                                                                        continue;
                                                                    }


                                                                    /*-----------------------------------------------------
                                                                     * Read Interrupt Status
                                                                     *----------------------------------------------------*/

                                                                    if (MPU6050_GetInterruptStatus(&hi2c1,
                                                                                                   &intStatus) != HAL_OK)
                                                                    {
                                                                        continue;
                                                                    }


                                                                    /*-----------------------------------------------------
                                                                     * FIFO Overflow
                                                                     *----------------------------------------------------*/

                                                                    if (intStatus & MPU6050_FIFO_OFLOW_INT_Msk)
                                                                    {
                                                                        overflowCount++;

                                                                        MPU6050_ResetFIFO(&hi2c1);

                                                                        continue;
                                                                    }


                                                                    /*-----------------------------------------------------
                                                                     * Wait Until Complete Packet Available
                                                                     *----------------------------------------------------*/

                                                                    if (fifoCount < 14U)
                                                                    {
                                                                        continue;
                                                                    }


                                                                    /*-----------------------------------------------------
                                                                     * Read One FIFO Packet
                                                                     *----------------------------------------------------*/

                                                                    if (MPU6050_ReadFIFOPacket(&hi2c1,
                                                                                               &packet) != HAL_OK)
                                                                    {
                                                                        continue;
                                                                    }


                                                                    packetCount++;


                                                                    /*-----------------------------------------------------
                                                                     * Print Approximately Every 100 ms
                                                                     *--------------------------------------------------------*/

                                                                    if ((HAL_GetTick() - lastPrintTime) >= 100U)
                                                                    {
                                                                        lastPrintTime = HAL_GetTick();


                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "\r\n--------------------------------\r\n");


                                                                        sprintf(message,
                                                                                "Packets Read : %lu\r\n",
                                                                                packetCount);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);


                                                                        sprintf(message,
                                                                                "FIFO Count   : %u bytes\r\n",
                                                                                fifoCount);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);


                                                                        sprintf(message,
                                                                                "Overflow Count: %lu\r\n\r\n",
                                                                                overflowCount);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);


                                                                        /*-------------------------------------------------
                                                                         * Accelerometer
                                                                         *------------------------------------------------*/

                                                                        sprintf(message,
                                                                                "Accel X : %6d\r\n",
                                                                                packet.accel.x);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);


                                                                        sprintf(message,
                                                                                "Accel Y : %6d\r\n",
                                                                                packet.accel.y);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);


                                                                        sprintf(message,
                                                                                "Accel Z : %6d\r\n\r\n",
                                                                                packet.accel.z);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);


                                                                        /*-------------------------------------------------
                                                                         * Temperature
                                                                         *------------------------------------------------*/

                                                                        sprintf(message,
                                                                                "Temperature : %.2f C\r\n\r\n",
                                                                                packet.temp.temperature);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);


                                                                        /*-------------------------------------------------
                                                                         * Gyroscope
                                                                         *------------------------------------------------*/

                                                                        sprintf(message,
                                                                                "Gyro X : %6d\r\n",
                                                                                packet.gyro.x);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);


                                                                        sprintf(message,
                                                                                "Gyro Y : %6d\r\n",
                                                                                packet.gyro.y);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);


                                                                        sprintf(message,
                                                                                "Gyro Z : %6d\r\n",
                                                                                packet.gyro.z);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);
                                                                    }
                                                                }

                                                            #endif


                                                                /*==============================================================================
                                                                 * TEST 7.12 : Sensor Physical Unit Conversion
                                                                 *==============================================================================
                                                                 *
                                                                 * Objective
                                                                 * ---------
                                                                 * Read live FIFO packets and convert raw sensor values into physical units.
                                                                 *
                                                                 * Accelerometer:
                                                                 *     ±2 g
                                                                 *     16384 LSB/g
                                                                 *
                                                                 * Gyroscope:
                                                                 *     ±250 dps
                                                                 *     131 LSB/(°/s)
                                                                 *
                                                                 * Temperature:
                                                                 *     Temperature = Raw / 340 + 36.53
                                                                 *
                                                                 *===========================================================================*/

                                                                #if 1

                                                                    MPU6050_FIFOPacket_t packet;

                                                                    uint16_t fifoCount;

                                                                    uint8_t intStatus;

                                                                    uint32_t packetCount = 0U;
                                                                    uint32_t overflowCount = 0U;

                                                                    uint32_t lastPrintTime = 0U;

                                                                    float accelX_g;
                                                                    float accelY_g;
                                                                    float accelZ_g;

                                                                    float gyroX_dps;
                                                                    float gyroY_dps;
                                                                    float gyroZ_dps;

                                                                    char message[128];


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
                                                                     *
                                                                     * ±2 g
                                                                     *--------------------------------------------------------*/

                                                                    if (MPU6050_SetAccelRange(&hi2c1,
                                                                                              MPU6050_ACCEL_RANGE_2G) != HAL_OK)
                                                                    {
                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "Accel Range Configuration Failed\r\n");

                                                                        while (1);
                                                                    }


                                                                    /*---------------------------------------------------------
                                                                     * Configure Gyroscope Range
                                                                     *
                                                                     * ±250 dps
                                                                     *--------------------------------------------------------*/

                                                                    if (MPU6050_SetGyroRange(&hi2c1,
                                                                                             MPU6050_GYRO_RANGE_250DPS) != HAL_OK)
                                                                    {
                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "Gyro Range Configuration Failed\r\n");

                                                                        while (1);
                                                                    }


                                                                    /*---------------------------------------------------------
                                                                     * Configure DLPF
                                                                     *--------------------------------------------------------*/

                                                                    if (MPU6050_SetDLPF(&hi2c1,
                                                                                        MPU6050_DLPF_BW_94HZ) != HAL_OK)
                                                                    {
                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "DLPF Configuration Failed\r\n");

                                                                        while (1);
                                                                    }


                                                                    /*---------------------------------------------------------
                                                                     * Configure Sample Rate
                                                                     *
                                                                     * 1000 / (1 + 9) = 100 Hz
                                                                     *--------------------------------------------------------*/

                                                                    if (MPU6050_SetSampleRateDivider(&hi2c1,
                                                                                                     9U) != HAL_OK)
                                                                    {
                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "Sample Rate Configuration Failed\r\n");

                                                                        while (1);
                                                                    }


                                                                    BSP_UART_TransmitString(&huart2,
                                                                                            "Sensor Configuration Successful\r\n");


                                                                    /*---------------------------------------------------------
                                                                     * Enable FIFO
                                                                     *--------------------------------------------------------*/

                                                                    if (MPU6050_EnableFIFO(&hi2c1) != HAL_OK)
                                                                    {
                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "FIFO Enable Failed\r\n");

                                                                        while (1);
                                                                    }


                                                                    /*---------------------------------------------------------
                                                                     * Enable FIFO Sources
                                                                     *--------------------------------------------------------*/

                                                                    if (MPU6050_EnableAccelFIFO(&hi2c1) != HAL_OK)
                                                                    {
                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "Accel FIFO Enable Failed\r\n");

                                                                        while (1);
                                                                    }

                                                                    if (MPU6050_EnableGyroXFIFO(&hi2c1) != HAL_OK)
                                                                    {
                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "Gyro X FIFO Enable Failed\r\n");

                                                                        while (1);
                                                                    }

                                                                    if (MPU6050_EnableGyroYFIFO(&hi2c1) != HAL_OK)
                                                                    {
                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "Gyro Y FIFO Enable Failed\r\n");

                                                                        while (1);
                                                                    }

                                                                    if (MPU6050_EnableGyroZFIFO(&hi2c1) != HAL_OK)
                                                                    {
                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "Gyro Z FIFO Enable Failed\r\n");

                                                                        while (1);
                                                                    }

                                                                    if (MPU6050_EnableTempFIFO(&hi2c1) != HAL_OK)
                                                                    {
                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "Temperature FIFO Enable Failed\r\n");

                                                                        while (1);
                                                                    }


                                                                    /*---------------------------------------------------------
                                                                     * Reset FIFO
                                                                     *--------------------------------------------------------*/

                                                                    if (MPU6050_ResetFIFO(&hi2c1) != HAL_OK)
                                                                    {
                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "FIFO Reset Failed\r\n");

                                                                        while (1);
                                                                    }


                                                                    BSP_UART_TransmitString(&huart2,
                                                                                            "FIFO Ready\r\n");


                                                                    lastPrintTime = HAL_GetTick();


                                                                    /*---------------------------------------------------------
                                                                     * Main Loop
                                                                     *--------------------------------------------------------*/

                                                                    while (1)
                                                                    {
                                                                        /*-----------------------------------------------------
                                                                         * Get FIFO Count
                                                                         *----------------------------------------------------*/

                                                                        if (MPU6050_GetFIFOCount(&hi2c1,
                                                                                                 &fifoCount) != HAL_OK)
                                                                        {
                                                                            continue;
                                                                        }


                                                                        /*-----------------------------------------------------
                                                                         * Check FIFO Overflow
                                                                         *----------------------------------------------------*/

                                                                        if (MPU6050_GetInterruptStatus(&hi2c1,
                                                                                                       &intStatus) != HAL_OK)
                                                                        {
                                                                            continue;
                                                                        }


                                                                        if (intStatus & MPU6050_FIFO_OFLOW_INT_Msk)
                                                                        {
                                                                            overflowCount++;

                                                                            MPU6050_ResetFIFO(&hi2c1);

                                                                            continue;
                                                                        }


                                                                        /*-----------------------------------------------------
                                                                         * Wait for Complete Packet
                                                                         *----------------------------------------------------*/

                                                                        if (fifoCount < 14U)
                                                                        {
                                                                            continue;
                                                                        }


                                                                        /*-----------------------------------------------------
                                                                         * Read FIFO Packet
                                                                         *----------------------------------------------------*/

                                                                        if (MPU6050_ReadFIFOPacket(&hi2c1,
                                                                                                   &packet) != HAL_OK)
                                                                        {
                                                                            continue;
                                                                        }


                                                                        packetCount++;


                                                                        /*-----------------------------------------------------
                                                                         * Convert Accelerometer
                                                                         *
                                                                         * ±2 g = 16384 LSB/g
                                                                         *----------------------------------------------------*/

                                                                        accelX_g = (float)packet.accel.x / 16384.0f;
                                                                        accelY_g = (float)packet.accel.y / 16384.0f;
                                                                        accelZ_g = (float)packet.accel.z / 16384.0f;


                                                                        /*-----------------------------------------------------
                                                                         * Convert Gyroscope
                                                                         *
                                                                         * ±250 dps = 131 LSB/(°/s)
                                                                         *----------------------------------------------------*/

                                                                        gyroX_dps = (float)packet.gyro.x / 131.0f;
                                                                        gyroY_dps = (float)packet.gyro.y / 131.0f;
                                                                        gyroZ_dps = (float)packet.gyro.z / 131.0f;


                                                                        /*-----------------------------------------------------
                                                                         * Print Every 100 ms
                                                                         *----------------------------------------------------*/

                                                                        if ((HAL_GetTick() - lastPrintTime) >= 100U)
                                                                        {
                                                                            lastPrintTime = HAL_GetTick();


                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    "\r\n--------------------------------\r\n");


                                                                            sprintf(message,
                                                                                    "Packets Read  : %lu\r\n",
                                                                                    packetCount);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "FIFO Count    : %u bytes\r\n",
                                                                                    fifoCount);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "Overflow Count: %lu\r\n\r\n",
                                                                                    overflowCount);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            /*-------------------------------------------------
                                                                             * Raw Accelerometer
                                                                             *------------------------------------------------*/

                                                                            sprintf(message,
                                                                                    "Accel Raw X : %6d\r\n",
                                                                                    packet.accel.x);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "Accel Raw Y : %6d\r\n",
                                                                                    packet.accel.y);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "Accel Raw Z : %6d\r\n\r\n",
                                                                                    packet.accel.z);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            /*-------------------------------------------------
                                                                             * Physical Accelerometer
                                                                             *------------------------------------------------*/

                                                                            sprintf(message,
                                                                                    "Accel X : %+.3f g\r\n",
                                                                                    accelX_g);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "Accel Y : %+.3f g\r\n",
                                                                                    accelY_g);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "Accel Z : %+.3f g\r\n\r\n",
                                                                                    accelZ_g);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            /*-------------------------------------------------
                                                                             * Temperature
                                                                             *-------------------------------------------------*/

                                                                            sprintf(message,
                                                                                    "Temperature : %.2f C\r\n\r\n",
                                                                                    packet.temp.temperature);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            /*-------------------------------------------------
                                                                             * Raw Gyroscope
                                                                             *-------------------------------------------------*/

                                                                            sprintf(message,
                                                                                    "Gyro Raw X : %6d\r\n",
                                                                                    packet.gyro.x);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "Gyro Raw Y : %6d\r\n",
                                                                                    packet.gyro.y);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "Gyro Raw Z : %6d\r\n\r\n",
                                                                                    packet.gyro.z);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            /*-------------------------------------------------
                                                                             * Physical Gyroscope
                                                                             *-------------------------------------------------*/

                                                                            sprintf(message,
                                                                                    "Gyro X : %+.2f dps\r\n",
                                                                                    gyroX_dps);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "Gyro Y : %+.2f dps\r\n",
                                                                                    gyroY_dps);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "Gyro Z : %+.2f dps\r\n",
                                                                                    gyroZ_dps);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);
                                                                        }
                                                                    }

                                                                #endif








}
