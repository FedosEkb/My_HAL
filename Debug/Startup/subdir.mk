################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f207ighx.s 

OBJS += \
./Startup/startup_stm32f207ighx.o 

S_DEPS += \
./Startup/startup_stm32f207ighx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/startup_stm32f207ighx.o: ../Startup/startup_stm32f207ighx.s Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -c -x assembler-with-cpp -MMD -MP -MF"Startup/startup_stm32f207ighx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

