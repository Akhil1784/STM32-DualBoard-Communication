//*****************************************************************************
// Copyright (c) 2026 Trenser
// All Rights Reserved
//*****************************************************************************
//
// File    : os_layer.h
// Summary : Prototypes and type definitions for the OS Abstraction Layer.
//
//*****************************************************************************

#ifndef OS_LAYER_H
#define OS_LAYER_H

//******************************* Include Files *******************************
#include "main.h"
#include "cmsis_os2.h"
#include "platform_types.h"

//***************************** Global Constants ******************************
#define OS_WAIT_FOREVER    osWaitForever
#define OS_NO_WAIT         0U

//******************************* Global Types ********************************
typedef struct _OS_TASK_CONFIG_
{
    const char* pcName;
    osThreadFunc_t pFunc;
    osPriority_t enPriority;
    uint32 ulStackSize;
} OS_TASK_CONFIG;

//***************************** Local Constants *******************************

//***************************** Global Variables ******************************

//****************************** Local Variables ******************************

//***************************** Type Definitions ******************************

//*************************** Forward Declarations ****************************
void OS_Initialize(void);
void OS_StartScheduler(void);
osThreadId_t OS_TaskCreate(const OS_TASK_CONFIG* const pstConfig);
osMutexId_t OS_MutexCreate(const char* pcName);
osStatus_t OS_MutexAcquire(osMutexId_t id, uint32 ulTimeout);
osStatus_t OS_MutexRelease(osMutexId_t id);

#endif // OS_LAYER_H

//******************************** End of File ********************************

