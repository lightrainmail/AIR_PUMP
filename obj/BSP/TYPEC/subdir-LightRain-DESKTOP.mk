################################################################################
# MRS Version: 2.5.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/TYPEC/typec.c 

C_DEPS += \
./BSP/TYPEC/typec.d 

OBJS += \
./BSP/TYPEC/typec.o 

DIR_OBJS += \
./BSP/TYPEC/*.o \

DIR_DEPS += \
./BSP/TYPEC/*.d \

DIR_EXPANDS += \
./BSP/TYPEC/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
BSP/TYPEC/%.o: ../BSP/TYPEC/%.c
	@	riscv-wch-elf-gcc -march=rv32ec_zmmul_xw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/LightRain/OneDrive/_32BitMCU/CH32/CH32V006/CH32V006F8U_AIR_PUMP_ES4/Debug" -I"c:/Users/LightRain/OneDrive/_32BitMCU/CH32/CH32V006/CH32V006F8U_AIR_PUMP_ES4/Core" -I"c:/Users/LightRain/OneDrive/_32BitMCU/CH32/CH32V006/CH32V006F8U_AIR_PUMP_ES4/User" -I"c:/Users/LightRain/OneDrive/_32BitMCU/CH32/CH32V006/CH32V006F8U_AIR_PUMP_ES4/Peripheral/inc" -I"c:/Users/LightRain/OneDrive/_32BitMCU/CH32/CH32V006/CH32V006F8U_AIR_PUMP_ES4/BSP/DISP" -I"c:/Users/LightRain/OneDrive/_32BitMCU/CH32/CH32V006/CH32V006F8U_AIR_PUMP_ES4/BSP/LED" -I"c:/Users/LightRain/OneDrive/_32BitMCU/CH32/CH32V006/CH32V006F8U_AIR_PUMP_ES4/BSP/MOTOR" -I"c:/Users/LightRain/OneDrive/_32BitMCU/CH32/CH32V006/CH32V006F8U_AIR_PUMP_ES4/BSP/KEY" -I"c:/Users/LightRain/OneDrive/_32BitMCU/CH32/CH32V006/CH32V006F8U_AIR_PUMP_ES4/BSP/TYPEC" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

