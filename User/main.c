/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2024/01/01
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *Multiprocessor communication mode routine:
 *Master:USART1_Tx(PD5)\USART1_Rx(PD6).
 *This routine demonstrates that USART1 receives the data sent by CH341 and inverts
 *it and sends it (baud rate 115200).
 *
 *Hardware connection:PD5 -- Rx
 *                     PD6 -- Tx
 *
 */

#include "debug.h"
#include "disp.h"
#include "tim.h"
#include "led.h"
#include "adc.h"
#include "motor.h"
#include "key.h"
#include "typec.h"
#include "pwr.h"
#include "mode.h"

/* Global define */
uint8_t num_disp = 0;


/* Global Variable */

/* Function Define */
void TIM2_CallBackFun(void);

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    SystemInit();
    Delay_Init();

    //外设初始化
    // PD7_To_GPIO_Init();
    TIM2_Init();
    ADC_DMA_Init();

    Motor_Init();
    KEY_Init();
    TYPEC_GPIO_Init();
    LED_Init();
    Mode_MachineInit();

    Delay_Ms(1000);
    Delay_Ms(1000);
    
    DISP_IsShowTURBO(0);

    LED_POWER_ON();
    while(1)
    {
        if(htypec.typec_state == TYPEC_STATE_IN) {
            DISP_IsShowFlash(1);
        }
        else{
            DISP_IsShowFlash(0);
        }

        Main_ModeMachine(&ModeHandle);

        if(ModeHandle.CurrMode == 0) {
            DISP_IsShowTURBO(1);
        }
        else {
            DISP_IsShowTURBO(0);
        }
        
        DISP_ShowNum(hbat.virtual_percentage);
        Delay_Ms(1);
    }
}

/**
 * @brief TIM2 Callback function  0.5ms执行一次
 * 
 */
void TIM2_CallBackFun(void) {
    DISP_Tick();
    ADC_Tick();
    TYPEC_Tick();
    KEY_Tick();
    LED_Tick();
    PWR_Tick();
    Motor_Tick();
}

