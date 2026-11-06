################################################################################
# MRS Version: 2.5.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BSP/KEY/key.c 

C_DEPS += \
./BSP/KEY/key.d 

OBJS += \
./BSP/KEY/key.o 

DIR_OBJS += \
./BSP/KEY/*.o \

DIR_DEPS += \
./BSP/KEY/*.d \

DIR_EXPANDS += \
./BSP/KEY/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
BSP/KEY/%.o: ../BSP/KEY/%.c
	@	riscv-wch-elf-gcc -march=rv32ec_zmmul_xw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/admin/OneDrive/_32BitMCU/CH32/CH32V006/PROJECT_AIR_PUMP/CH32V006F8U_AIR_PUMP_ES6/Debug" -I"c:/Users/admin/OneDrive/_32BitMCU/CH32/CH32V006/PROJECT_AIR_PUMP/CH32V006F8U_AIR_PUMP_ES6/Core" -I"c:/Users/admin/OneDrive/_32BitMCU/CH32/CH32V006/PROJECT_AIR_PUMP/CH32V006F8U_AIR_PUMP_ES6/User" -I"c:/Users/admin/OneDrive/_32BitMCU/CH32/CH32V006/PROJECT_AIR_PUMP/CH32V006F8U_AIR_PUMP_ES6/Peripheral/inc" -I"c:/Users/admin/OneDrive/_32BitMCU/CH32/CH32V006/PROJECT_AIR_PUMP/CH32V006F8U_AIR_PUMP_ES6/BSP/DISP" -I"c:/Users/admin/OneDrive/_32BitMCU/CH32/CH32V006/PROJECT_AIR_PUMP/CH32V006F8U_AIR_PUMP_ES6/BSP/LED" -I"c:/Users/admin/OneDrive/_32BitMCU/CH32/CH32V006/PROJECT_AIR_PUMP/CH32V006F8U_AIR_PUMP_ES6/BSP/MOTOR" -I"c:/Users/admin/OneDrive/_32BitMCU/CH32/CH32V006/PROJECT_AIR_PUMP/CH32V006F8U_AIR_PUMP_ES6/BSP/KEY" -I"c:/Users/admin/OneDrive/_32BitMCU/CH32/CH32V006/PROJECT_AIR_PUMP/CH32V006F8U_AIR_PUMP_ES6/BSP/TYPEC" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

