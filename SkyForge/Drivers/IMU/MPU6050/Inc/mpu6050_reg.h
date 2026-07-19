#ifndef MPU6050_REG_H
#define MPU6050_REG_H

/*=========================================================
 * Device Address
 *========================================================*/

#define MPU6050_I2C_ADDR_LOW          (0x68U << 1)
#define MPU6050_I2C_ADDR_HIGH         (0x69U << 1)

/*=========================================================
 * PWR_MGMT_1 Register Bits
 *========================================================*/

#define MPU6050_DEVICE_RESET          (1U << 7)
#define MPU6050_SLEEP                 (1U << 6)

/*=========================================================
 * Register Map
 *========================================================*/

#define MPU6050_REG_SELF_TEST_X       0x0D
#define MPU6050_REG_SELF_TEST_Y       0x0E
#define MPU6050_REG_SELF_TEST_Z       0x0F
#define MPU6050_REG_SELF_TEST_A       0x10

#define MPU6050_REG_SMPLRT_DIV        0x19
#define MPU6050_REG_CONFIG            0x1A
//#define MPU6050_REG_GYRO_CONFIG       0x1B
#define MPU6050_REG_GYRO_CONFIG       0x1BU
#define MPU6050_REG_ACCEL_CONFIG      0x1C

/*=========================================================
 * Accelerometer Configuration Register (0x1C)
 *========================================================*/

/* Full Scale Select (AFS_SEL) */

#define MPU6050_ACCEL_FS_SEL_Pos      3U
#define MPU6050_ACCEL_FS_SEL_Msk      (0x03U << MPU6050_ACCEL_FS_SEL_Pos)


/*=========================================================
 * Gyroscope Configuration Register (0x1B)
 *========================================================*/

/* Full Scale Select (FS_SEL) */

#define MPU6050_GYRO_FS_SEL_Pos          3U
#define MPU6050_GYRO_FS_SEL_Msk          (0x03U << MPU6050_GYRO_FS_SEL_Pos)

/*=========================================================
 * ACCEL_CONFIG Register Bits
 *========================================================*/


#define MPU6050_REG_INT_PIN_CFG       0x37
#define MPU6050_REG_INT_ENABLE        0x38

#define MPU6050_REG_ACCEL_XOUT_H      0x3B
#define MPU6050_REG_ACCEL_XOUT_L      0x3C
#define MPU6050_REG_ACCEL_YOUT_H      0x3D
#define MPU6050_REG_ACCEL_YOUT_L      0x3E
#define MPU6050_REG_ACCEL_ZOUT_H      0x3F
#define MPU6050_REG_ACCEL_ZOUT_L      0x40

#define MPU6050_REG_TEMP_OUT_H        0x41
#define MPU6050_REG_TEMP_OUT_L        0x42

#define MPU6050_REG_GYRO_XOUT_H       0x43
#define MPU6050_REG_GYRO_XOUT_L       0x44
#define MPU6050_REG_GYRO_YOUT_H       0x45
#define MPU6050_REG_GYRO_YOUT_L       0x46
#define MPU6050_REG_GYRO_ZOUT_H       0x47
#define MPU6050_REG_GYRO_ZOUT_L       0x48

#define MPU6050_REG_PWR_MGMT_1        0x6B
#define MPU6050_REG_PWR_MGMT_2        0x6C

/*=========================================================
 * PWR_MGMT_1 Register Bits
 *========================================================*/

#define MPU6050_DEVICE_RESET          (1U << 7)
#define MPU6050_SLEEP                 (1U << 6)

#define MPU6050_REG_WHO_AM_I          0x75

#endif
