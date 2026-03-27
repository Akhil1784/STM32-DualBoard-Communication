//*****************************************************************************
// Copyright (c) 2026 Trenser
// All Rights Reserved
//*****************************************************************************
//
// File    : uart_transmitter.h
// Summary : Prototypes and constants for UART transmission and logging.
//
//*****************************************************************************

#ifndef UART_TRANSMITTER_H
#define UART_TRANSMITTER_H

//******************************* Include Files *******************************
#include "sensor_service.h"
#include "main.h"
#include <stdbool.h>
#include <stdint.h>

//******************************** Global Types *******************************

//***************************** Global Constants ******************************
#define TX_PACKET_BUF_SIZE    128U
#define UART_TX_TIMEOUT_MS    100U
#define TX_TASK_DELAY_MS      100U

//***************************** Local Constants *******************************

//***************************** Global Variables ******************************

//****************************** Local Variables ******************************

//***************************** Type Definitions ******************************

//*************************** Forward Declarations *****************************

//******************************.FUNCTION_HEADER.******************************
bool UartTxSendLog(UART_HandleTypeDef* const phUart, MPU6050_DEVICE* const pstDevice);
void UartTxTask(void* pvArgument);

#endif // UART_TRANSMITTER_H

//******************************** End of File ********************************
