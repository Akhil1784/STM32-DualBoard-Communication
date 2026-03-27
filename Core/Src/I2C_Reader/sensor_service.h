//*****************************************************************************
// Copyright (c) 2026 Trenser
// All Rights Reserved
//*****************************************************************************
//
// File    : sensor_service.h
// Summary : Prototypes and structures for MPU6050 I2C acquisition.
//
//*****************************************************************************

#ifndef MPU6050_SENSOR_H
#define MPU6050_SENSOR_H

//******************************* Include Files *******************************
#include "main.h"
#include "platform_types.h"
#include <stdint.h>

//***************************** Global Constants ******************************
#define RAW_BUF_SIZE             6U

//******************************* Global Types ********************************
typedef struct _MPU6050_DEVICE_
{
    I2C_HandleTypeDef* phHi2c;
    uint16 unDevAddr;
    uint8 aucRawBuf[RAW_BUF_SIZE];
    int16 nAx;
    int16 nAy;
    int16 nAz;
    float fPitch;
    float fRoll;
} MPU6050_DEVICE;

//***************************** Local Constants *******************************

//***************************** Global Variables ******************************

//****************************** Local Variables ******************************

//***************************** Type Definitions ******************************

//*************************** Forward Declarations *****************************

//******************************.FUNCTION_HEADER.******************************
bool SensorReadInit(I2C_HandleTypeDef* const phI2c, MPU6050_DEVICE* const pstDevice);
bool SensorReadAcquire(MPU6050_DEVICE* const pstDevice);
void SensorReadTask(void* pvArgument);

#endif /* MPU6050_SENSOR_H */

//******************************** End of File ********************************

