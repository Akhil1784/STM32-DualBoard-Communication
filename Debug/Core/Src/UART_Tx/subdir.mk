################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/UART_Tx/uart_transmitter.c 

OBJS += \
./Core/Src/UART_Tx/uart_transmitter.o 

C_DEPS += \
./Core/Src/UART_Tx/uart_transmitter.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/UART_Tx/%.o Core/Src/UART_Tx/%.su Core/Src/UART_Tx/%.cyclo: ../Core/Src/UART_Tx/%.c Core/Src/UART_Tx/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_NUCLEO_64 -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/BSP/STM32U5xx_Nucleo -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../Core/Src/I2C_Reader -I../Core/Src/UART_Tx -I../Core/Src/OS_Execution -I../Core/Src/Data_Processor -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-UART_Tx

clean-Core-2f-Src-2f-UART_Tx:
	-$(RM) ./Core/Src/UART_Tx/uart_transmitter.cyclo ./Core/Src/UART_Tx/uart_transmitter.d ./Core/Src/UART_Tx/uart_transmitter.o ./Core/Src/UART_Tx/uart_transmitter.su

.PHONY: clean-Core-2f-Src-2f-UART_Tx

