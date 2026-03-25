//*****************************************************************************
//  Copyright (c) 2026 Trenser
//  All Rights Reserved
//*****************************************************************************
//
// File    : logger_service.c
// Summary : Implementation of UART logging service for data transmission.
// Note    : Adheres to Trenser Embedded Coding Standard V1.0.
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "logger_service.h"
#include <stdio.h>
#include <string.h>

//******************************* Global Types ********************************

//***************************** Global Constants ******************************

//***************************** Local Constants *******************************
#define DEFAULT_UART_TIMEOUT_MS    10U
#define EMPTY_BUFFER_SIZE          0U

//***************************** Global Variables ******************************

//***************************** Type Definitions ******************************

//******************************.FUNCTION_HEADER.******************************
//Purpose : Initializes the logger configuration structure with the UART handle.
//Inputs  : pstConfig - Pointer to the logger configuration structure.
//          phUart    - Pointer to the HAL UART hardware handle.
//Outputs : pstConfig - Updated with UART handle and default timeout.
//Return  : bool      - true if initialization is successful; false if
//                      pointers are NULL.
//*****************************************************************************
bool LoggerInit(Logger_Config_t* const pstConfig, UART_HandleTypeDef* const phUart)
{
    bool bRetVal = false;

    if ((NULL != pstConfig) && (NULL != phUart))
    {
        pstConfig->phUart      = phUart;
        pstConfig->unTimeoutMs = DEFAULT_UART_TIMEOUT_MS;
        bRetVal                = true;
    }

    return bRetVal;
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : Transmits a character buffer over the configured UART interface.
//Inputs  : pstConfig - Pointer to the logger configuration structure.
//          pcBuffer  - Pointer to the string/data buffer to be sent.
//          unLength  - Number of bytes to transmit.
//Outputs : None (Data sent over hardware pins).
//Return  : bool      - true if HAL_UART_Transmit returns HAL_OK; else false.
//*****************************************************************************
bool LoggerData(Logger_Config_t* const pstConfig, const char* pcBuffer, uint16_t unLength)
{
    bool bStatus = false;
    HAL_StatusTypeDef enHalStatus;

    if ((NULL != pstConfig) && (NULL != pstConfig->phUart) &&
        (NULL != pcBuffer)  && (EMPTY_BUFFER_SIZE != unLength))
    {
        enHalStatus = HAL_UART_Transmit(pstConfig->phUart,
                                        (uint8_t*)pcBuffer,
                                        unLength,
                                        pstConfig->unTimeoutMs);

        if (HAL_OK == enHalStatus)
        {
            bStatus = true;
        }
    }

    return bStatus;
}

// EOF
