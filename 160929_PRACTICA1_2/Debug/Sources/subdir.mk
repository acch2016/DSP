################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/._DAC.c \
../Sources/._FUNC.c \
../Sources/._GPIO.c \
../Sources/._MOTOR.c \
../Sources/._Matrix.c \
../Sources/._NVIC.c \
../Sources/._PIT.c \
../Sources/._main.c \
../Sources/DAC.c \
../Sources/FUNC.c \
../Sources/GPIO.c \
../Sources/MOTOR.c \
../Sources/Matrix.c \
../Sources/NVIC.c \
../Sources/PIT.c \
../Sources/main.c 

OBJS += \
./Sources/._DAC.o \
./Sources/._FUNC.o \
./Sources/._GPIO.o \
./Sources/._MOTOR.o \
./Sources/._Matrix.o \
./Sources/._NVIC.o \
./Sources/._PIT.o \
./Sources/._main.o \
./Sources/DAC.o \
./Sources/FUNC.o \
./Sources/GPIO.o \
./Sources/MOTOR.o \
./Sources/Matrix.o \
./Sources/NVIC.o \
./Sources/PIT.o \
./Sources/main.o 

C_DEPS += \
./Sources/._DAC.d \
./Sources/._FUNC.d \
./Sources/._GPIO.d \
./Sources/._MOTOR.d \
./Sources/._Matrix.d \
./Sources/._NVIC.d \
./Sources/._PIT.d \
./Sources/._main.d \
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


