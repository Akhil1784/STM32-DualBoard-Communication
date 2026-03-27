//*****************************************************************************
// Copyright (c) 2026 Trenser
// All Rights Reserved
//*****************************************************************************
//
// File    : processor_service.h
// Summary : Prototypes and constants for MPU6050 data processing logic.
//
//*****************************************************************************

#ifndef PROCESSOR_SERVICE_H
#define PROCESSOR_SERVICE_H

//******************************* Include Files *******************************
#include "sensor_service.h"
#include "main.h"
#include "platform_types.h"
#include <stdint.h>

//***************************** Global Constants ******************************

//******************************* Global Types ********************************

//***************************** Local Constants *******************************

//***************************** Global Variables ******************************

//****************************** Local Variables ******************************

//***************************** Type Definitions ******************************

//*************************** Forward Declarations ****************************

//******************************.FUNCTION_HEADER.******************************
bool DataProcessExecute(MPU6050_DEVICE* const pstDevice);
void DataProcessTask(void* pvArgument);

#endif // PROCESSOR_SERVICE_H

//******************************** End of File ********************************
