/**
 * @file key.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-06-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */
 #ifndef __AIR_PUMP_KEY_H
 #define __AIR_PUMP_KEY_H

#include "ch32v00X.h"
#include "ch32v00X_gpio.h"
#include "ch32v00X_pwr.h"
#include "led.h"

/* 正确的PWR寄存器地址和位定义 (请务必与您的芯片手册核对) */
#define PWR_CSR_WUF         (1 << 0)    // 唤醒标志位
#define PWR_CSR_SBF         (1 << 1)    // 待机标志位

//设定 KEY Update 更新周期  单位0.5ms
#define KEY_UPDATE_PERIOD       20  //20*0.5ms = 10ms
#define KEY_INIT_DOUBLE_TIME    10  //10*10 = 100ms
#define KEY_INIT_TRIPE_TIME     10  //10*10 = 100ms
#define KEY_INIT_LONG_TIME      50  //50*10 = 500ms


#define KEY_GPIO_Port   GPIOC
#define KEY_Pin         GPIO_Pin_5

typedef struct {
    uint8_t KeyState;

    uint8_t tick;
    uint8_t period; //KEY Update 更新周期
    uint8_t double_time;
    uint8_t tripe_time;
    uint8_t long_time;

    unsigned int isHOLD : 1;    
    unsigned int LONG : 1;
    unsigned int SINGLE : 1;
    unsigned int DOUBLE : 1;
    unsigned int TRIPE : 1;
} KEY_Handle_t;

extern KEY_Handle_t KeyHandle;

/**
 * @brief 按键初始化函数
 * 
 */
void KEY_Init(void);

/**
 * @brief KEY tick 放于0.5ms定时中断函数中 每隔20ms执行一次
 * 
 */
void KEY_Tick(void);

 #endif