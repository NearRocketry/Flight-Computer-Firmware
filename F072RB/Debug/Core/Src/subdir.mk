################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/InertialMeasurementSystem.c \
../Core/Src/LinearAlgebra.c \
../Core/Src/LocalSaveSystem.c \
../Core/Src/SimulatedSensorManager.c \
../Core/Src/TrajectorySimulator.c \
../Core/Src/main.c \
../Core/Src/stm32f0xx_hal_msp.c \
../Core/Src/stm32f0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f0xx.c 

C_DEPS += \
./Core/Src/InertialMeasurementSystem.d \
./Core/Src/LinearAlgebra.d \
./Core/Src/LocalSaveSystem.d \
./Core/Src/SimulatedSensorManager.d \
./Core/Src/TrajectorySimulator.d \
./Core/Src/main.d \
./Core/Src/stm32f0xx_hal_msp.d \
./Core/Src/stm32f0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f0xx.d 

OBJS += \
./Core/Src/InertialMeasurementSystem.o \
./Core/Src/LinearAlgebra.o \
./Core/Src/LocalSaveSystem.o \
./Core/Src/SimulatedSensorManager.o \
./Core/Src/TrajectorySimulator.o \
./Core/Src/main.o \
./Core/Src/stm32f0xx_hal_msp.o \
./Core/Src/stm32f0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f0xx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F072xB -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/InertialMeasurementSystem.cyclo ./Core/Src/InertialMeasurementSystem.d ./Core/Src/InertialMeasurementSystem.o ./Core/Src/InertialMeasurementSystem.su ./Core/Src/LinearAlgebra.cyclo ./Core/Src/LinearAlgebra.d ./Core/Src/LinearAlgebra.o ./Core/Src/LinearAlgebra.su ./Core/Src/LocalSaveSystem.cyclo ./Core/Src/LocalSaveSystem.d ./Core/Src/LocalSaveSystem.o ./Core/Src/LocalSaveSystem.su ./Core/Src/SimulatedSensorManager.cyclo ./Core/Src/SimulatedSensorManager.d ./Core/Src/SimulatedSensorManager.o ./Core/Src/SimulatedSensorManager.su ./Core/Src/TrajectorySimulator.cyclo ./Core/Src/TrajectorySimulator.d ./Core/Src/TrajectorySimulator.o ./Core/Src/TrajectorySimulator.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f0xx_hal_msp.cyclo ./Core/Src/stm32f0xx_hal_msp.d ./Core/Src/stm32f0xx_hal_msp.o ./Core/Src/stm32f0xx_hal_msp.su ./Core/Src/stm32f0xx_it.cyclo ./Core/Src/stm32f0xx_it.d ./Core/Src/stm32f0xx_it.o ./Core/Src/stm32f0xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f0xx.cyclo ./Core/Src/system_stm32f0xx.d ./Core/Src/system_stm32f0xx.o ./Core/Src/system_stm32f0xx.su

.PHONY: clean-Core-2f-Src

