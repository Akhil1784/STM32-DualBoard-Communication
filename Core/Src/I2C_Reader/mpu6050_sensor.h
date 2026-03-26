//*****************************************************************************
//  Copyright (c) 2026 Trenser
//  All Rights Reserved
//*****************************************************************************
//
// File    : mpu6050_sensor.h
// Summary : Header file for MPU6050 sensor driver.
// Note    : Adheres to Trenser Embedded Coding Standard V1.0.
//
//*****************************************************************************

#ifndef MPU6050_SENSOR_H
#define MPU6050_SENSOR_H

//******************************* Include Files *******************************
#include "main.h"
#include <stdint.h>
#include <stdbool.h>

//******************************* Global Types *******************************
typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef int16_t  int16;

//***************************** Global Constants ******************************
#define RAW_BUFFER_SIZE    6U

//***************************** Local Constants *******************************


//***************************** Global Variables ******************************

//***************************** Type Definitions ******************************
typedef struct _MPU6050_DEVICE_
{
    I2C_HandleTypeDef* phHi2c;
    uint16 unDevAddr;
    uint8 aucRawBuf[RAW_BUFFER_SIZE];
    int16 nAx;
    int16 nAy;
    int16 nAz;
    float fPitch;
    float fRoll;
} MPU6050_DEVICE;

//***************************** Forward Declarations **************************
HAL_StatusTypeDef MpuSensorInit(MPU6050_DEVICE* const pstMpuDevice, I2C_HandleTypeDef* const phHi2c);
HAL_StatusTypeDef MpuSensorAcquireRaw(MPU6050_DEVICE* const pstMpuDevice);
bool I2CReader(MPU6050_DEVICE* const pstMpuDevice);

#endif // MPU6050_SENSOR_H

// EOF
