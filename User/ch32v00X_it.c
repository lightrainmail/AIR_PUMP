/********************************** (C) COPYRIGHT *******************************
 * File Name          : ch32v00X_it.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2024/11/04
 * Description        : Main Interrupt Service Routines.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include <ch32v00X_it.h>
#include "disp.h"
#include "adc.h"
#include "string.h"

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

extern void TIM2_CallBackFun(void);

/*********************************************************************
 * @fn      NMI_Handler
 *
 * @brief   This function handles NMI exception.
 *
 * @return  none
 */
void NMI_Handler(void)
{
  while (1)
  {
  }
}

/*********************************************************************
 * @fn      HardFault_Handler
 *
 * @brief   This function handles Hard Fault exception.
 *
 * @return  none
 */
void HardFault_Handler(void)
{
  NVIC_SystemReset();
  while (1)
  {
  }
}


/**
 * @brief 
 * 
 */
 void TIM2_IRQHandler(void) {
    // 检查是否是更新中断产生
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        // 清除中断标志位[reference:7]
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        TIM2_CallBackFun();
    }
}
