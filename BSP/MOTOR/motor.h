/**
 * @file motor.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-06-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */

 #ifndef __AIR_PUMP_MOTOR_H
 #define __AIR_PUMP_MOTOR_H

#include "ch32v00X.h"
#include "ch32v00X_tim.h"

#define MOTOR_UPDATE_PERIOD    50   //50 * 0.5ms = 25ms

typedef struct {
   uint8_t tick;
   uint8_t period;
   uint8_t isRUN;
   uint16_t duty;
} Motor_Handle_t;

extern  Motor_Handle_t MotorHandle;

 /**
  * @brief TIM1 PWM Init
  * 
  */
void TIM1_PWM_Init(void);

/**
 * @brief Motor Init
 * 
 */
void Motor_Init(void);

/**
 * @brief Motor Tick Function
 * 
 */
void Motor_Tick(void);

/**
 * @brief 设定MOTOR PWM 波的占空比
    @param duty 占空比 0 ~ 999
 * 
 */
void Motor_PWM_Duty(Motor_Handle_t *motor_handle);

 #endif