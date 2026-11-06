################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/adc.c \
../User/ch32v00X_it.c \
../User/main.c \
../User/pwr.c \
../User/system_ch32v00X.c \
../User/tim.c 

C_DEPS += \
./User/adc.d \
./User/ch32v00X_it.d \
./User/main.d \
./User/pwr.d \
./User/system_ch32v00X.d \
./User/tim.d 

OBJS += \
./User/adc.o \
./User/ch32v00X_it.o \
./User/main.o \
./User/pwr.o \
./User/system_ch32v00X.o \
./User/tim.o 

DIR_OBJS += \
./User/*.o \

DIR_DEPS += \
./User/*.d \

DIR_EXPANDS += \
./User/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	riscv-wch-elf-gcc -march=rv32ec_zmmul_xw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/Debug" -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/Core" -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/User" -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/Peripheral/inc" -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/BSP/DISP" -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/BSP/LED" -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/BSP/MOTOR" -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/BSP/KEY" -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/BSP/TYPEC" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

