#ifndef MPU6050_UTILS_H
#define MPU6050_UTILS_H

#include "mpu6050_types.h"

const char *MPU6050_GetAccelRangeString(MPU6050_AccelRange_t range);

const char *MPU6050_GetGyroRangeString(MPU6050_GyroRange_t range);

const char *MPU6050_GetDLPFString(MPU6050_DLPF_t dlpf);

const char *MPU6050_GetClockSourceString(MPU6050_ClockSource_t source);

#endif
