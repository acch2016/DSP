################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/ADC.c \
../Sources/DAC.c \
../Sources/FREQ_SELECT.c \
../Sources/FlexTimer.c \
../Sources/GPIO.c \
../Sources/GlobalFunctions.c \
../Sources/I2C.c \
../Sources/MCG.c \
../Sources/MotionSensor.c \
../Sources/NVIC.c \
../Sources/PIT.c \
../Sources/SoundGen.c \
../Sources/main.c 

OBJS += \
./Sources/ADC.o \
./Sources/DAC.o \
./Sources/FREQ_SELECT.o \
./Sources/FlexTimer.o \
./Sources/GPIO.o \
./Sources/GlobalFunctions.o \
./Sources/I2C.o \
./Sources/MCG.o \
./Sources/MotionSensor.o \
./Sources/NVIC.o \
./Sources/PIT.o \
./Sources/SoundGen.o \
./Sources/main.o 

C_DEPS += \
./Sources/ADC.d \
./Sources/DAC.d \
./Sources/FREQ_SELECT.d \
./Sources/FlexTimer.d \
./Sources/GPIO.d \
./Sources/GlobalFunctions.d \
./Sources/I2C.d \
./Sources/MCG.d \
./Sources/MotionSensor.d \
./Sources/NVIC.d \
./Sources/PIT.d \
./Sources/SoundGen.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


