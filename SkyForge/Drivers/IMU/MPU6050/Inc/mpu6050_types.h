#ifndef MPU6050_TYPES_H
#define MPU6050_TYPES_H

#include <stdint.h>

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
} MPU6050_Accel_t;

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
} MPU6050_Gyro_t;


/*=========================================================
 * Calibrated Gyroscope Data
 *
 * Units:
 *     X, Y, Z = degrees per second (°/s)
 *=========================================================*/

typedef struct
{
    float x;
    float y;
    float z;

} MPU6050_GyroCalibrated_t;

typedef struct
{
    int16_t raw;
    float temperature;
} MPU6050_Temp_t;

/*=========================================================
 * Calibrated Accelerometer Data
 *=========================================================*/
typedef struct
{
    float x;
    float y;
    float z;

} MPU6050_AccelCalibrated_t;

typedef struct
{
    MPU6050_Accel_t accel;
    MPU6050_Temp_t  temp;
    MPU6050_Gyro_t  gyro;
} MPU6050_FIFOPacket_t;


typedef enum
{
    MPU6050_ACCEL_RANGE_2G = 0,
    MPU6050_ACCEL_RANGE_4G,
    MPU6050_ACCEL_RANGE_8G,
    MPU6050_ACCEL_RANGE_16G
} MPU6050_AccelRange_t;


/*=========================================================
 * Calibrated IMU Data
 *
 * Accel : g
 * Gyro  : degrees per second
 * Temp  : degrees Celsius
 *=========================================================*/

typedef struct
{
    MPU6050_AccelCalibrated_t accel;
    MPU6050_GyroCalibrated_t  gyro;
    MPU6050_Temp_t             temp;

} MPU6050_IMUData_t;

typedef enum
{
    MPU6050_GYRO_RANGE_250DPS = 0,
    MPU6050_GYRO_RANGE_500DPS,
    MPU6050_GYRO_RANGE_1000DPS,
    MPU6050_GYRO_RANGE_2000DPS
} MPU6050_GyroRange_t;

typedef enum
{
    MPU6050_DLPF_BW_260HZ = 0,
    MPU6050_DLPF_BW_184HZ,
    MPU6050_DLPF_BW_94HZ,
    MPU6050_DLPF_BW_44HZ,
    MPU6050_DLPF_BW_21HZ,
    MPU6050_DLPF_BW_10HZ,
    MPU6050_DLPF_BW_5HZ
} MPU6050_DLPF_t;





typedef enum
{
    MPU6050_CLOCK_INTERNAL = 0,
    MPU6050_CLOCK_PLL_XGYRO,
    MPU6050_CLOCK_PLL_YGYRO,
    MPU6050_CLOCK_PLL_ZGYRO,
    MPU6050_CLOCK_PLL_EXT32K,
    MPU6050_CLOCK_PLL_EXT19M,
    MPU6050_CLOCK_RESERVED,
    MPU6050_CLOCK_STOP

} MPU6050_ClockSource_t;

#endif /* MPU6050_TYPES_H */
