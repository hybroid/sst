################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../adc.c \
../encoder.c \
../main.c \
../seg_led.c \
../spi.c \
../uart.c 

OBJS += \
./adc.o \
./encoder.o \
./main.o \
./seg_led.o \
./spi.o \
./uart.o 

C_DEPS += \
./adc.d \
./encoder.d \
./main.d \
./seg_led.d \
./spi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Soft\_installed\avr8-gnu-toolchain\avr\include" -Wall -g2 -gdwarf-2 -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega88a -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


