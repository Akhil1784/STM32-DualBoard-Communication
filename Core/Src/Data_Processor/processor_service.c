//*****************************************************************************
// Copyright (c) 2026 Trenser
// All Rights Reserved
//*****************************************************************************
//
// File    : processor_service.c
// Summary : Implementation of math logic and RTOS task for data processing.
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "processor_service.h"
#include "os_layer.h"
#include <math.h>

//***************************** Global Constants ******************************

//******************************* Global Types ********************************

//***************************** Local Constants *******************************
#define RAD_TO_DEG_CONST      57.2957f
#define BIT_SHIFT_EIGHT       8U
#define DATA_INDEX_ZERO       0U
#define DATA_INDEX_ONE        1U
#define DATA_INDEX_TWO        2U
#define DATA_INDEX_THREE      3U
#define DATA_INDEX_FOUR       4U
#define DATA_INDEX_FIVE       5U
#define PROCESS_TASK_DELAY    20U

//***************************** Global Variables ******************************
extern osMutexId_t     gpMtxDataProtect;
extern MPU6050_DEVICE  gstMpuNode;

//****************************** Local Variables ******************************

//***************************** Type Definitions ******************************

//*************************** Forward Declarations ****************************

//******************************.FUNCTION_HEADER.******************************
//Purpose : Performs math calculations to convert raw bytes to Pitch and Roll.
//Inputs  : pstDevice - Pointer to MPU device structure containing raw data.
//Outputs : Members nAx, nAy, nAz, fPitch, and fRoll of pstDevice are updated.
//Return  : bool - true if processing is successful, false otherwise.
//*****************************************************************************
bool DataProcessExecute(MPU6050_DEVICE* const pstDevice)
{
    bool  blStatus = false;
    float fYZSumSq = 0.0f;

    if (NULL != pstDevice)
    {
        pstDevice->nAx = (int16)((pstDevice->aucRawBuf[DATA_INDEX_ZERO] <<
                                  BIT_SHIFT_EIGHT) |
                                  pstDevice->aucRawBuf[DATA_INDEX_ONE]);

        pstDevice->nAy = (int16)((pstDevice->aucRawBuf[DATA_INDEX_TWO] <<
                                  BIT_SHIFT_EIGHT) |
                                  pstDevice->aucRawBuf[DATA_INDEX_THREE]);

        pstDevice->nAz = (int16)((pstDevice->aucRawBuf[DATA_INDEX_FOUR] <<
                                  BIT_SHIFT_EIGHT) |
                                  pstDevice->aucRawBuf[DATA_INDEX_FIVE]);

        pstDevice->fRoll = atan2f((float)pstDevice->nAy,
                                  (float)pstDevice->nAz) * RAD_TO_DEG_CONST;

        fYZSumSq = ((float)pstDevice->nAy * (float)pstDevice->nAy) +
                   ((float)pstDevice->nAz * (float)pstDevice->nAz);

        pstDevice->fPitch = atan2f(-(float)pstDevice->nAx,
                                    sqrtf(fYZSumSq)) * RAD_TO_DEG_CONST;

        blStatus = true;
    }

    return blStatus;
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : RTOS Task entry for periodic data processing.
//Inputs  : pvArgument - Task input parameter.
//Outputs : The global MPU structure is updated with processed data.
//Return  : None.
//*****************************************************************************
void DataProcessTask(void* pvArgument)
{
    (void) pvArgument;

    for (;;)
    {
        if (osOK == OS_MutexAcquire(gpMtxDataProtect, OS_WAIT_FOREVER))
        {
            (void) DataProcessExecute(&gstMpuNode);
            (void) OS_MutexRelease(gpMtxDataProtect);
        }

        osDelay(PROCESS_TASK_DELAY);
    }
}

//******************************** End of File ********************************
