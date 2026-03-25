################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/UART_Logging/logger_service.c 

OBJS += \
./Drivers/UART_Logging/logger_service.o 

C_DEPS += \
./Drivers/UART_Logging/logger_service.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/UART_Logging/%.o Drivers/UART_Logging/%.su Drivers/UART_Logging/%.cyclo: ../Drivers/UART_Logging/%.c Drivers/UART_Logging/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32U5xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Drivers/I2C_Sensor -I../Drivers/UART_Logging -I../Drivers/OS_Execution -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-UART_Logging

clean-Drivers-2f-UART_Logging:
	-$(RM) ./Drivers/UART_Logging/logger_service.cyclo ./Drivers/UART_Logging/logger_service.d ./Drivers/UART_Logging/logger_service.o ./Drivers/UART_Logging/logger_service.su

.PHONY: clean-Drivers-2f-UART_Logging

