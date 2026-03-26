//*****************************************************************************
//  Copyright (c) 2026 Trenser
//  All Rights Reserved
//*****************************************************************************
//
// File    : uart_transmitter.h
// Summary : Header for UART transmission and data formatting service.
// Note    : Adheres to Trenser Embedded Coding Standard V1.0.
//
//*****************************************************************************

#ifndef UART_TRANSMITTER_H
#define UART_TRANSMITTER_H

//******************************* Include Files *******************************
#include "main.h"
#include "mpu6050_sensor.h"
#include <stdbool.h>

//******************************* Global Types ********************************
typedef uint16_t uint16;
typedef uint32_t uint32;

//***************************** Global Constants ******************************

//***************************** Local Constants *******************************


//***************************** Global Variables ******************************

//***************************** Type Definitions ******************************
typedef struct _LOGGER_CONFIG_
{
    UART_HandleTypeDef* phUart;
    uint32  unTimeoutMs;
} Logger_Config_t;

//*************************** Function Prototypes *****************************
bool LoggerInit(Logger_Config_t* const pstConfig, UART_HandleTypeDef* const phUart);
bool LoggerData(Logger_Config_t* const pstConfig, const char* pcBuffer, uint16 unLength);
bool UartTransmitter(Logger_Config_t* const pstConfig, MPU6050_DEVICE* const pstMpuDevice);

#endif // UART_TRANSMITTER_H
