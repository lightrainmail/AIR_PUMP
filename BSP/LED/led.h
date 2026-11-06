/**
 * @file led.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-18
 * 
 * @copyright Copyright (c) 2026
 * 
 */
 #ifndef _LED_H
 #define _LED_H

#include "ch32v00X.h"

#define LED_DATA_Port    GPIOC
#define LED_DATA_Pin     GPIO_Pin_1

#define LED_EN_Port     GPIOC
#define LED_EN_Pin      GPIO_Pin_0

typedef struct{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} LED_Handle_t;

/**
  * @brief LED GPIO Init
  * 
  */
void LED_Init(void);

  
/**
   * @brief Open LED Power
   * 
   */
void LED_POWER_ON(void);

/**
 * @brief Close LED Power
 * 
 */
void LED_POWER_OFF(void);

/**
 * @brief LED 发送颜色数据
 * 
 * @param green 
 * @param red 
 * @param blue 
 */
void LED_Send_Color(uint8_t red,uint8_t green,uint8_t blue);

/**
 * @brief RESET
 * 
 */
void LED_RESET(void);

/**
 * @brief LED Tick function 设定100ms执行一次
 * 
 */
void LED_Tick(void);

/**
 * @brief LED Update Function
 * 
 */
void LED_Update(void);

 #endif