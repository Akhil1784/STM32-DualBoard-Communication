//*****************************************************************************
//  Copyright (c) 2026 Trenser
//  All Rights Reserved
//*****************************************************************************
//
// File    : os_layer.c
// Summary : OS Task management for sensor acquisition and processing.
// Note    : This file acts ONLY as the workflow orchestrator.
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "main.h"
#include "cmsis_os2.h"
#include "mpu6050_sensor.h"
#include "processor_service.h"
#include "uart_transmitter.h"

//******************************* Global Types *******************************

//***************************** Global Constants ******************************

//***************************** Local Constants *******************************
#define WORKFLOW_STEPS          3U
#define ERR_LED_DELAY_MS        100U
#define TASK_DELAY_MS           20U
#define INIT_STEP_IDX           0U

//***************************** Global Variables ******************************

//***************************** Local Variables *******************************
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;

static MPU6050_DEVICE  g_stAccelNode;
static Logger_Config_t g_stBoardTxLogger;

//***************************** Type Definitions ******************************
typedef bool (*Workflow_Fn)(void);

//******************************.FUNCTION_HEADER.******************************
//Purpose : Wrapper for the I2C acquisition step.
//Inputs  : None (Uses global g_stAccelNode).
//Outputs : g_stAccelNode - Raw buffer updated.
//Return  : bool - true if acquisition successful; else false.
//*****************************************************************************
static bool Step_I2C_Reader(void)
{
    return I2CReader(&g_stAccelNode);
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : Wrapper for the data processing step.
//Inputs  : None (Uses global g_stAccelNode).
//Outputs : g_stAccelNode - Pitch, Roll, and Integers calculated.
//Return  : bool - true if processing successful; else false.
//*****************************************************************************
static bool Step_Data_Processor(void)
{
    return DataProcessor(&g_stAccelNode);
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : Wrapper for the UART transmission step.
//Inputs  : None (Uses global g_stBoardTxLogger and g_stAccelNode).
//Outputs : None - Data sent to UART hardware.
//Return  : bool - true if transmission successful; else false.
//*****************************************************************************
static bool Step_UART_Sender(void)
{
    return UartTransmitter(&g_stBoardTxLogger, &g_stAccelNode);
}

static const Workflow_Fn g_fnBoard1Workflow[WORKFLOW_STEPS] =
{
    Step_I2C_Reader,
    Step_Data_Processor,
    Step_UART_Sender
};

//******************************.FUNCTION_HEADER.******************************
//Purpose : Primary Thread Entry Point. Initialization and Workflow execution.
//Inputs  : argument - Standard FreeRTOS task argument (unused).
//Outputs : GPIO PB14 (Red LED) - Indicates error status.
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
            HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
            osDelay(ERR_LED_DELAY_MS);
        }
    }

    for(;;)
    {
        bStepSuccess = g_fnBoard1Workflow[ucStepIdx]();

        if (true == bStepSuccess)
        {
            ucStepIdx = (uint8_t)((ucStepIdx + 1U) % WORKFLOW_STEPS);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
        }

        osDelay(TASK_DELAY_MS);
    }
}
