#include "mpu6050_utils.h"


const char *MPU6050_GetAccelRangeString(MPU6050_AccelRange_t range)
{
    switch (range)
    {
        case MPU6050_ACCEL_RANGE_2G:
            return "±2g";

        case MPU6050_ACCEL_RANGE_4G:
            return "±4g";

        case MPU6050_ACCEL_RANGE_8G:
            return "±8g";

        case MPU6050_ACCEL_RANGE_16G:
            return "±16g";

        default:
            return "Unknown";
    }
}

const char *MPU6050_GetGyroRangeString(MPU6050_GyroRange_t range)
{
    switch (range)
    {
        case MPU6050_GYRO_RANGE_250DPS:
            return "±250 dps";

        case MPU6050_GYRO_RANGE_500DPS:
            return "±500 dps";

        case MPU6050_GYRO_RANGE_1000DPS:
            return "±1000 dps";

        case MPU6050_GYRO_RANGE_2000DPS:
            return "±2000 dps";

        default:
            return "Unknown";
    }
}

const char *MPU6050_GetDLPFString(MPU6050_DLPF_t dlpf)
{
    switch (dlpf)
    {
        case MPU6050_DLPF_BW_260HZ:
            return "260 Hz";

        case MPU6050_DLPF_BW_184HZ:
            return "184 Hz";

        case MPU6050_DLPF_BW_94HZ:
            return "94 Hz";

        case MPU6050_DLPF_BW_44HZ:
            return "44 Hz";

        case MPU6050_DLPF_BW_21HZ:
            return "21 Hz";

        case MPU6050_DLPF_BW_10HZ:
            return "10 Hz";

        case MPU6050_DLPF_BW_5HZ:
            return "5 Hz";

        default:
            return "Unknown";
    }

}
const char *MPU6050_GetClockSourceString(
        MPU6050_ClockSource_t source)
    {
        switch (source)
        {
            case MPU6050_CLOCK_INTERNAL:
                return "Internal Oscillator";

            case MPU6050_CLOCK_PLL_XGYRO:
                return "PLL with X Gyro";

            case MPU6050_CLOCK_PLL_YGYRO:
                return "PLL with Y Gyro";

            case MPU6050_CLOCK_PLL_ZGYRO:
                return "PLL with Z Gyro";

            case MPU6050_CLOCK_PLL_EXT32K:
                return "PLL with External 32.768 kHz";

            case MPU6050_CLOCK_PLL_EXT19M:
                return "PLL with External 19.2 MHz";

            case MPU6050_CLOCK_STOP:
                return "Stop Clock";

            default:
                return "Unknown";
        }
    }
