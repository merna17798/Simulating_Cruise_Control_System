################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../DIO.c \
../EXT_INT.c \
../LCD.c \
../Switches.c \
../Timer.c \
../UART.c \
../main.c 

OBJS += \
./ADC.o \
./DIO.o \
./EXT_INT.o \
./LCD.o \
./Switches.o \
./Timer.o \
./UART.o \
./main.o 

C_DEPS += \
./ADC.d \
./DIO.d \
./EXT_INT.d \
./LCD.d \
./Switches.d \
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


