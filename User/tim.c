/**
 * @file tim.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "tim.h"

/**
 * @brief 初始化TIM2，配置为0.5ms定时中断
 */
void TIM2_Init(void) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // 1. 使能TIM2时钟
    // 注意：TIM2外设通常挂在APB1总线上[reference:5]，请根据实际情况选择合适的函数
    RCC_PB1PeriphClockCmd(RCC_PB1Periph_TIM2, ENABLE);

    // 2. 配置定时器基本参数
    // 定时器计数模式为向上计数
    TIM_TimeBaseStructure.TIM_Period = 48 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 500 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // 3. 清除TIM2的更新中断标志位，并使能更新中断
    TIM_ClearFlag(TIM2, TIM_IT_Update);

    // 4. 配置NVIC中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    // 5. 使能TIM2计数器，开始计时
    TIM_Cmd(TIM2, ENABLE);
}