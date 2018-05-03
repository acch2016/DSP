################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ADC.c \
../source/DAC.c \
../source/GPIO.c \
../source/NVIC.c \
../source/PIT.c \
../source/main.c 

OBJS += \
./source/ADC.o \
./source/DAC.o \
./source/GPIO.o \
./source/NVIC.o \
./source/PIT.o \
./source/main.o 

C_DEPS += \
./source/ADC.d \
./source/DAC.d \
./source/GPIO.d \
./source/NVIC.d \
./source/PIT.d \
./source/main.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -flto  -g3 -D"CPU_MK64FN1M0VDC12" -I../freertos/Source/include -I../startup -I../board -I../utilities -I../freertos/Source/portable/GCC/ARM_CM4F -I../CMSIS -I../source -I../drivers -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


