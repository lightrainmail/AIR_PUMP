/**
 * @file pwr.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-06-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef __AIR_PUMP_PWR_H
#define __AIR_PUMP_PWR_H

#include "ch32v00X.h"
#include "ch32v00X_pwr.h"
#include "key.h"
#include "typec.h"
#include "tim.h"
#include "motor.h"
#include "disp.h"

/**
 * @brief 配置待机模式唤醒源（事件模式） 并进入待机模式
 * 
 */
void Enter_StandbyMode(void);

/**
 * @brief PWR Tick 放于0.5ms的定时中断函数中。在松开按键的5s后进入休眠模式
 * 
 */
void PWR_Tick(void);

#endif