//*****************************************************************************
// Copyright (c) 2026 Trenser
// All Rights Reserved
//*****************************************************************************
//
// File    : uart_transmitter.c
// Summary : Implementation of UART logging task and transmission logic.
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "uart_transmitter.h"
#include "os_layer.h"
#include <stdio.h>

//******************************** Global Types *******************************

//***************************** Global Constants ******************************

//***************************** Local Constants *******************************

//***************************** Global Variables ******************************
extern UART_HandleTypeDef huart1;
extern osMutexId_t gpMtxDataProtect;
extern MPU6050_DEVICE gstMpuNode;

//****************************** Local Variables ******************************

//***************************** Type Definitions ******************************

//*************************** Forward Declarations ****************************

//******************************.FUNCTION_HEADER.******************************
//Purpose : Formats and transmits sensor data via UART.
//Inputs  : phUart - Pointer to UART handle.
//          pstDevice - Pointer to MPU device structure.
//Outputs : Data shifted out via UART hardware pins.
//Return  : bool - true if transmission successful.
//*****************************************************************************
bool UartTxSendLog(UART_HandleTypeDef* const phUart, MPU6050_DEVICE* const pstDevice)
{
    char aucMessageBuffer[TX_PACKET_BUF_SIZE];
    int  nLength = 0;
    bool blStatus = false;

    if ((NULL != phUart) && (NULL != pstDevice))
    {
        nLength = snprintf(aucMessageBuffer, sizeof(aucMessageBuffer),
                           "[LOG] AX:%d, AY:%d, AZ:%d, P:%.2f, R:%.2f\r\n",
                           pstDevice->nAx, pstDevice->nAy, pstDevice->nAz,
                           pstDevice->fPitch, pstDevice->fRoll);

        if (nLength > 0)
        {
            if (HAL_OK == HAL_UART_Transmit(phUart, (uint8_t*)aucMessageBuffer,
                                         (uint16_t)nLength, UART_TX_TIMEOUT_MS))
            {
                blStatus = true;
            }
        }
    }

    return blStatus;
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : RTOS Task entry for periodic UART transmission.
//Inputs  : pvArgument - Task input parameter.
//Outputs : Data transmitted via UART1 TX hardware.
//Return  : None.
//*****************************************************************************
void UartTxTask(void* pvArgument)
{
    (void) pvArgument;

    for (;;)
    {
        if (osOK == OS_MutexAcquire(gpMtxDataProtect, OS_WAIT_FOREVER))
        {
            (void) UartTxSendLog(&huart1, &gstMpuNode);
            (void) OS_MutexRelease(gpMtxDataProtect);
        }

        osDelay(TX_TASK_DELAY_MS);
    }
}

//******************************** End of File ********************************
