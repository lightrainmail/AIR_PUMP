/**
 * @file typec.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-06-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */
 #ifndef __AIR_PUMP_TYPEC_H
 #define __AIR_PUMP_TYPEC_H

#include "ch32v00X.h"
#include "ch32v00X_gpio.h"

#define TYPEC_GPIO_Port     GPIOD
#define TYPEC_Pin           GPIO_Pin_2

typedef enum {
    TYPEC_STATE_IDLE = 0,
    TYPEC_STATE_IN,
    TYPEC_STATE_OUT
} TYPEC_State_t;

typedef struct {
    TYPEC_State_t typec_state;
} TYPECHandle_t;

extern TYPECHandle_t htypec;

/**
 * @brief TYPEC GPIO Init
 * 
 */
void TYPEC_GPIO_Init(void);

 /**
  * @brief TYPEC Init 放于0.5ms定时中断中 5ms执行一次
  */
void TYPEC_Tick(void);

 #endif