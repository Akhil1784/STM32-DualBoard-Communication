//*****************************************************************************
//  Copyright (c) 2026 Trenser
//  All Rights Reserved
//*****************************************************************************
//
// File    : sensor_task.c
// Summary : OS Task management for sensor acquisition and processing.
// Note    : Adheres to Trenser Embedded Coding Standard V1.0 .
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "main.h"
#include "cmsis_os2.h"
#include "mpu6050_sensor.h"
#include "logger_service.h"
#include <math.h>
#include <stdio.h>

//***************************** Local Constants *******************************
#define RAD_TO_DEG              57.2957795f
#define ACCEL_SENSITIVITY       16384.0f
#define PI_VALUE                3.14159265f
#define WORKFLOW_STEPS          3U
#define PACKET_BUF_SIZE         128U
#define IDX_ACCEL_X_H           0U
#define IDX_ACCEL_X_L           1U
#define IDX_ACCEL_Y_H           2U
#define IDX_ACCEL_Y_L           3U
#define IDX_ACCEL_Z_H           4U
#define IDX_ACCEL_Z_L           5U
#define BIT_SHIFT_8             8U
#define ERR_LED_DELAY_MS        100U
#define TASK_DELAY_MS           20U
#define INIT_STEP_IDX           0U

//***************************** Local Variables *******************************
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;

static MPU6050_DEVICE  g_stAccelNode;
static Logger_Config_t g_stBoardTxLogger;

//***************************** Type Definitions ******************************
typedef bool (*Workflow_Fn)(void);

//******************************.FUNCTION_HEADER.******************************
//Purpose : Performs a non-blocking I2C read to  capture 6 bytes of raw
//          accelerometer data from the MPU6050.
//Inputs  : None (Uses global entity g_stAccelNode).
//Outputs : g_stAccelNode.aucRawBuf - Updated with fresh sensor data.
//Return  : bool - true if HAL_I2C_Mem_Read returns HAL_OK; else false.
//*****************************************************************************
static bool Step_I2C_Reader(void)
{
    HAL_StatusTypeDef enStatus;
    enStatus = MpuSensorAcquireRaw(&g_stAccelNode);
    return (HAL_OK == enStatus);
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : Converts raw byte pairs into signed 16-bit   integers and
//          calculates Pitch and Roll using trigonometry.
//Inputs  : g_stAccelNode.aucRawBuf - The raw bytes from Step 1.
//Outputs : g_stAccelNode.nAx, nAy, nAz - Reconstructed integers.
//          g_stAccelNode.fPitch, fRoll - Calculated orientation in degrees.
//Return  : bool - Always returns true as math operations are deterministic.
//*****************************************************************************
static bool Step_Data_Processor(void)
{
    float fAxG;
    float fAyG;
    float fAzG;
    float fYZSumSq;

    /* Combine High and Low Bytes for 16-bit signed integers */
    g_stAccelNode.nAx = (int16_t)(((uint16_t)g_stAccelNode.aucRawBuf[IDX_ACCEL_X_H] << BIT_SHIFT_8) |
                                             g_stAccelNode.aucRawBuf[IDX_ACCEL_X_L]);

    g_stAccelNode.nAy = (int16_t)(((uint16_t)g_stAccelNode.aucRawBuf[IDX_ACCEL_Y_H] << BIT_SHIFT_8) |
                                             g_stAccelNode.aucRawBuf[IDX_ACCEL_Y_L]);

    g_stAccelNode.nAz = (int16_t)(((uint16_t)g_stAccelNode.aucRawBuf[IDX_ACCEL_Z_H] << BIT_SHIFT_8) |
                                             g_stAccelNode.aucRawBuf[IDX_ACCEL_Z_L]);

    fAxG = (float)g_stAccelNode.nAx / ACCEL_SENSITIVITY;
    fAyG = (float)g_stAccelNode.nAy / ACCEL_SENSITIVITY;
    fAzG = (float)g_stAccelNode.nAz / ACCEL_SENSITIVITY;

    g_stAccelNode.fRoll  = atan2f(fAyG, fAzG) * RAD_TO_DEG;

    fYZSumSq = (fAyG * fAyG) + (fAzG * fAzG);
    g_stAccelNode.fPitch = atan2f(-fAxG, sqrtf(fYZSumSq)) * RAD_TO_DEG;

    return true;
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : Formats the processed sensor data into a human-readable string
//          and transmits it via the Logger Service.
//Inputs  : g_stAccelNode - The processed sensor entity.
//Outputs : UART TX Buffer - Serial data transmitted to external listener.
//Return  : bool - true if UART transmission was successful.
//*****************************************************************************
static bool Step_UART_Sender(void)
{
    char acTlvPacket[PACKET_BUF_SIZE];
    int  nLen;
    bool bStatus = false;

    nLen = snprintf(acTlvPacket, PACKET_BUF_SIZE,
                    "[LOG] AX:%d, AY:%d, AZ:%d, P:%.2f, R:%.2f\r\n",
                    g_stAccelNode.nAx, g_stAccelNode.nAy, g_stAccelNode.nAz,
                    g_stAccelNode.fPitch, g_stAccelNode.fRoll);

    if (nLen > 0)
    {
        bStatus = LoggerData(&g_stBoardTxLogger, acTlvPacket, (uint16)nLen);
    }

    return bStatus;
}

static const Workflow_Fn g_fnBoard1Workflow[WORKFLOW_STEPS] =
{
    Step_I2C_Reader,
    Step_Data_Processor,
    Step_UART_Sender
};

//******************************.FUNCTION_HEADER.******************************
//Purpose : Primary Thread Entry Point. Initialization of  peripherals and
//          the execution of the TRENSR Function Table.
//Inputs  : argument - Standard FreeRTOS task argument (unused).
//Outputs : Red LED - Signals hardware/initialization failure.
//Return  : None (Infinite Loop).
//*****************************************************************************
void SensorTask(void *argument)
{
    uint8_t ucStepIdx = INIT_STEP_IDX;
    bool bSensorReady;
    bool bLoggerReady;
    bool bStepSuccess;

    bSensorReady = (HAL_OK == MpuSensorInit(&g_stAccelNode, &hi2c1));
    bLoggerReady = LoggerInit(&g_stBoardTxLogger, &huart1);

    if ((false == bSensorReady) || (false == bLoggerReady))
    {
        for(;;)
        {
            BSP_LED_Toggle(LED_RED);
            osDelay(ERR_LED_DELAY_MS);
        }
    }

    for(;;)
    {
        bStepSuccess = g_fnBoard1Workflow[ucStepIdx]();

        if (true == bStepSuccess)
        {
            ucStepIdx = (uint8_t)((ucStepIdx + 1U) % WORKFLOW_STEPS);
            BSP_LED_Off(LED_RED);
        }
        else
        {
            BSP_LED_On(LED_RED);
        }

        osDelay(TASK_DELAY_MS);
    }
}
