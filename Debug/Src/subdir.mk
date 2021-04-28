################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/SPI_driver.c \
../Src/gpio_driver.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/SPI_driver.o \
./Src/gpio_driver.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/SPI_driver.d \
./Src/gpio_driver.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/SPI_driver.o: ../Src/SPI_driver.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F207IGHx -DSTM32F2 -c -I../Inc -I"C:/cubeIDEwork/My_HAL/Drivers/CMSIS/Include" -I"C:/cubeIDEwork/My_HAL/Drivers/CMSIS/Device/ST/STM32F2xx/Include" -I"C:/cubeIDEwork/My_HAL/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/SPI_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/gpio_driver.o: ../Src/gpio_driver.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F207IGHx -DSTM32F2 -c -I../Inc -I"C:/cubeIDEwork/My_HAL/Drivers/CMSIS/Include" -I"C:/cubeIDEwork/My_HAL/Drivers/CMSIS/Device/ST/STM32F2xx/Include" -I"C:/cubeIDEwork/My_HAL/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/gpio_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/main.o: ../Src/main.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F207IGHx -DSTM32F2 -c -I../Inc -I"C:/cubeIDEwork/My_HAL/Drivers/CMSIS/Include" -I"C:/cubeIDEwork/My_HAL/Drivers/CMSIS/Device/ST/STM32F2xx/Include" -I"C:/cubeIDEwork/My_HAL/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F207IGHx -DSTM32F2 -c -I../Inc -I"C:/cubeIDEwork/My_HAL/Drivers/CMSIS/Include" -I"C:/cubeIDEwork/My_HAL/Drivers/CMSIS/Device/ST/STM32F2xx/Include" -I"C:/cubeIDEwork/My_HAL/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F207IGHx -DSTM32F2 -c -I../Inc -I"C:/cubeIDEwork/My_HAL/Drivers/CMSIS/Include" -I"C:/cubeIDEwork/My_HAL/Drivers/CMSIS/Device/ST/STM32F2xx/Include" -I"C:/cubeIDEwork/My_HAL/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

