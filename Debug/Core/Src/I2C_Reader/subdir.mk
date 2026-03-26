################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/I2C_Reader/mpu6050_sensor.c 

OBJS += \
./Core/Src/I2C_Reader/mpu6050_sensor.o 

C_DEPS += \
./Core/Src/I2C_Reader/mpu6050_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/I2C_Reader/%.o Core/Src/I2C_Reader/%.su Core/Src/I2C_Reader/%.cyclo: ../Core/Src/I2C_Reader/%.c Core/Src/I2C_Reader/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32U5xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Core/Src/I2C_Reader -I../Core/Src/UART_Tx -I../Core/Src/OS_Execution -I../Core/Src/Data_Processor -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-I2C_Reader

clean-Core-2f-Src-2f-I2C_Reader:
	-$(RM) ./Core/Src/I2C_Reader/mpu6050_sensor.cyclo ./Core/Src/I2C_Reader/mpu6050_sensor.d ./Core/Src/I2C_Reader/mpu6050_sensor.o ./Core/Src/I2C_Reader/mpu6050_sensor.su

.PHONY: clean-Core-2f-Src-2f-I2C_Reader

