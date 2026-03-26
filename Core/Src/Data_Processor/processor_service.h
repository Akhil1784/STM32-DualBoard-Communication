//*****************************************************************************
//  Copyright (c) 2026 Trenser
//  All Rights Reserved
//*****************************************************************************
//
// File    : processor_service.h
// Summary : Header file for Data Processor.
// Note    : Adheres to Trenser Embedded Coding Standard V1.0.
//
//*****************************************************************************

#ifndef PROCESSOR_SERVICE_H
#define PROCESSOR_SERVICE_H

//******************************* Include Files *******************************
#include "mpu6050_sensor.h"
#include <stdbool.h>

//******************************* Global Types *******************************

//***************************** Global Constants ******************************

//***************************** Local Constants *******************************


//***************************** Global Variables ******************************

//***************************** Type Definitions ******************************

//***************************** Forward Declarations **************************
bool DataProcessor(MPU6050_DEVICE* const pstMpuDevice);

#endif // PROCESSOR_SERVICE_H

// EOF
