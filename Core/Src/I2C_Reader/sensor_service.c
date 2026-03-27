//*****************************************************************************
// Copyright (c) 2026 Trenser
// All Rights Reserved
//*****************************************************************************
//
// File    : sensor_service.c
// Summary : Implementation of sensor initialization and acquisition tasks.
//
//*****************************************************************************

//******************************* Include Files *******************************
#include "sensor_service.h"
#include "os_layer.h"

//***************************** Local Constants *******************************
#define MPU6050_I2C_ADDR         (0x68U << 1U)
#define REG_PWR_MGMT_1           0x6BU
#define REG_ACCEL_X_HIGH         0x3BU
#define MEM_ADDR_SIZE            1U
#define WRITE_DATA_SIZE          1U
#define I2C_COMM_TIMEOUT         100U
#define SENSOR_TASK_DELAY        20U

//***************************** Global Variables ******************************
extern I2C_HandleTypeDef hi2c1;
extern osMutexId_t       gpMtxDataProtect;
extern MPU6050_DEVICE    gstMpuNode;

//******************************.FUNCTION_HEADER.******************************
//Purpose : Initializes the sensor hardware and device structure.
//Inputs  : phI2c - Pointer to I2C handle.
//          pstDevice - Pointer to MPU device structure.
//Outputs : Device structure and sensor power registers updated.
//Return  : bool - true if initialization successful.
//*****************************************************************************
bool SensorReadInit(I2C_HandleTypeDef* const phI2c, MPU6050_DEVICE* const pstDevice)
{
    uint8 ucWakeupData = 0;
    bool  blStatus     = false;

    if ((NULL != phI2c) && (NULL != pstDevice))
    {
        pstDevice->phHi2c    = phI2c;
        pstDevice->unDevAddr = MPU6050_I2C_ADDR;

        if (HAL_OK == HAL_I2C_Mem_Write(pstDevice->phHi2c,
                                        pstDevice->unDevAddr,
                                        REG_PWR_MGMT_1,
                                        MEM_ADDR_SIZE,
                                        &ucWakeupData,
                                        WRITE_DATA_SIZE,
                                        I2C_COMM_TIMEOUT))
        {
            blStatus = true;
        }
    }

    return blStatus;
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : Logic function to acquire raw data from sensor.
//Inputs  : pstDevice - Pointer to MPU device structure.
//Outputs : pstDevice->aucRawBuf updated with 6 bytes of raw data.
//Return  : bool - true if acquisition successful.
//*****************************************************************************
bool SensorReadAcquire(MPU6050_DEVICE* const pstDevice)
{
    bool blStatus = false;

    if (NULL != pstDevice)
    {

        if (HAL_OK == HAL_I2C_Mem_Read(pstDevice->phHi2c,
                                       pstDevice->unDevAddr,
                                       REG_ACCEL_X_HIGH,
                                       MEM_ADDR_SIZE,
                                       pstDevice->aucRawBuf,
                                       RAW_BUF_SIZE,
                                       I2C_COMM_TIMEOUT))
        {
            blStatus = true;
        }
    }

    return blStatus;
}

//******************************.FUNCTION_HEADER.******************************
//Purpose : RTOS Task entry for periodic sensor data acquisition.
//Inputs  : pvArgument - Task input parameter.
//Outputs : gstMpuNode structure updated globally with raw data.
//Return  : None.
//*****************************************************************************
void SensorReadTask(void* pvArgument)
{
    (void) pvArgument;

    (void) SensorReadInit(&hi2c1, &gstMpuNode);

    for (;;)
    {

        if (osOK == OS_MutexAcquire(gpMtxDataProtect, OS_WAIT_FOREVER))
        {
            (void) SensorReadAcquire(&gstMpuNode);
            (void) OS_MutexRelease(gpMtxDataProtect);
        }

        osDelay(SENSOR_TASK_DELAY);
    }
}

//******************************** End of File ********************************
