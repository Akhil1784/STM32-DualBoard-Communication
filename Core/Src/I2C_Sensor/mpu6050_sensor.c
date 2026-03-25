//*****************************************************************************
//  Copyright (c) 2026 Trenser
//  All Rights Reserved
//*****************************************************************************
//
// File    : mpu6050_sensor.c
// Summary : Implementation of MPU6050 sensor initialization and acquisition.
// Note    : Adheres to Trenser Embedded Coding Standard V1.0.
//
//*****************************************************************************
//******************************* Include Files *******************************
#include "mpu6050_sensor.h"

//******************************* Global Types ********************************

//***************************** Global Constants ******************************

//***************************** Local Constants *******************************
#define MPU6050_ADDR            (0x68U << 1U)
#define REG_PWR_MGMT_1          0x6BU
#define REG_ACCEL_XOUT_H        0x3BU
#define WAKEUP_VALUE            0x00U
#define MEM_ADDR_SIZE           1U
#define DATA_WRITE_SIZE         1U
#define I2C_TIMEOUT             100U

//***************************** Global Variables ******************************

//***************************** Type Definitions ******************************
typedef uint8_t uint8;

//******************************.FUNCTION_HEADER.******************************
//Purpose : Initializes the MPU6050 sensor by setting the power management.
//Inputs  : pstMpuDevice - Pointer to the device structure.
//          phHi2c       - Pointer to the I2C hardware handle.
//Outputs : pstMpuDevice - Updated with I2C handle and address.
//Return  : HAL_StatusTypeDef - Result of the I2C write operation.
//*****************************************************************************
HAL_StatusTypeDef MpuSensorInit(MPU6050_DEVICE* const pstMpuDevice, 
                                               I2C_HandleTypeDef* const phHi2c)
{
    uint8 ucWakeupData = WAKEUP_VALUE;
    HAL_StatusTypeDef enStatus = HAL_ERROR;

    if ((NULL != pstMpuDevice) && (NULL != phHi2c))
    {
        pstMpuDevice->phHi2c    = phHi2c;
        pstMpuDevice->unDevAddr = MPU6050_ADDR;

        enStatus = HAL_I2C_Mem_Write(pstMpuDevice->phHi2c,
                                     pstMpuDevice->unDevAddr,
                                     REG_PWR_MGMT_1,
                                     MEM_ADDR_SIZE,
                                     &ucWakeupData,
                                     DATA_WRITE_SIZE,
                                     I2C_TIMEOUT);
    }

    return enStatus;
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : Acquires raw accelerometer data from the sensor.
//Inputs  : pstMpuDevice - Pointer to the device structure.
//Outputs : pstMpuDevice - aucRawBuf updated with 6 bytes of data.
//Return  : HAL_StatusTypeDef - Result of the I2C read operation.
//*****************************************************************************
HAL_StatusTypeDef MpuSensorAcquireRaw(MPU6050_DEVICE* const pstMpuDevice)
{
    HAL_StatusTypeDef enStatus = HAL_ERROR;

    if (NULL != pstMpuDevice)
    {
        enStatus = HAL_I2C_Mem_Read(pstMpuDevice->phHi2c,
                                    pstMpuDevice->unDevAddr,
                                    REG_ACCEL_XOUT_H,
                                    MEM_ADDR_SIZE,
                                    pstMpuDevice->aucRawBuf,
                                    RAW_BUFFER_SIZE,
                                    I2C_TIMEOUT);
    }

    return enStatus;
}

// EOF
