//*****************************************************************************
//  Copyright (c) 2026 Trenser
//  All Rights Reserved
//*****************************************************************************
//
// File    : processor_service.c
// Summary : Implementation of MPU6050 data conversion and math logic.
// Note    : Adheres to Trenser Embedded Coding Standard V1.0.
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "processor_service.h"
#include <math.h>

//******************************* Global Types *******************************

//***************************** Global Constants ******************************

//***************************** Local Constants *******************************
#define RAD_TO_DEG              57.2957795f
#define ACCEL_SENSITIVITY       16384.0f
#define BIT_SHIFT_8             8U
#define IDX_ACCEL_X_H           0U
#define IDX_ACCEL_X_L           1U
#define IDX_ACCEL_Y_H           2U
#define IDX_ACCEL_Y_L           3U
#define IDX_ACCEL_Z_H           4U
#define IDX_ACCEL_Z_L           5U

//***************************** Global Variables ******************************

//***************************** Type Definitions ******************************

//******************************.FUNCTION_HEADER.******************************
//Purpose : Converts raw byte pairs into signed 16-bit integers and
//          calculates Pitch and Roll using trigonometry.
//Inputs  : pstMpuDevice - Pointer to the device structure containing raw data.
//Outputs : pstMpuDevice - Updated nAx, nAy, nAz, fPitch, and fRoll.
//Return  : bool         - true if processing is successful; else false.
//*****************************************************************************
bool DataProcessor(MPU6050_DEVICE* const pstMpuDevice)
{
    float fAxG;
    float fAyG;
    float fAzG;
    float fYZSumSq;
    bool  bStatus = false;

    if (NULL != pstMpuDevice)
    {
        pstMpuDevice->nAx = (int16_t)(((uint16_t)pstMpuDevice->aucRawBuf[IDX_ACCEL_X_H] << BIT_SHIFT_8) |
                                                 pstMpuDevice->aucRawBuf[IDX_ACCEL_X_L]);

        pstMpuDevice->nAy = (int16_t)(((uint16_t)pstMpuDevice->aucRawBuf[IDX_ACCEL_Y_H] << BIT_SHIFT_8) |
                                                 pstMpuDevice->aucRawBuf[IDX_ACCEL_Y_L]);

        pstMpuDevice->nAz = (int16_t)(((uint16_t)pstMpuDevice->aucRawBuf[IDX_ACCEL_Z_H] << BIT_SHIFT_8) |
                                                 pstMpuDevice->aucRawBuf[IDX_ACCEL_Z_L]);

        fAxG = (float)pstMpuDevice->nAx / ACCEL_SENSITIVITY;
        fAyG = (float)pstMpuDevice->nAy / ACCEL_SENSITIVITY;
        fAzG = (float)pstMpuDevice->nAz / ACCEL_SENSITIVITY;

        pstMpuDevice->fRoll  = atan2f(fAyG, fAzG) * RAD_TO_DEG;

        fYZSumSq = (fAyG * fAyG) + (fAzG * fAzG);
        pstMpuDevice->fPitch = atan2f(-fAxG, sqrtf(fYZSumSq)) * RAD_TO_DEG;

        bStatus = true;
    }

    return bStatus;
}

// EOF
