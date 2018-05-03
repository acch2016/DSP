################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/FlexTimer.c \
../Sources/GPIO.c \
../Sources/I2C.c \
../Sources/LCDNokia5110.c \
../Sources/LCDNokia5110Images.c \
../Sources/NVIC.c \
../Sources/SPI.c \
../Sources/UART.c \
../Sources/main.c \
../Sources/menu.c 

OBJS += \
./Sources/FlexTimer.o \
./Sources/GPIO.o \
./Sources/I2C.o \
./Sources/LCDNokia5110.o \
./Sources/LCDNokia5110Images.o \
./Sources/NVIC.o \
./Sources/SPI.o \
./Sources/UART.o \
./Sources/main.o \
./Sources/menu.o 

C_DEPS += \
./Sources/FlexTimer.d \
./Sources/GPIO.d \
./Sources/I2C.d \
./Sources/LCDNokia5110.d \
./Sources/LCDNokia5110Images.d \
./Sources/NVIC.d \
./Sources/SPI.d \
./Sources/UART.d \
./Sources/main.d \
./Sources/menu.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


