/**
 * @file pwr.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-06-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "pwr.h"
uint16_t pwr_tick = 0;

/**
 * @brief 将所有未使用的脚配置成模拟输入
 * 
 */
void GPIO_unused_To_AIN_Mode(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOA | RCC_PB2Periph_GPIOC | RCC_PB2Periph_GPIOD,ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4;
    GPIO_Init(GPIOA,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_Init(GPIOD,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_Init(GPIOC,&GPIO_InitStruct);
}

/**
 * @brief 配置待机模式唤醒源（事件模式） 并进入待机模式
 * 
 */
void Enter_StandbyMode(void) {
    EXTI_InitTypeDef EXTI_InitStruct = {0};
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    //配置KEY唤醒源
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOC | RCC_PB2Periph_AFIO,ENABLE);

    GPIO_InitStruct.GPIO_Pin = KEY_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(KEY_GPIO_Port,&GPIO_InitStruct);

    //将PC5链接到EXTI线
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

    EXTI_InitStruct.EXTI_Line = EXTI_Line5;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Event;            //事件唤醒，而非中断事件。这样换新后不会立刻跳转中断服务函数，而是让程序从头开始执行
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;    //下降沿触发
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);

    //配置TYPEC唤醒源
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOD,ENABLE);

    GPIO_InitStruct.GPIO_Pin = TYPEC_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(TYPEC_GPIO_Port,&GPIO_InitStruct);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2);

    EXTI_InitStruct.EXTI_Line = EXTI_Line2;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Event;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);
    
    RCC_PB1PeriphClockCmd(RCC_PB1Periph_PWR,ENABLE);    //使能电源接口时钟
    PWR->CSR |= PWR_CSR_WUF;

    //功耗优化配置
    //关闭所有未使用的外设时钟
    RCC_PB1PeriphClockCmd(RCC_PB1Periph_TIM2,DISABLE);
    ADC_DeInit(ADC1);
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_TIM1 | RCC_PB2Periph_ADC1,DISABLE);

    //关闭DMA 
    RCC_HBPeriphClockCmd(RCC_HBPeriph_DMA1,DISABLE);
    DMA_DeInit(DMA1_Channel1);

    //将所有用不到的引脚配置为模拟输入
    GPIO_unused_To_AIN_Mode();

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC,&GPIO_InitStruct);

    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOA,DISABLE);
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOD,DISABLE);
    RCC_PB2PeriphResetCmd(RCC_PB2Periph_AFIO,DISABLE);

    
    //进入待机模式,并等待事件唤醒
    PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFI);
}

/**
 * @brief PWR Tick 放于0.5ms的定时中断函数中。在松开按键的5s后进入休眠模式
 * 
 */
void PWR_Tick(void) {
    if(pwr_tick == 10000){
        pwr_tick = 0;
        Enter_StandbyMode();
        SystemInit();
        LED_Init();
        LED_POWER_ON();
        TIM2_Init();
        ADC_DMA_Init();
        TIM1_PWM_Init();
        KEY_Init();
        TYPEC_GPIO_Init();
        DISP_IsShowTURBO(1);
    }

    if(MotorHandle.isRUN == 0) {
        pwr_tick++;
    }
    else {
        pwr_tick = 0;
    }
    
    if(htypec.typec_state == TYPEC_STATE_IN) {
        pwr_tick = 0;
    }
    
}