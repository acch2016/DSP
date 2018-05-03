################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/DAC.c \
../Sources/FUNC.c \
../Sources/GPIO.c \
../Sources/MOTOR.c \
../Sources/Matrix.c \
../Sources/NVIC.c \
../Sources/PIT.c \
../Sources/main.c 

OBJS += \
./Sources/DAC.o \
./Sources/FUNC.o \
./Sources/GPIO.o \
./Sources/MOTOR.o \
./Sources/Matrix.o \
./Sources/NVIC.o \
./Sources/PIT.o \
./Sources/main.o 

C_DEPS += \
./Sources/DAC.d \
./Sources/FUNC.d \
./Sources/GPIO.d \
./Sources/MOTOR.d \
./Sources/Matrix.d \
./Sources/NVIC.d \
./Sources/PIT.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


