//*****************************************************************************
//  Copyright (c) 2026 Trenser
//  All Rights Reserved
//*****************************************************************************
//
// File    : logger_service.h
// Summary : Header file for UART logging service.
// Note    : Adheres to Trenser Embedded Coding Standard V1.0.
//
//*****************************************************************************

#ifndef LOGGER_SERVICE_H
#define LOGGER_SERVICE_H

//******************************* Include Files *******************************
#include "main.h"
#include <stdbool.h>
#include <stdint.h>

//******************************* Global Types ********************************
typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

//***************************** Global Constants ******************************

//***************************** Local Constants *******************************

//***************************** Global Variables ******************************

//***************************** Type Definitions ******************************
typedef struct _LOGGER_CONFIG_
{
    UART_HandleTypeDef* phUart;
    uint32 unTimeoutMs;
} Logger_Config_t;

//***************************** Forward Declarations **************************
bool LoggerInit(Logger_Config_t* const pstConfig,
                                             UART_HandleTypeDef* const phUart);
bool LoggerData(Logger_Config_t* const pstConfig, const char* pcBuffer, 
                                                              uint16 unLength);

#endif // LOGGER_SERVICE_H

// EOF
