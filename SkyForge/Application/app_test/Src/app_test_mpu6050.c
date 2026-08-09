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
#include <math.h>

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

                                                                #if 0

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



                                                                    /*==============================================================================
                                                                     * TEST 7.13 : Gyroscope Bias Calibration
                                                                     *==============================================================================
                                                                     *
                                                                     * Objective
                                                                     * ---------
                                                                     * Measure the MPU6050 gyroscope zero-rate bias while the sensor is stationary.
                                                                     *
                                                                     * Calibration:
                                                                     *
                                                                     *     Bias = Sum(samples) / Number of samples
                                                                     *
                                                                     * Corrected value:
                                                                     *
                                                                     *     Corrected = Measured - Bias
                                                                     *
                                                                     * Configuration:
                                                                     *
                                                                     *     Gyroscope : ±250 dps
                                                                     *     DLPF      : 94 Hz
                                                                     *     Sample    : 100 Hz
                                                                     *
                                                                     * IMPORTANT:
                                                                     * Keep the MPU6050 completely stationary during calibration.
                                                                     *
                                                                     *===========================================================================*/

                                                                    #if 0

                                                                        MPU6050_FIFOPacket_t packet;

                                                                        uint16_t fifoCount;
                                                                        uint8_t intStatus;

                                                                        uint32_t sampleCount = 0U;

                                                                        int64_t gyroSumX = 0;
                                                                        int64_t gyroSumY = 0;
                                                                        int64_t gyroSumZ = 0;

                                                                        int32_t gyroBiasX;
                                                                        int32_t gyroBiasY;
                                                                        int32_t gyroBiasZ;

                                                                        float gyroBiasXdps;
                                                                        float gyroBiasYdps;
                                                                        float gyroBiasZdps;

                                                                        float gyroXdps;
                                                                        float gyroYdps;
                                                                        float gyroZdps;

                                                                        uint32_t lastPrintTime;

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
                                                                         * Configure Gyroscope Range
                                                                         *
                                                                         * ±250 dps
                                                                         * 131 LSB/(dps)
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
                                                                         * Enable Gyroscope FIFO Sources
                                                                         *--------------------------------------------------------*/

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


                                                                        /*---------------------------------------------------------
                                                                         * Reset FIFO
                                                                         *--------------------------------------------------------*/

                                                                        if (MPU6050_ResetFIFO(&hi2c1) != HAL_OK)
                                                                        {
                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    "FIFO Reset Failed\r\n");

                                                                            while (1);
                                                                        }


                                                                        /*---------------------------------------------------------
                                                                         * Allow sensor/FIFO to settle
                                                                         *--------------------------------------------------------*/

                                                                        HAL_Delay(100);


                                                                        /*---------------------------------------------------------
                                                                         * Reset FIFO again before calibration
                                                                         *--------------------------------------------------------*/

                                                                        if (MPU6050_ResetFIFO(&hi2c1) != HAL_OK)
                                                                        {
                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    "FIFO Reset Before Calibration Failed\r\n");

                                                                            while (1);
                                                                        }


                                                                        /*---------------------------------------------------------
                                                                         * Calibration Warning
                                                                         *--------------------------------------------------------*/

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "\r\n================================\r\n");

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "GYROSCOPE CALIBRATION\r\n");

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "KEEP SENSOR COMPLETELY STILL\r\n");

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "Collecting 1000 samples...\r\n");

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "================================\r\n");


                                                                        /*---------------------------------------------------------
                                                                         * Collect 1000 Samples
                                                                         *--------------------------------------------------------*/

                                                                        while (sampleCount < 1000U)
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
                                                                                /*
                                                                                 * Calibration data would be invalid if samples
                                                                                 * were lost. Restart calibration.
                                                                                 */

                                                                                gyroSumX = 0;
                                                                                gyroSumY = 0;
                                                                                gyroSumZ = 0;

                                                                                sampleCount = 0U;

                                                                                MPU6050_ResetFIFO(&hi2c1);

                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                        "\r\nFIFO Overflow - Restarting Calibration\r\n");

                                                                                continue;
                                                                            }


                                                                            /*-----------------------------------------------------
                                                                             * Wait for Complete Packet
                                                                             *----------------------------------------------------*/

                                                                            if (fifoCount < 6U)
                                                                            {
                                                                                continue;
                                                                            }


                                                                            /*
                                                                             * Only gyroscope X/Y/Z are enabled in FIFO.
                                                                             *
                                                                             * Therefore packet size is:
                                                                             *
                                                                             *     6 bytes
                                                                             *
                                                                             * However, MPU6050_ReadFIFOPacket() expects the
                                                                             * complete 14-byte packet.
                                                                             *
                                                                             * So we cannot use it here.
                                                                             */

                                                                            {
                                                                                uint8_t gyroBuffer[6];

                                                                                if (MPU6050_ReadFIFOBuffer(&hi2c1,
                                                                                                           gyroBuffer,
                                                                                                           6U) != HAL_OK)
                                                                                {
                                                                                    continue;
                                                                                }


                                                                                /*-------------------------------------------------
                                                                                 * Convert FIFO bytes to signed 16-bit values
                                                                                 *------------------------------------------------*/

                                                                                int16_t gyroX =
                                                                                    (int16_t)(((uint16_t)gyroBuffer[0] << 8) |
                                                                                               gyroBuffer[1]);

                                                                                int16_t gyroY =
                                                                                    (int16_t)(((uint16_t)gyroBuffer[2] << 8) |
                                                                                               gyroBuffer[3]);

                                                                                int16_t gyroZ =
                                                                                    (int16_t)(((uint16_t)gyroBuffer[4] << 8) |
                                                                                               gyroBuffer[5]);


                                                                                gyroSumX += gyroX;
                                                                                gyroSumY += gyroY;
                                                                                gyroSumZ += gyroZ;

                                                                                sampleCount++;
                                                                            }
                                                                        }


                                                                        /*---------------------------------------------------------
                                                                         * Calculate Bias
                                                                         *--------------------------------------------------------*/

                                                                        gyroBiasX = (int32_t)(gyroSumX / 1000);
                                                                        gyroBiasY = (int32_t)(gyroSumY / 1000);
                                                                        gyroBiasZ = (int32_t)(gyroSumZ / 1000);


                                                                        /*---------------------------------------------------------
                                                                         * Convert Bias to Physical Units
                                                                         *
                                                                         * ±250 dps = 131 LSB/dps
                                                                         *--------------------------------------------------------*/

                                                                        gyroBiasXdps = (float)gyroBiasX / 131.0f;
                                                                        gyroBiasYdps = (float)gyroBiasY / 131.0f;
                                                                        gyroBiasZdps = (float)gyroBiasZ / 131.0f;


                                                                        /*---------------------------------------------------------
                                                                         * Print Calibration Result
                                                                         *--------------------------------------------------------*/

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "\r\n================================\r\n");

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "GYROSCOPE CALIBRATION COMPLETE\r\n");

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "================================\r\n");


                                                                        sprintf(message,
                                                                                "Samples : %lu\r\n\r\n",
                                                                                sampleCount);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);


                                                                        sprintf(message,
                                                                                "Bias X : %ld raw\r\n",
                                                                                gyroBiasX);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);


                                                                        sprintf(message,
                                                                                "Bias Y : %ld raw\r\n",
                                                                                gyroBiasY);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);


                                                                        sprintf(message,
                                                                                "Bias Z : %ld raw\r\n\r\n",
                                                                                gyroBiasZ);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);


                                                                        sprintf(message,
                                                                                "Bias X : %+.3f dps\r\n",
                                                                                gyroBiasXdps);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);


                                                                        sprintf(message,
                                                                                "Bias Y : %+.3f dps\r\n",
                                                                                gyroBiasYdps);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);


                                                                        sprintf(message,
                                                                                "Bias Z : %+.3f dps\r\n",
                                                                                gyroBiasZdps);

                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                message);


                                                                        /*---------------------------------------------------------
                                                                         * Clear FIFO Before Corrected Data Test
                                                                         *--------------------------------------------------------*/

                                                                        MPU6050_ResetFIFO(&hi2c1);


                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                "\r\nStarting Corrected Gyro Output...\r\n");


                                                                        lastPrintTime = HAL_GetTick();


                                                                        /*---------------------------------------------------------
                                                                         * Enable Continuous Gyro FIFO Processing
                                                                         *--------------------------------------------------------*/

                                                                        while (1)
                                                                        {
                                                                            if (MPU6050_GetFIFOCount(&hi2c1,
                                                                                                     &fifoCount) != HAL_OK)
                                                                            {
                                                                                continue;
                                                                            }


                                                                            if (MPU6050_GetInterruptStatus(&hi2c1,
                                                                                                           &intStatus) != HAL_OK)
                                                                            {
                                                                                continue;
                                                                            }


                                                                            if (intStatus & MPU6050_FIFO_OFLOW_INT_Msk)
                                                                            {
                                                                                MPU6050_ResetFIFO(&hi2c1);

                                                                                continue;
                                                                            }


                                                                            if (fifoCount < 6U)
                                                                            {
                                                                                continue;
                                                                            }


                                                                            {
                                                                                uint8_t gyroBuffer[6];

                                                                                if (MPU6050_ReadFIFOBuffer(&hi2c1,
                                                                                                           gyroBuffer,
                                                                                                           6U) != HAL_OK)
                                                                                {
                                                                                    continue;
                                                                                }


                                                                                int16_t gyroX =
                                                                                    (int16_t)(((uint16_t)gyroBuffer[0] << 8) |
                                                                                               gyroBuffer[1]);

                                                                                int16_t gyroY =
                                                                                    (int16_t)(((uint16_t)gyroBuffer[2] << 8) |
                                                                                               gyroBuffer[3]);

                                                                                int16_t gyroZ =
                                                                                    (int16_t)(((uint16_t)gyroBuffer[4] << 8) |
                                                                                               gyroBuffer[5]);


                                                                                /*---------------------------------------------
                                                                                 * Remove Bias
                                                                                 *--------------------------------------------*/

                                                                                gyroXdps =
                                                                                    ((float)gyroX - (float)gyroBiasX) / 131.0f;

                                                                                gyroYdps =
                                                                                    ((float)gyroY - (float)gyroBiasY) / 131.0f;

                                                                                gyroZdps =
                                                                                    ((float)gyroZ - (float)gyroBiasZ) / 131.0f;


                                                                                /*---------------------------------------------
                                                                                 * Print Every 100 ms
                                                                                 *--------------------------------------------*/

                                                                                if ((HAL_GetTick() - lastPrintTime) >= 100U)
                                                                                {
                                                                                    lastPrintTime = HAL_GetTick();


                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                            "\r\n--------------------------------\r\n");


                                                                                    sprintf(message,
                                                                                            "Corrected Gyro X : %+.3f dps\r\n",
                                                                                            gyroXdps);

                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                            message);


                                                                                    sprintf(message,
                                                                                            "Corrected Gyro Y : %+.3f dps\r\n",
                                                                                            gyroYdps);

                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                            message);


                                                                                    sprintf(message,
                                                                                            "Corrected Gyro Z : %+.3f dps\r\n",
                                                                                            gyroZdps);

                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                            message);
                                                                                }
                                                                            }
                                                                        }

                                                                    #endif


                                                                        /*==============================================================================
                                                                         * TEST 7.13A : Gyroscope Calibration Integrity
                                                                         *==============================================================================
                                                                         *
                                                                         * Objective
                                                                         * ---------
                                                                         * Verify that gyro calibration samples are valid and stable.
                                                                         *
                                                                         * FIFO Configuration
                                                                         * -------------------
                                                                         *
                                                                         *     Gyro X : 2 bytes
                                                                         *     Gyro Y : 2 bytes
                                                                         *     Gyro Z : 2 bytes
                                                                         *     ----------------
                                                                         *     Total  : 6 bytes
                                                                         *
                                                                         * Calibration
                                                                         * -----------
                                                                         *
                                                                         *     1000 samples
                                                                         *
                                                                         *     Bias = Sum(samples) / 1000
                                                                         *
                                                                         * The test also calculates:
                                                                         *
                                                                         *     Minimum
                                                                         *     Maximum
                                                                         *     Average
                                                                         *
                                                                         * This allows us to determine whether the FIFO data is stable
                                                                         * before trusting the calculated bias.
                                                                         *
                                                                         * Configuration
                                                                         * -------------
                                                                         *
                                                                         *     Gyroscope : ±250 dps
                                                                         *     DLPF      : 94 Hz
                                                                         *     Sample    : 100 Hz
                                                                         *
                                                                         * IMPORTANT:
                                                                         * Keep the MPU6050 completely stationary during calibration.
                                                                         *
                                                                         *===========================================================================*/

                                                                        #if 0

                                                                            uint16_t fifoCount;
                                                                            uint8_t intStatus;

                                                                            uint8_t gyroBuffer[6];

                                                                            uint32_t sampleCount = 0U;
                                                                            uint32_t discardedSamples = 0U;

                                                                            int64_t gyroSumX = 0;
                                                                            int64_t gyroSumY = 0;
                                                                            int64_t gyroSumZ = 0;

                                                                            int16_t gyroMinX = INT16_MAX;
                                                                            int16_t gyroMinY = INT16_MAX;
                                                                            int16_t gyroMinZ = INT16_MAX;

                                                                            int16_t gyroMaxX = INT16_MIN;
                                                                            int16_t gyroMaxY = INT16_MIN;
                                                                            int16_t gyroMaxZ = INT16_MIN;

                                                                            int32_t gyroBiasX;
                                                                            int32_t gyroBiasY;
                                                                            int32_t gyroBiasZ;

                                                                            float gyroBiasXdps;
                                                                            float gyroBiasYdps;
                                                                            float gyroBiasZdps;

                                                                            float gyroXdps;
                                                                            float gyroYdps;
                                                                            float gyroZdps;

                                                                            uint32_t lastPrintTime = 0U;

                                                                            char message[128];


                                                                            /*=========================================================
                                                                             * Initialize MPU6050
                                                                             *========================================================*/

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


                                                                            /*=========================================================
                                                                             * Configure Gyroscope Range
                                                                             *
                                                                             * ±250 dps
                                                                             *
                                                                             * Sensitivity:
                                                                             *
                                                                             * 131 LSB / dps
                                                                             *=========================================================*/

                                                                            if (MPU6050_SetGyroRange(&hi2c1,
                                                                                                     MPU6050_GYRO_RANGE_250DPS) != HAL_OK)
                                                                            {
                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                        "Gyro Range Configuration Failed\r\n");

                                                                                while (1);
                                                                            }


                                                                            /*=========================================================
                                                                             * Configure DLPF
                                                                             *=========================================================*/

                                                                            if (MPU6050_SetDLPF(&hi2c1,
                                                                                                MPU6050_DLPF_BW_94HZ) != HAL_OK)
                                                                            {
                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                        "DLPF Configuration Failed\r\n");

                                                                                while (1);
                                                                            }


                                                                            /*=========================================================
                                                                             * Configure Sample Rate
                                                                             *
                                                                             * Sample Rate =
                                                                             *
                                                                             * 1000 / (1 + SMPLRT_DIV)
                                                                             *
                                                                             * Divider = 9
                                                                             *
                                                                             * Sample Rate = 100 Hz
                                                                             *=========================================================*/

                                                                            if (MPU6050_SetSampleRateDivider(&hi2c1,
                                                                                                             9U) != HAL_OK)
                                                                            {
                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                        "Sample Rate Configuration Failed\r\n");

                                                                                while (1);
                                                                            }


                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    "Sensor Configuration Successful\r\n");


                                                                            /*=========================================================
                                                                             * Enable FIFO
                                                                             *=========================================================*/

                                                                            if (MPU6050_EnableFIFO(&hi2c1) != HAL_OK)
                                                                            {
                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                        "FIFO Enable Failed\r\n");

                                                                                while (1);
                                                                            }


                                                                            /*=========================================================
                                                                             * Enable ONLY Gyroscope FIFO Sources
                                                                             *=========================================================*/

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


                                                                            /*=========================================================
                                                                             * Reset FIFO AFTER configuring FIFO sources
                                                                             *
                                                                             * This guarantees that calibration starts from an empty
                                                                             * FIFO containing only the selected gyro sources.
                                                                             *=========================================================*/

                                                                            if (MPU6050_ResetFIFO(&hi2c1) != HAL_OK)
                                                                            {
                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                        "FIFO Reset Failed\r\n");

                                                                                while (1);
                                                                            }


                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    "Gyroscope FIFO Ready\r\n");


                                                                            /*=========================================================
                                                                             * Allow FIFO to collect samples
                                                                             *=========================================================*/

                                                                            HAL_Delay(50);


                                                                            /*=========================================================
                                                                             * Discard First 10 Samples
                                                                             *
                                                                             * These samples are not used for calibration.
                                                                             *=========================================================*/

                                                                            discardedSamples = 0U;


                                                                            while (discardedSamples < 10U)
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
                                                                                 * Check FIFO Overflow
                                                                                 *----------------------------------------------------*/

                                                                                if (intStatus & MPU6050_FIFO_OFLOW_INT_Msk)
                                                                                {
                                                                                    MPU6050_ResetFIFO(&hi2c1);

                                                                                    discardedSamples = 0U;

                                                                                    continue;
                                                                                }


                                                                                /*-----------------------------------------------------
                                                                                 * One gyro sample = 6 bytes
                                                                                 *----------------------------------------------------*/

                                                                                if (fifoCount < 6U)
                                                                                {
                                                                                    continue;
                                                                                }


                                                                                /*-----------------------------------------------------
                                                                                 * Read one gyro sample
                                                                                 *----------------------------------------------------*/

                                                                                if (MPU6050_ReadFIFOBuffer(&hi2c1,
                                                                                                           gyroBuffer,
                                                                                                           6U) != HAL_OK)
                                                                                {
                                                                                    continue;
                                                                                }


                                                                                discardedSamples++;
                                                                            }


                                                                            /*=========================================================
                                                                             * Final FIFO Reset
                                                                             *
                                                                             * Calibration starts from an empty FIFO.
                                                                             *=========================================================*/

                                                                            if (MPU6050_ResetFIFO(&hi2c1) != HAL_OK)
                                                                            {
                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                        "Calibration FIFO Reset Failed\r\n");

                                                                                while (1);
                                                                            }


                                                                            /*=========================================================
                                                                             * Calibration Message
                                                                             *=========================================================*/

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    "\r\n================================\r\n");

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    "GYRO CALIBRATION INTEGRITY TEST\r\n");

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    "KEEP SENSOR COMPLETELY STILL\r\n");

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    "Collecting 1000 samples...\r\n");

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    "================================\r\n");


                                                                            /*=========================================================
                                                                             * Collect 1000 Samples
                                                                             *=========================================================*/

                                                                            while (sampleCount < 1000U)
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
                                                                                 *
                                                                                 * If overflow happens, the calibration is invalid.
                                                                                 * Restart the complete calibration process.
                                                                                 *----------------------------------------------------*/

                                                                                if (intStatus & MPU6050_FIFO_OFLOW_INT_Msk)
                                                                                {
                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                            "\r\nFIFO OVERFLOW\r\n");

                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                            "Restarting Calibration...\r\n");


                                                                                    gyroSumX = 0;
                                                                                    gyroSumY = 0;
                                                                                    gyroSumZ = 0;

                                                                                    gyroMinX = INT16_MAX;
                                                                                    gyroMinY = INT16_MAX;
                                                                                    gyroMinZ = INT16_MAX;

                                                                                    gyroMaxX = INT16_MIN;
                                                                                    gyroMaxY = INT16_MIN;
                                                                                    gyroMaxZ = INT16_MIN;

                                                                                    sampleCount = 0U;


                                                                                    if (MPU6050_ResetFIFO(&hi2c1) != HAL_OK)
                                                                                    {
                                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                                "FIFO Reset Failed\r\n");

                                                                                        while (1);
                                                                                    }


                                                                                    continue;
                                                                                }


                                                                                /*-----------------------------------------------------
                                                                                 * Wait for one complete gyro sample
                                                                                 *----------------------------------------------------*/

                                                                                if (fifoCount < 6U)
                                                                                {
                                                                                    continue;
                                                                                }


                                                                                /*-----------------------------------------------------
                                                                                 * Read 6-byte gyro sample
                                                                                 *----------------------------------------------------*/

                                                                                if (MPU6050_ReadFIFOBuffer(&hi2c1,
                                                                                                           gyroBuffer,
                                                                                                           6U) != HAL_OK)
                                                                                {
                                                                                    continue;
                                                                                }


                                                                                /*-----------------------------------------------------
                                                                                 * Decode Gyro X
                                                                                 *
                                                                                 * FIFO format:
                                                                                 *
                                                                                 * Byte 0 = MSB
                                                                                 * Byte 1 = LSB
                                                                                 *----------------------------------------------------*/

                                                                                int16_t gyroX =
                                                                                    (int16_t)(((uint16_t)gyroBuffer[0] << 8U) |
                                                                                               gyroBuffer[1]);


                                                                                /*-----------------------------------------------------
                                                                                 * Decode Gyro Y
                                                                                 *----------------------------------------------------*/

                                                                                int16_t gyroY =
                                                                                    (int16_t)(((uint16_t)gyroBuffer[2] << 8U) |
                                                                                               gyroBuffer[3]);


                                                                                /*-----------------------------------------------------
                                                                                 * Decode Gyro Z
                                                                                 *----------------------------------------------------*/

                                                                                int16_t gyroZ =
                                                                                    (int16_t)(((uint16_t)gyroBuffer[4] << 8U) |
                                                                                               gyroBuffer[5]);


                                                                                /*-----------------------------------------------------
                                                                                 * Accumulate
                                                                                 *----------------------------------------------------*/

                                                                                gyroSumX += gyroX;
                                                                                gyroSumY += gyroY;
                                                                                gyroSumZ += gyroZ;


                                                                                /*-----------------------------------------------------
                                                                                 * Minimum
                                                                                 *----------------------------------------------------*/

                                                                                if (gyroX < gyroMinX)
                                                                                {
                                                                                    gyroMinX = gyroX;
                                                                                }

                                                                                if (gyroY < gyroMinY)
                                                                                {
                                                                                    gyroMinY = gyroY;
                                                                                }

                                                                                if (gyroZ < gyroMinZ)
                                                                                {
                                                                                    gyroMinZ = gyroZ;
                                                                                }


                                                                                /*-----------------------------------------------------
                                                                                 * Maximum
                                                                                 *----------------------------------------------------*/

                                                                                if (gyroX > gyroMaxX)
                                                                                {
                                                                                    gyroMaxX = gyroX;
                                                                                }

                                                                                if (gyroY > gyroMaxY)
                                                                                {
                                                                                    gyroMaxY = gyroY;
                                                                                }

                                                                                if (gyroZ > gyroMaxZ)
                                                                                {
                                                                                    gyroMaxZ = gyroZ;
                                                                                }


                                                                                /*-----------------------------------------------------
                                                                                 * Next sample
                                                                                 *----------------------------------------------------*/

                                                                                sampleCount++;
                                                                            }


                                                                            /*=========================================================
                                                                             * Calculate Average Bias
                                                                             *=========================================================*/

                                                                            gyroBiasX = (int32_t)(gyroSumX / 1000LL);

                                                                            gyroBiasY = (int32_t)(gyroSumY / 1000LL);

                                                                            gyroBiasZ = (int32_t)(gyroSumZ / 1000LL);


                                                                            /*=========================================================
                                                                             * Convert Bias to °/s
                                                                             *
                                                                             * ±250 dps:
                                                                             *
                                                                             * 131 LSB / °/s
                                                                             *=========================================================*/

                                                                            gyroBiasXdps =
                                                                                (float)gyroBiasX / 131.0f;

                                                                            gyroBiasYdps =
                                                                                (float)gyroBiasY / 131.0f;

                                                                            gyroBiasZdps =
                                                                                (float)gyroBiasZ / 131.0f;


                                                                            /*=========================================================
                                                                             * Print Calibration Statistics
                                                                             *=========================================================*/

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    "\r\n================================\r\n");

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    "CALIBRATION RESULTS\r\n");

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    "================================\r\n");


                                                                            sprintf(message,
                                                                                    "Samples : %lu\r\n\r\n",
                                                                                    sampleCount);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            /*---------------------------------------------------------
                                                                             * Gyro X
                                                                             *--------------------------------------------------------*/

                                                                            sprintf(message,
                                                                                    "GX Average : %ld raw\r\n",
                                                                                    gyroBiasX);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "GX Minimum : %d raw\r\n",
                                                                                    gyroMinX);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "GX Maximum : %d raw\r\n\r\n",
                                                                                    gyroMaxX);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            /*---------------------------------------------------------
                                                                             * Gyro Y
                                                                             *--------------------------------------------------------*/

                                                                            sprintf(message,
                                                                                    "GY Average : %ld raw\r\n",
                                                                                    gyroBiasY);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "GY Minimum : %d raw\r\n",
                                                                                    gyroMinY);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "GY Maximum : %d raw\r\n\r\n",
                                                                                    gyroMaxY);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            /*---------------------------------------------------------
                                                                             * Gyro Z
                                                                             *--------------------------------------------------------*/

                                                                            sprintf(message,
                                                                                    "GZ Average : %ld raw\r\n",
                                                                                    gyroBiasZ);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "GZ Minimum : %d raw\r\n",
                                                                                    gyroMinZ);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "GZ Maximum : %d raw\r\n\r\n",
                                                                                    gyroMaxZ);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            /*---------------------------------------------------------
                                                                             * Bias in Physical Units
                                                                             *--------------------------------------------------------*/

                                                                            sprintf(message,
                                                                                    "Bias X : %+.3f dps\r\n",
                                                                                    gyroBiasXdps);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "Bias Y : %+.3f dps\r\n",
                                                                                    gyroBiasYdps);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            sprintf(message,
                                                                                    "Bias Z : %+.3f dps\r\n",
                                                                                    gyroBiasZdps);

                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    message);


                                                                            /*=========================================================
                                                                             * Reset FIFO Before Corrected Output
                                                                             *=========================================================*/

                                                                            if (MPU6050_ResetFIFO(&hi2c1) != HAL_OK)
                                                                            {
                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                        "FIFO Reset Before Corrected Output Failed\r\n");

                                                                                while (1);
                                                                            }


                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                    "\r\nStarting Corrected Gyro Output...\r\n");


                                                                            lastPrintTime = HAL_GetTick();


                                                                            /*=========================================================
                                                                             * Continuous Corrected Gyro Output
                                                                             *=========================================================*/

                                                                            while (1)
                                                                            {
                                                                                /*-----------------------------------------------------
                                                                                 * FIFO Count
                                                                                 *----------------------------------------------------*/

                                                                                if (MPU6050_GetFIFOCount(&hi2c1,
                                                                                                         &fifoCount) != HAL_OK)
                                                                                {
                                                                                    continue;
                                                                                }


                                                                                /*-----------------------------------------------------
                                                                                 * Interrupt Status
                                                                                 *----------------------------------------------------*/

                                                                                if (MPU6050_GetInterruptStatus(&hi2c1,
                                                                                                               &intStatus) != HAL_OK)
                                                                                {
                                                                                    continue;
                                                                                }


                                                                                /*-----------------------------------------------------
                                                                                 * Overflow
                                                                                 *----------------------------------------------------*/

                                                                                if (intStatus & MPU6050_FIFO_OFLOW_INT_Msk)
                                                                                {
                                                                                    if (MPU6050_ResetFIFO(&hi2c1) != HAL_OK)
                                                                                    {
                                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                                "FIFO Reset Failed\r\n");

                                                                                        while (1);
                                                                                    }

                                                                                    continue;
                                                                                }


                                                                                /*-----------------------------------------------------
                                                                                 * Wait for Complete Gyro Sample
                                                                                 *----------------------------------------------------*/

                                                                                if (fifoCount < 6U)
                                                                                {
                                                                                    continue;
                                                                                }


                                                                                /*-----------------------------------------------------
                                                                                 * Read Gyro Sample
                                                                                 *----------------------------------------------------*/

                                                                                if (MPU6050_ReadFIFOBuffer(&hi2c1,
                                                                                                           gyroBuffer,
                                                                                                           6U) != HAL_OK)
                                                                                {
                                                                                    continue;
                                                                                }


                                                                                /*-----------------------------------------------------
                                                                                 * Decode
                                                                                 *----------------------------------------------------*/

                                                                                int16_t gyroX =
                                                                                    (int16_t)(((uint16_t)gyroBuffer[0] << 8U) |
                                                                                               gyroBuffer[1]);


                                                                                int16_t gyroY =
                                                                                    (int16_t)(((uint16_t)gyroBuffer[2] << 8U) |
                                                                                               gyroBuffer[3]);


                                                                                int16_t gyroZ =
                                                                                    (int16_t)(((uint16_t)gyroBuffer[4] << 8U) |
                                                                                               gyroBuffer[5]);


                                                                                /*-----------------------------------------------------
                                                                                 * Remove Bias and Convert to °/s
                                                                                 *----------------------------------------------------*/

                                                                                gyroXdps =
                                                                                    ((float)gyroX - (float)gyroBiasX) / 131.0f;


                                                                                gyroYdps =
                                                                                    ((float)gyroY - (float)gyroBiasY) / 131.0f;


                                                                                gyroZdps =
                                                                                    ((float)gyroZ - (float)gyroBiasZ) / 131.0f;


                                                                                /*-----------------------------------------------------
                                                                                 * Print Every 100 ms
                                                                                 *----------------------------------------------------*/

                                                                                if ((HAL_GetTick() - lastPrintTime) >= 100U)
                                                                                {
                                                                                    lastPrintTime = HAL_GetTick();


                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                            "\r\n--------------------------------\r\n");


                                                                                    sprintf(message,
                                                                                            "Corrected Gyro X : %+.3f dps\r\n",
                                                                                            gyroXdps);

                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                            message);


                                                                                    sprintf(message,
                                                                                            "Corrected Gyro Y : %+.3f dps\r\n",
                                                                                            gyroYdps);

                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                            message);


                                                                                    sprintf(message,
                                                                                            "Corrected Gyro Z : %+.3f dps\r\n",
                                                                                            gyroZdps);

                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                            message);
                                                                                }
                                                                            }

                                                                        #endif




                                                                            /*==============================================================================
                                                                             * TEST 7.14A : Accelerometer Orientation Measurement
                                                                             *==============================================================================
                                                                             *
                                                                             * Objective
                                                                             * ---------
                                                                             * Measure the average accelerometer output in six known orientations.
                                                                             *
                                                                             * Positions:
                                                                             *
                                                                             *     +X UP
                                                                             *     -X UP
                                                                             *     +Y UP
                                                                             *     -Y UP
                                                                             *     +Z UP
                                                                             *     -Z UP
                                                                             *
                                                                             * Each position:
                                                                             *
                                                                             *     200 samples
                                                                             *
                                                                             * Settling time:
                                                                             *
                                                                             *     5 seconds
                                                                             *
                                                                             * Configuration:
                                                                             *
                                                                             *     Accelerometer : ±2 g
                                                                             *
                                                                             * IMPORTANT:
                                                                             * Keep the sensor completely stationary while samples are collected.
                                                                             *
                                                                             *===========================================================================*/

                                                                            #if 0

                                                                                MPU6050_Accel_t accel;

                                                                                int64_t sumX;
                                                                                int64_t sumY;
                                                                                int64_t sumZ;

                                                                                int32_t avgX;
                                                                                int32_t avgY;
                                                                                int32_t avgZ;

                                                                                uint32_t sampleCount;

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
                                                                                 *
                                                                                 * 16384 LSB/g
                                                                                 *--------------------------------------------------------*/

                                                                                if (MPU6050_SetAccelRange(&hi2c1,
                                                                                                          MPU6050_ACCEL_RANGE_2G) != HAL_OK)
                                                                                {
                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                            "Accel Range Configuration Failed\r\n");

                                                                                    while (1);
                                                                                }


                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                        "Accelerometer configured for ±2 g\r\n");


                                                                                /*---------------------------------------------------------
                                                                                 * Allow sensor to settle after initialization
                                                                                 *--------------------------------------------------------*/

                                                                                HAL_Delay(500);


                                                                                /*=========================================================
                                                                                 * Helper Macro
                                                                                 *
                                                                                 * Collect 200 accelerometer samples and calculate average.
                                                                                 *=========================================================*/

                                                                            #define MEASURE_ACCEL_ORIENTATION(POSITION_NAME)                 \
                                                                                                                                             \
                                                                                do                                                           \
                                                                                {                                                            \
                                                                                    sumX = 0;                                                \
                                                                                    sumY = 0;                                                \
                                                                                    sumZ = 0;                                                \
                                                                                    sampleCount = 0;                                        \
                                                                                                                                             \
                                                                                    BSP_UART_TransmitString(&huart2,                         \
                                                                                                            "\r\nPlace sensor: "              \
                                                                                                            POSITION_NAME "\r\n");            \
                                                                                                                                             \
                                                                                    BSP_UART_TransmitString(&huart2,                         \
                                                                                                            "Waiting 5 seconds...\r\n");      \
                                                                                                                                             \
                                                                                    HAL_Delay(5000);                                         \
                                                                                                                                             \
                                                                                    BSP_UART_TransmitString(&huart2,                         \
                                                                                                            "Collecting 200 samples...\r\n");\
                                                                                                                                             \
                                                                                    while (sampleCount < 200U)                               \
                                                                                    {                                                        \
                                                                                        if (MPU6050_ReadAccel(&hi2c1,                        \
                                                                                                              &accel) != HAL_OK)              \
                                                                                        {                                                    \
                                                                                            continue;                                        \
                                                                                        }                                                    \
                                                                                                                                             \
                                                                                        sumX += accel.x;                                     \
                                                                                        sumY += accel.y;                                     \
                                                                                        sumZ += accel.z;                                     \
                                                                                                                                             \
                                                                                        sampleCount++;                                       \
                                                                                                                                             \
                                                                                        HAL_Delay(10);                                       \
                                                                                    }                                                        \
                                                                                                                                             \
                                                                                    avgX = (int32_t)(sumX / 200LL);                           \
                                                                                    avgY = (int32_t)(sumY / 200LL);                           \
                                                                                    avgZ = (int32_t)(sumZ / 200LL);                           \
                                                                                                                                             \
                                                                                    BSP_UART_TransmitString(&huart2,                         \
                                                                                                            "\r\nResult:\r\n");               \
                                                                                                                                             \
                                                                                    sprintf(message,                                         \
                                                                                            "Accel X : %ld raw\r\n",                         \
                                                                                            avgX);                                           \
                                                                                                                                             \
                                                                                    BSP_UART_TransmitString(&huart2,                         \
                                                                                                            message);                        \
                                                                                                                                             \
                                                                                    sprintf(message,                                         \
                                                                                            "Accel Y : %ld raw\r\n",                         \
                                                                                            avgY);                                           \
                                                                                                                                             \
                                                                                    BSP_UART_TransmitString(&huart2,                         \
                                                                                                            message);                        \
                                                                                                                                             \
                                                                                    sprintf(message,                                         \
                                                                                            "Accel Z : %ld raw\r\n",                         \
                                                                                            avgZ);                                           \
                                                                                                                                             \
                                                                                    BSP_UART_TransmitString(&huart2,                         \
                                                                                                            message);                        \
                                                                                                                                             \
                                                                                } while (0)


                                                                                /*=========================================================
                                                                                 * +X UP
                                                                                 *=========================================================*/

                                                                                MEASURE_ACCEL_ORIENTATION("+X UP");


                                                                                /*=========================================================
                                                                                 * -X UP
                                                                                 *=========================================================*/

                                                                                MEASURE_ACCEL_ORIENTATION("-X UP");


                                                                                /*=========================================================
                                                                                 * +Y UP
                                                                                 *=========================================================*/

                                                                                MEASURE_ACCEL_ORIENTATION("+Y UP");


                                                                                /*=========================================================
                                                                                 * -Y UP
                                                                                 *=========================================================*/

                                                                                MEASURE_ACCEL_ORIENTATION("-Y UP");


                                                                                /*=========================================================
                                                                                 * +Z UP
                                                                                 *=========================================================*/

                                                                                MEASURE_ACCEL_ORIENTATION("+Z UP");


                                                                                /*=========================================================
                                                                                 * -Z UP
                                                                                 *=========================================================*/

                                                                                MEASURE_ACCEL_ORIENTATION("-Z UP");


                                                                                /*=========================================================
                                                                                 * End Test
                                                                                 *=========================================================*/

                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                        "\r\n================================\r\n");

                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                        "ACCELEROMETER MEASUREMENT COMPLETE\r\n");

                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                        "================================\r\n");


                                                                            #undef MEASURE_ACCEL_ORIENTATION


                                                                                while (1)
                                                                                {
                                                                                    HAL_Delay(1000);
                                                                                }

                                                                            #endif




                                                                                /*==============================================================================
                                                                                 * TEST 7.14B : Accelerometer Calibration Validation
                                                                                 *==============================================================================
                                                                                 *
                                                                                 * Objective
                                                                                 * ---------
                                                                                 * Validate accelerometer offset and scale calibration using six stationary
                                                                                 * orientations.
                                                                                 *
                                                                                 * Calibration values obtained from multiple stationary iterations:
                                                                                 *
                                                                                 *     Offset X = +678 raw
                                                                                 *     Offset Y = -223 raw
                                                                                 *     Offset Z = -1284 raw
                                                                                 *
                                                                                 *     Scale X = 16237.5 raw/g
                                                                                 *     Scale Y = 16332.7 raw/g
                                                                                 *     Scale Z = 16420.5 raw/g
                                                                                 *
                                                                                 * The calibration is NOT written into the MPU6050 driver.
                                                                                 *
                                                                                 * Each orientation:
                                                                                 *
                                                                                 *     5 seconds settling
                                                                                 *     200 samples
                                                                                 *
                                                                                 *===========================================================================*/

                                                                                #if 0

                                                                                    MPU6050_Accel_t accel;

                                                                                    int64_t sumX;
                                                                                    int64_t sumY;
                                                                                    int64_t sumZ;

                                                                                    int32_t avgX;
                                                                                    int32_t avgY;
                                                                                    int32_t avgZ;

                                                                                    float correctedX;
                                                                                    float correctedY;
                                                                                    float correctedZ;

                                                                                    float magnitude;

                                                                                    uint32_t sampleCount;

                                                                                    char message[160];


                                                                                    /*---------------------------------------------------------
                                                                                     * Calibration Constants
                                                                                     *--------------------------------------------------------*/

                                                                                    const float ACCEL_OFFSET_X = 678.0f;
                                                                                    const float ACCEL_OFFSET_Y = -223.0f;
                                                                                    const float ACCEL_OFFSET_Z = -1284.0f;

                                                                                    const float ACCEL_SCALE_X = 16237.5f;
                                                                                    const float ACCEL_SCALE_Y = 16332.7f;
                                                                                    const float ACCEL_SCALE_Z = 16420.5f;


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

                                                                                    if (MPU6050_SetAccelRange(&hi2c1,
                                                                                                              MPU6050_ACCEL_RANGE_2G) != HAL_OK)
                                                                                    {
                                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                                "Accel Range Configuration Failed\r\n");

                                                                                        while (1);
                                                                                    }


                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                            "Accelerometer configured for ±2 g\r\n");


                                                                                    HAL_Delay(500);


                                                                                    /*=========================================================
                                                                                     * Measurement Macro
                                                                                     *=========================================================*/

                                                                                #define VALIDATE_ACCEL_ORIENTATION(POSITION_NAME)                  \
                                                                                                                                                  \
                                                                                    do                                                            \
                                                                                    {                                                             \
                                                                                        sumX = 0;                                                 \
                                                                                        sumY = 0;                                                 \
                                                                                        sumZ = 0;                                                 \
                                                                                        sampleCount = 0;                                         \
                                                                                                                                                  \
                                                                                        BSP_UART_TransmitString(&huart2,                          \
                                                                                                                "\r\n==============================\r\n"); \
                                                                                                                                                  \
                                                                                        BSP_UART_TransmitString(&huart2,                          \
                                                                                                                POSITION_NAME "\r\n");            \
                                                                                                                                                  \
                                                                                        BSP_UART_TransmitString(&huart2,                          \
                                                                                                                "Waiting 5 seconds...\r\n");       \
                                                                                                                                                  \
                                                                                        HAL_Delay(5000);                                          \
                                                                                                                                                  \
                                                                                        BSP_UART_TransmitString(&huart2,                          \
                                                                                                                "Collecting 200 samples...\r\n"); \
                                                                                                                                                  \
                                                                                        while (sampleCount < 200U)                                \
                                                                                        {                                                         \
                                                                                            if (MPU6050_ReadAccel(&hi2c1,                         \
                                                                                                                  &accel) != HAL_OK)               \
                                                                                            {                                                     \
                                                                                                continue;                                         \
                                                                                            }                                                     \
                                                                                                                                                  \
                                                                                            sumX += accel.x;                                      \
                                                                                            sumY += accel.y;                                      \
                                                                                            sumZ += accel.z;                                      \
                                                                                                                                                  \
                                                                                            sampleCount++;                                        \
                                                                                                                                                  \
                                                                                            HAL_Delay(10);                                        \
                                                                                        }                                                         \
                                                                                                                                                  \
                                                                                        avgX = (int32_t)(sumX / 200LL);                            \
                                                                                        avgY = (int32_t)(sumY / 200LL);                            \
                                                                                        avgZ = (int32_t)(sumZ / 200LL);                            \
                                                                                                                                                  \
                                                                                        /*----------------------------------------------------- \
                                                                                         * Apply offset and scale calibration                   \
                                                                                         *-----------------------------------------------------*/ \
                                                                                                                                                  \
                                                                                        correctedX =                                             \
                                                                                            ((float)avgX - ACCEL_OFFSET_X) / ACCEL_SCALE_X;       \
                                                                                                                                                  \
                                                                                        correctedY =                                             \
                                                                                            ((float)avgY - ACCEL_OFFSET_Y) / ACCEL_SCALE_Y;       \
                                                                                                                                                  \
                                                                                        correctedZ =                                             \
                                                                                            ((float)avgZ - ACCEL_OFFSET_Z) / ACCEL_SCALE_Z;       \
                                                                                                                                                  \
                                                                                        /*----------------------------------------------------- \
                                                                                         * Calculate total acceleration magnitude                \
                                                                                         *-----------------------------------------------------*/ \
                                                                                                                                                  \
                                                                                        magnitude = sqrtf(                                         \
                                                                                            correctedX * correctedX +                             \
                                                                                            correctedY * correctedY +                             \
                                                                                            correctedZ * correctedZ);                             \
                                                                                                                                                  \
                                                                                        /*----------------------------------------------------- \
                                                                                         * Raw values                                             \
                                                                                         *-----------------------------------------------------*/ \
                                                                                                                                                  \
                                                                                        BSP_UART_TransmitString(&huart2,                          \
                                                                                                                "\r\nRAW:\r\n");                   \
                                                                                                                                                  \
                                                                                        sprintf(message,                                          \
                                                                                                "Accel X : %ld raw\r\n",                          \
                                                                                                avgX);                                            \
                                                                                        BSP_UART_TransmitString(&huart2, message);                \
                                                                                                                                                  \
                                                                                        sprintf(message,                                          \
                                                                                                "Accel Y : %ld raw\r\n",                          \
                                                                                                avgY);                                            \
                                                                                        BSP_UART_TransmitString(&huart2, message);                \
                                                                                                                                                  \
                                                                                        sprintf(message,                                          \
                                                                                                "Accel Z : %ld raw\r\n",                          \
                                                                                                avgZ);                                            \
                                                                                        BSP_UART_TransmitString(&huart2, message);                \
                                                                                                                                                  \
                                                                                        /*----------------------------------------------------- \
                                                                                         * Corrected values                                      \
                                                                                         *-----------------------------------------------------*/ \
                                                                                                                                                  \
                                                                                        BSP_UART_TransmitString(&huart2,                          \
                                                                                                                "\r\nCORRECTED:\r\n");             \
                                                                                                                                                  \
                                                                                        sprintf(message,                                          \
                                                                                                "Accel X : %+0.4f g\r\n",                         \
                                                                                                correctedX);                                      \
                                                                                        BSP_UART_TransmitString(&huart2, message);                \
                                                                                                                                                  \
                                                                                        sprintf(message,                                          \
                                                                                                "Accel Y : %+0.4f g\r\n",                         \
                                                                                                correctedY);                                      \
                                                                                        BSP_UART_TransmitString(&huart2, message);                \
                                                                                                                                                  \
                                                                                        sprintf(message,                                          \
                                                                                                "Accel Z : %+0.4f g\r\n",                         \
                                                                                                correctedZ);                                      \
                                                                                        BSP_UART_TransmitString(&huart2, message);                \
                                                                                                                                                  \
                                                                                        sprintf(message,                                          \
                                                                                                "\r\nMagnitude : %.4f g\r\n",                    \
                                                                                                magnitude);                                       \
                                                                                        BSP_UART_TransmitString(&huart2, message);                \
                                                                                                                                                  \
                                                                                    } while (0)


                                                                                    /*=========================================================
                                                                                     * +X UP
                                                                                     *=========================================================*/

                                                                                    VALIDATE_ACCEL_ORIENTATION("+X UP");


                                                                                    /*=========================================================
                                                                                     * -X UP
                                                                                     *=========================================================*/

                                                                                    VALIDATE_ACCEL_ORIENTATION("-X UP");


                                                                                    /*=========================================================
                                                                                     * +Y UP
                                                                                     *=========================================================*/

                                                                                    VALIDATE_ACCEL_ORIENTATION("+Y UP");


                                                                                    /*=========================================================
                                                                                     * -Y UP
                                                                                     *=========================================================*/

                                                                                    VALIDATE_ACCEL_ORIENTATION("-Y UP");


                                                                                    /*=========================================================
                                                                                     * +Z UP
                                                                                     *=========================================================*/

                                                                                    VALIDATE_ACCEL_ORIENTATION("+Z UP");


                                                                                    /*=========================================================
                                                                                     * -Z UP
                                                                                     *=========================================================*/

                                                                                    VALIDATE_ACCEL_ORIENTATION("-Z UP");


                                                                                    /*=========================================================
                                                                                     * Test Complete
                                                                                     *=========================================================*/

                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                            "\r\n========================================\r\n");

                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                            "ACCELEROMETER CALIBRATION VALIDATION COMPLETE\r\n");

                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                            "========================================\r\n");


                                                                                #undef VALIDATE_ACCEL_ORIENTATION


                                                                                    while (1)
                                                                                    {
                                                                                        HAL_Delay(1000);
                                                                                    }

                                                                                #endif
                                                                                    /*==============================================================================
                                                                                     * TEST 7.15 : Calibrated Accelerometer Read
                                                                                     *==============================================================================
                                                                                     *
                                                                                     * Objective
                                                                                     * ---------
                                                                                     * Verify that MPU6050_ReadAccelCalibrated() returns accelerometer data
                                                                                     * in g after applying the provisional calibration.
                                                                                     *
                                                                                     *===========================================================================*/

                                                                                    #if 0

                                                                                        MPU6050_AccelCalibrated_t accel;

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
                                                                                         * Configure Accelerometer
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

                                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                                "Accelerometer configured for ±2 g\r\n");


                                                                                        HAL_Delay(1000);


                                                                                        /*---------------------------------------------------------
                                                                                         * Continuous calibrated accelerometer read
                                                                                         *--------------------------------------------------------*/

                                                                                        while (1)
                                                                                        {
                                                                                            if (MPU6050_ReadAccelCalibrated(&hi2c1,
                                                                                                                            &accel) != HAL_OK)
                                                                                            {
                                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                                        "Calibrated Accel Read Failed\r\n");

                                                                                                HAL_Delay(500);

                                                                                                continue;
                                                                                            }


                                                                                            sprintf(message,
                                                                                                    "\r\nAccel X : %+0.4f g\r\n",
                                                                                                    accel.x);

                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    message);


                                                                                            sprintf(message,
                                                                                                    "Accel Y : %+0.4f g\r\n",
                                                                                                    accel.y);

                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    message);


                                                                                            sprintf(message,
                                                                                                    "Accel Z : %+0.4f g\r\n",
                                                                                                    accel.z);

                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    message);


                                                                                            HAL_Delay(500);
                                                                                        }

                                                                                    #endif


                                                                                        /*==============================================================================
                                                                                         * TEST 7.16 : Gyroscope Raw Bias Measurement
                                                                                         *==============================================================================
                                                                                         *
                                                                                         * Objective
                                                                                         * ---------
                                                                                         * Measure the stationary raw gyroscope bias.
                                                                                         *
                                                                                         * No calibration or bias correction is applied in this test.
                                                                                         *
                                                                                         * MPU6050 gyro range:
                                                                                         *
                                                                                         *     ±250 °/s
                                                                                         *
                                                                                         * Sensitivity:
                                                                                         *
                                                                                         *     131 LSB/(°/s)
                                                                                         *
                                                                                         * Therefore:
                                                                                         *
                                                                                         *     dps = raw / 131.0
                                                                                         *
                                                                                         *===========================================================================*/

                                                                                        #if 0

                                                                                            MPU6050_Gyro_t gyro;

                                                                                            int64_t sumX = 0;
                                                                                            int64_t sumY = 0;
                                                                                            int64_t sumZ = 0;

                                                                                            int32_t avgX;
                                                                                            int32_t avgY;
                                                                                            int32_t avgZ;

                                                                                            float biasX_dps;
                                                                                            float biasY_dps;
                                                                                            float biasZ_dps;

                                                                                            uint32_t sampleCount = 0;

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
                                                                                             * Configure Gyroscope
                                                                                             *
                                                                                             * ±250 °/s
                                                                                             *--------------------------------------------------------*/

                                                                                            if (MPU6050_SetGyroRange(&hi2c1,
                                                                                                                     MPU6050_GYRO_RANGE_250DPS) != HAL_OK)
                                                                                            {
                                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                                        "Gyro Range Configuration Failed\r\n");

                                                                                                while (1);
                                                                                            }

                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    "Gyroscope configured for ±250 dps\r\n");


                                                                                            /*---------------------------------------------------------
                                                                                             * Allow sensor to settle
                                                                                             *--------------------------------------------------------*/

                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    "\r\nKEEP SENSOR COMPLETELY STILL\r\n");

                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    "Waiting 5 seconds...\r\n");

                                                                                            HAL_Delay(5000);


                                                                                            /*---------------------------------------------------------
                                                                                             * Collect samples
                                                                                             *--------------------------------------------------------*/

                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    "Collecting 1000 samples...\r\n");

                                                                                            while (sampleCount < 1000U)
                                                                                            {
                                                                                                if (MPU6050_ReadGyroRaw(&hi2c1,
                                                                                                                        &gyro) != HAL_OK)
                                                                                                {
                                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                                            "Gyro Read Failed\r\n");

                                                                                                    continue;
                                                                                                }

                                                                                                sumX += gyro.x;
                                                                                                sumY += gyro.y;
                                                                                                sumZ += gyro.z;

                                                                                                sampleCount++;

                                                                                                HAL_Delay(5);
                                                                                            }


                                                                                            /*---------------------------------------------------------
                                                                                             * Calculate average raw bias
                                                                                             *--------------------------------------------------------*/

                                                                                            avgX = (int32_t)(sumX / 1000LL);
                                                                                            avgY = (int32_t)(sumY / 1000LL);
                                                                                            avgZ = (int32_t)(sumZ / 1000LL);


                                                                                            /*---------------------------------------------------------
                                                                                             * Convert raw bias to °/s
                                                                                             *
                                                                                             * ±250 dps = 131 LSB/(°/s)
                                                                                             *--------------------------------------------------------*/

                                                                                            biasX_dps = (float)avgX / 131.0f;
                                                                                            biasY_dps = (float)avgY / 131.0f;
                                                                                            biasZ_dps = (float)avgZ / 131.0f;


                                                                                            /*---------------------------------------------------------
                                                                                             * Print results
                                                                                             *--------------------------------------------------------*/

                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    "\r\n========================================\r\n");

                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    "GYROSCOPE RAW BIAS MEASUREMENT\r\n");

                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    "========================================\r\n");


                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    "\r\nRAW AVERAGE:\r\n");


                                                                                            sprintf(message,
                                                                                                    "Gyro X : %ld raw\r\n",
                                                                                                    avgX);

                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    message);


                                                                                            sprintf(message,
                                                                                                    "Gyro Y : %ld raw\r\n",
                                                                                                    avgY);

                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    message);


                                                                                            sprintf(message,
                                                                                                    "Gyro Z : %ld raw\r\n",
                                                                                                    avgZ);

                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    message);


                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    "\r\nBIAS:\r\n");


                                                                                            sprintf(message,
                                                                                                    "Gyro X : %+0.4f dps\r\n",
                                                                                                    biasX_dps);

                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    message);


                                                                                            sprintf(message,
                                                                                                    "Gyro Y : %+0.4f dps\r\n",
                                                                                                    biasY_dps);

                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    message);


                                                                                            sprintf(message,
                                                                                                    "Gyro Z : %+0.4f dps\r\n",
                                                                                                    biasZ_dps);

                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    message);


                                                                                            BSP_UART_TransmitString(&huart2,
                                                                                                                    "\r\nMeasurement Complete.\r\n");


                                                                                            while (1)
                                                                                            {
                                                                                                HAL_Delay(1000);
                                                                                            }

                                                                                        #endif


                                                                                            /*==============================================================================
                                                                                             * TEST 7.17 : Calibrated Gyroscope Stationary Verification
                                                                                             *==============================================================================
                                                                                             *
                                                                                             * Objective
                                                                                             * ---------
                                                                                             * Verify that the provisional gyro bias correction produces approximately
                                                                                             * 0 °/s when the MPU6050 is stationary.
                                                                                             *
                                                                                             * Gyro configuration:
                                                                                             *
                                                                                             *     ±250 °/s
                                                                                             *     131 LSB/(°/s)
                                                                                             *
                                                                                             * Provisional bias:
                                                                                             *
                                                                                             *     X = -645.5 raw
                                                                                             *     Y = -160.5 raw
                                                                                             *     Z = -255.0 raw
                                                                                             *
                                                                                             *===========================================================================*/

                                                                                            #if 1

                                                                                                MPU6050_GyroCalibrated_t gyro;

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
                                                                                                 * Configure Gyroscope
                                                                                                 *
                                                                                                 * ±250 °/s
                                                                                                 *--------------------------------------------------------*/

                                                                                                if (MPU6050_SetGyroRange(&hi2c1,
                                                                                                                         MPU6050_GYRO_RANGE_250DPS) != HAL_OK)
                                                                                                {
                                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                                            "Gyro Range Configuration Failed\r\n");

                                                                                                    while (1);
                                                                                                }


                                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                                        "Gyroscope configured for ±250 dps\r\n");


                                                                                                /*---------------------------------------------------------
                                                                                                 * Allow sensor to settle
                                                                                                 *--------------------------------------------------------*/

                                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                                        "\r\nKEEP SENSOR COMPLETELY STILL\r\n");

                                                                                                BSP_UART_TransmitString(&huart2,
                                                                                                                        "Waiting 5 seconds...\r\n");

                                                                                                HAL_Delay(5000);


                                                                                                /*---------------------------------------------------------
                                                                                                 * Continuous calibrated gyro read
                                                                                                 *--------------------------------------------------------*/

                                                                                                while (1)
                                                                                                {
                                                                                                    if (MPU6050_ReadGyroCalibrated(&hi2c1,
                                                                                                                                   &gyro) != HAL_OK)
                                                                                                    {
                                                                                                        BSP_UART_TransmitString(&huart2,
                                                                                                                                "Calibrated Gyro Read Failed\r\n");

                                                                                                        HAL_Delay(500);

                                                                                                        continue;
                                                                                                    }


                                                                                                    sprintf(message,
                                                                                                            "\r\nCorrected Gyro X : %+0.3f dps\r\n",
                                                                                                            gyro.x);

                                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                                            message);


                                                                                                    sprintf(message,
                                                                                                            "Corrected Gyro Y : %+0.3f dps\r\n",
                                                                                                            gyro.y);

                                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                                            message);


                                                                                                    sprintf(message,
                                                                                                            "Corrected Gyro Z : %+0.3f dps\r\n",
                                                                                                            gyro.z);

                                                                                                    BSP_UART_TransmitString(&huart2,
                                                                                                                            message);


                                                                                                    HAL_Delay(500);
                                                                                                }

                                                                                            #endif













}
