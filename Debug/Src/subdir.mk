################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/bht1750.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/main.c \
../Src/stm32f0xx_hal_msp.c \
../Src/stm32f0xx_it.c \
../Src/system_stm32f0xx.c \
../Src/usart.c 

OBJS += \
./Src/bht1750.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/main.o \
./Src/stm32f0xx_hal_msp.o \
./Src/stm32f0xx_it.o \
./Src/system_stm32f0xx.o \
./Src/usart.o 

C_DEPS += \
./Src/bht1750.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/main.d \
./Src/stm32f0xx_hal_msp.d \
./Src/stm32f0xx_it.d \
./Src/system_stm32f0xx.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F030x6 -I"/Users/laalex/work/codesilk/microcontrollers/stm32/bht1750_lib/Inc" -I"/Users/laalex/work/codesilk/microcontrollers/stm32/bht1750_lib/Drivers/STM32F0xx_HAL_Driver/Inc" -I"/Users/laalex/work/codesilk/microcontrollers/stm32/bht1750_lib/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"/Users/laalex/work/codesilk/microcontrollers/stm32/bht1750_lib/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"/Users/laalex/work/codesilk/microcontrollers/stm32/bht1750_lib/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


