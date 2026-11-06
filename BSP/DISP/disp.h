/**
 * @file disp.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
 #ifndef __AIR_PUMP_DISP_H
 #define __AIR_PUMP_DISP_H

#include "debug.h"

#define LED_GPIO_Port       GPIOD
#define LED1_Pin             GPIO_Pin_3

#define LED_GPIO_Port      GPIOD
#define LED2_Pin            GPIO_Pin_4

#define LED_GPIO_Port      GPIOD
#define LED3_Pin            GPIO_Pin_5

#define LED_GPIO_Port      GPIOD
#define LED4_Pin            GPIO_Pin_6

#define LED_GPIO_Port      GPIOD
#define LED5_Pin            GPIO_Pin_7


/**
 * @brief 控制数码管显示数字
 * 
 */
void DISP_ShowNum(uint8_t shownum);

 /**
* @brief DISP Tick 将其放入定时中断函数中
* 
*/
void DISP_Tick(void);

// 请务必添加FLASH操作相关的头文件，如 #include "ch32v00x_flash.h"

void PD7_To_GPIO_Init(void);

/**
 * @brief 控制数码管显示闪电符号
 * @param 1显示FLASH 0不显示FLASH
 */
void DISP_IsShowFlash(uint8_t Flash_EN);

 /**
  * @brief 数码管是否显示TURBO
  * @param 1显示TURBO 0不显示TURBO
  */
void DISP_IsShowTURBO(uint8_t TURBO_EN);

 #endif