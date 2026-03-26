//*****************************************************************************
//  Copyright (c) 2026 Trenser
//  All Rights Reserved
//*****************************************************************************
//
// File    : uart_transmitter.c
// Summary : Implementation of data formatting and UART transmission.
// Note    : Adheres to Trenser Embedded Coding Standard V1.0.
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "uart_transmitter.h"
#include <stdio.h>
#include <string.h>

//******************************* Global Types ********************************

//***************************** Global Constants ******************************

//***************************** Local Constants *******************************
#define DEFAULT_UART_TIMEOUT_MS    10U
#define EMPTY_BUFFER_SIZE          0U
#define PACKET_BUF_SIZE            128U

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
//Purpose : Transmits a raw character buffer over the configured UART interface.
//Inputs  : pstConfig - Pointer to the logger configuration structure.
//          pcBuffer  - Pointer to the data buffer to be transmitted.
//          unLength  - Number of bytes to transmit.
//Outputs : None      - Data is shifted out via UART hardware pins.
//Return  : bool      - true if HAL_UART_Transmit returns HAL_OK; else false.
//*****************************************************************************
bool LoggerData(Logger_Config_t* const pstConfig, const char* pcBuffer, uint16 unLength)
{
    bool bStatus = false;
    HAL_StatusTypeDef enHalStatus;

    if ((NULL != pstConfig) && (NULL != pstConfig->phUart) &&
        (NULL != pcBuffer)  && (unLength > EMPTY_BUFFER_SIZE))
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

//******************************.FUNCTION_HEADER.******************************
//Purpose : Step-level wrapper that formats processed sensor data into a
//          log string and initiates UART transmission.
//Inputs  : pstConfig    - Pointer to the logger configuration structure.
//          pstMpuDevice - Pointer to the device structure containing
//                         calculated Pitch, Roll, and Accel values.
//Outputs : None         - Formatted string is sent to the LoggerData function.
//Return  : bool         - true if string was formatted and sent successfully;
//                         else false.
//*****************************************************************************
bool UartTransmitter(Logger_Config_t* const pstConfig, MPU6050_DEVICE* const pstMpuDevice)
{
    char acTlvPacket[PACKET_BUF_SIZE];
    int  nLen;
    bool bStatus = false;

    if ((NULL != pstConfig) && (NULL != pstMpuDevice))
    {
        nLen = snprintf(acTlvPacket, PACKET_BUF_SIZE,
        		        "[LOG] AX:%d, AY:%d, AZ:%d, P:%.2f, R:%.2f\r\n",
                        pstMpuDevice->nAx,
                        pstMpuDevice->nAy,
                        pstMpuDevice->nAz,
                        pstMpuDevice->fPitch,
                        pstMpuDevice->fRoll);

        if (nLen > 0)
        {
            bStatus = LoggerData(pstConfig, acTlvPacket, (uint16)nLen);
        }
    }

    return bStatus;
}

// EOF
