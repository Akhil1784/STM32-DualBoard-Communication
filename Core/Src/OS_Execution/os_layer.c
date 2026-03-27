//*****************************************************************************
// Copyright (c) 2026 Trenser
// All Rights Reserved
//*****************************************************************************
//
// File    : os_layer.c
// Summary : Implementation of OS initialization and Task Table .
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "sensor_service.h"
#include "os_layer.h"
#include "processor_service.h"
#include "uart_transmitter.h"

//***************************** Local Constants *******************************
#define SENSOR_STACK_SIZE     1024U
#define PROCESS_STACK_SIZE    1024U
#define UART_TX_STACK_SIZE    1024U

//***************************** Global Constants ******************************
#define NUM_TASKS (sizeof(gstTaskTable) / sizeof(OS_TASK_CONFIG))

//***************************** Global Variables ******************************
MPU6050_DEVICE gstMpuNode;
osMutexId_t    gpMtxDataProtect;

//****************************** Local Variables ******************************

//***************************** Type Definitions ******************************

//***************************** Task Table ************************************
static const OS_TASK_CONFIG gstTaskTable[] =
{
    {
        "SensorRead",  SensorReadTask,  osPriorityHigh,   SENSOR_STACK_SIZE
    },
    {
        "DataProcess", DataProcessTask, osPriorityNormal, PROCESS_STACK_SIZE
    },
    {
        "UartTx",      UartTxTask,      osPriorityLow,    UART_TX_STACK_SIZE
    }
};

//******************************.FUNCTION_HEADER.******************************
//Purpose : Initializes the OS kernel and creates internal OS objects.
//Inputs  : None.
//Outputs : Mutex created, Tasks initialized in Kernel.
//Return  : None.
//*****************************************************************************
void OS_Initialize(void)
{
    uint32 ulIndex = 0U;

    osKernelInitialize();
    gpMtxDataProtect = OS_MutexCreate("DataMtx");

    for (ulIndex = 0; ulIndex < NUM_TASKS; ulIndex++)
    {
        (void) OS_TaskCreate(&gstTaskTable[ulIndex]);
    }
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : Starts the RTOS scheduler.
//Inputs  : None.
//Outputs : Control handed to RTOS.
//Return  : None.
//*****************************************************************************
void OS_StartScheduler(void)
{
    osKernelStart();
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : Wrapper to create a CMSIS-RTOS2 thread.
//Inputs  : pstConfig - Pointer to the task configuration structure.
//Outputs : Thread created in OS.
//Return  : osThreadId_t - The ID of the created thread.
//*****************************************************************************
osThreadId_t OS_TaskCreate(const OS_TASK_CONFIG* const pstConfig)
{
    osThreadAttr_t stAttr =
    {
        0U
    };

    stAttr.name       = pstConfig->pcName;
    stAttr.stack_size = pstConfig->ulStackSize;
    stAttr.priority   = pstConfig->enPriority;

    return osThreadNew(pstConfig->pFunc, NULL, &stAttr);
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : Wrapper to create a recursive mutex.
//Inputs  : pcName - Pointer to the mutex name string.
//Outputs : Mutex object created.
//Return  : osMutexId_t - ID of the created mutex.
//*****************************************************************************
osMutexId_t OS_MutexCreate(const char* pcName)
{
    const osMutexAttr_t stMtxAttr =
    {
        .name = pcName,
        .attr_bits = osMutexRecursive
    };

    return osMutexNew(&stMtxAttr);
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : Wrapper to acquire a mutex.
//Inputs  : id - Mutex ID, ulTimeout - Time to wait.
//Outputs : Mutex ownership updated.
//Return  : osStatus_t - Operation status.
//*****************************************************************************
osStatus_t OS_MutexAcquire(osMutexId_t id, uint32 ulTimeout)
{
    return osMutexAcquire(id, ulTimeout);
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : Wrapper to release a mutex.
//Inputs  : id - Mutex ID.
//Outputs : Mutex ownership released.
//Return  : osStatus_t - Operation status.
//*****************************************************************************
osStatus_t OS_MutexRelease(osMutexId_t id)
{
    return osMutexRelease(id);
}

//******************************** End of File ********************************
