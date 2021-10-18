################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../DC.c \
../DIO.c \
../LCD.c \
../Timer.c \
../UART.c \
../main.c 

OBJS += \
./ADC.o \
./DC.o \
./DIO.o \
./LCD.o \
./Timer.o \
./UART.o \
./main.o 

C_DEPS += \
./ADC.d \
./DC.d \
./DIO.d \
./LCD.d \
./Timer.d \
./UART.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


