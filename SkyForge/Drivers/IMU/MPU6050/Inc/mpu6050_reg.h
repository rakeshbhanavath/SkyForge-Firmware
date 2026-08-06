#ifndef MPU6050_REG_H
#define MPU6050_REG_H

/*=========================================================
 * Device Address
 *========================================================*/

#define MPU6050_I2C_ADDR_LOW             (0x68U << 1)
#define MPU6050_I2C_ADDR_HIGH            (0x69U << 1)

/*=========================================================
 * Register Addresses
 *========================================================*/

/*---------------- Self-Test Registers ----------------*/

#define MPU6050_REG_SELF_TEST_X          0x0DU
#define MPU6050_REG_SELF_TEST_Y          0x0EU
#define MPU6050_REG_SELF_TEST_Z          0x0FU
#define MPU6050_REG_SELF_TEST_A          0x10U

/*---------------- Sample Rate Divider ----------------*/

#define MPU6050_REG_SMPLRT_DIV           0x19U

/*---------------- Configuration Registers ----------------*/

#define MPU6050_REG_CONFIG               0x1AU
#define MPU6050_REG_GYRO_CONFIG          0x1BU
#define MPU6050_REG_ACCEL_CONFIG         0x1CU

/*---------------- FIFO Registers ----------------*/

#define MPU6050_REG_FIFO_EN              0x23U

/*---------------- Interrupt Registers ----------------*/

#define MPU6050_REG_INT_PIN_CFG          0x37U
#define MPU6050_REG_INT_ENABLE           0x38U
#define MPU6050_REG_INT_STATUS           0x3AU

/*---------------- Accelerometer Output Registers ----------------*/

#define MPU6050_REG_ACCEL_XOUT_H         0x3BU
#define MPU6050_REG_ACCEL_XOUT_L         0x3CU

#define MPU6050_REG_ACCEL_YOUT_H         0x3DU
#define MPU6050_REG_ACCEL_YOUT_L         0x3EU

#define MPU6050_REG_ACCEL_ZOUT_H         0x3FU
#define MPU6050_REG_ACCEL_ZOUT_L         0x40U

/*---------------- Temperature Output Registers ----------------*/

#define MPU6050_REG_TEMP_OUT_H           0x41U
#define MPU6050_REG_TEMP_OUT_L           0x42U

/*---------------- Gyroscope Output Registers ----------------*/

#define MPU6050_REG_GYRO_XOUT_H          0x43U
#define MPU6050_REG_GYRO_XOUT_L          0x44U

#define MPU6050_REG_GYRO_YOUT_H          0x45U
#define MPU6050_REG_GYRO_YOUT_L          0x46U

#define MPU6050_REG_GYRO_ZOUT_H          0x47U
#define MPU6050_REG_GYRO_ZOUT_L          0x48U

/*---------------- User Control Register ----------------*/

#define MPU6050_REG_USER_CTRL            0x6AU

/*---------------- Power Management Registers ----------------*/

#define MPU6050_REG_PWR_MGMT_1           0x6BU
#define MPU6050_REG_PWR_MGMT_2           0x6CU

/*---------------- FIFO Count Registers ----------------*/

#define MPU6050_REG_FIFO_COUNTH          0x72U
#define MPU6050_REG_FIFO_COUNTL          0x73U

/*---------------- FIFO Read/Write Register ----------------*/

#define MPU6050_REG_FIFO_R_W             0x74U

/*---------------- Device Identification ----------------*/

#define MPU6050_REG_WHO_AM_I             0x75U

/*=========================================================
 * PWR_MGMT_1 Register Bits
 *========================================================*/

#define MPU6050_CLKSEL_Pos               0U
#define MPU6050_CLKSEL_Msk               (0x07U << MPU6050_CLKSEL_Pos)

#define MPU6050_SLEEP                    (1U << 6)

#define MPU6050_DEVICE_RESET             (1U << 7)

/*=========================================================
 * CONFIG Register Bits
 *========================================================*/

#define MPU6050_DLPF_CFG_Pos             0U
#define MPU6050_DLPF_CFG_Msk             (0x07U << MPU6050_DLPF_CFG_Pos)

/*=========================================================
 * GYRO_CONFIG Register Bits
 *========================================================*/

#define MPU6050_GYRO_FS_SEL_Pos          3U
#define MPU6050_GYRO_FS_SEL_Msk          (0x03U << MPU6050_GYRO_FS_SEL_Pos)

/*=========================================================
 * ACCEL_CONFIG Register Bits
 *========================================================*/

#define MPU6050_ACCEL_FS_SEL_Pos         3U
#define MPU6050_ACCEL_FS_SEL_Msk         (0x03U << MPU6050_ACCEL_FS_SEL_Pos)

/*=========================================================
 * USER_CTRL Register Bits
 *========================================================*/

#define MPU6050_FIFO_EN_Pos              6U
#define MPU6050_FIFO_EN_Msk              (1U << MPU6050_FIFO_EN_Pos)

#define MPU6050_FIFO_RESET_Pos           2U
#define MPU6050_FIFO_RESET_Msk           (1U << MPU6050_FIFO_RESET_Pos)


/*=========================================================
 * FIFO_EN Register Bits
 *========================================================*/

/* Temperature */

#define MPU6050_FIFO_TEMP_Pos          7U
#define MPU6050_FIFO_TEMP_Msk          (1U << MPU6050_FIFO_TEMP_Pos)

/* Gyroscope */

#define MPU6050_FIFO_XG_Pos            6U
#define MPU6050_FIFO_XG_Msk            (1U << MPU6050_FIFO_XG_Pos)

#define MPU6050_FIFO_YG_Pos            5U
#define MPU6050_FIFO_YG_Msk            (1U << MPU6050_FIFO_YG_Pos)

#define MPU6050_FIFO_ZG_Pos            4U
#define MPU6050_FIFO_ZG_Msk            (1U << MPU6050_FIFO_ZG_Pos)

/* Accelerometer */

#define MPU6050_FIFO_ACCEL_Pos         3U
#define MPU6050_FIFO_ACCEL_Msk         (1U << MPU6050_FIFO_ACCEL_Pos)

/*=========================================================
 * INT_ENABLE / INT_STATUS Register Bits
 *========================================================*/

#define MPU6050_DATA_RDY_INT_Pos         0U
#define MPU6050_DATA_RDY_INT_Msk         (1U << MPU6050_DATA_RDY_INT_Pos)

#endif /* MPU6050_REG_H */
