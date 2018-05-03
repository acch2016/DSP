################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/FlexTimer.c \
../Sources/GPIO.c \
../Sources/GlobalFunctions.c \
../Sources/NVIC.c \
../Sources/main.c 

OBJS += \
./Sources/FlexTimer.o \
./Sources/GPIO.o \
./Sources/GlobalFunctions.o \
./Sources/NVIC.o \
./Sources/main.o 

C_DEPS += \
./Sources/FlexTimer.d \
./Sources/GPIO.d \
./Sources/GlobalFunctions.d \
./Sources/NVIC.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


