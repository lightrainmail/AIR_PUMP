################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/core_riscv.c 

C_DEPS += \
./Core/core_riscv.d 

OBJS += \
./Core/core_riscv.o 

DIR_OBJS += \
./Core/*.o \

DIR_DEPS += \
./Core/*.d \

DIR_EXPANDS += \
./Core/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
Core/%.o: ../Core/%.c
	@	riscv-wch-elf-gcc -march=rv32ec_zmmul_xw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/Debug" -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/Core" -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/User" -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/Peripheral/inc" -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/BSP/DISP" -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/BSP/LED" -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/BSP/MOTOR" -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/BSP/KEY" -I"c:/Users/light/OneDrive/桌面/CH32V006F8U_AIR_PUMP_ES3/BSP/TYPEC" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

