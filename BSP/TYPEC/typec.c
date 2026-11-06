/**
 * @file typec.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-06-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */

 #include "typec.h"

uint8_t typec_tick = 0;
TYPECHandle_t htypec = {TYPEC_STATE_IDLE};

 /**
  * @brief TYPEC Update
  * 
  */
void TYPEC_Update(void) {
    if(GPIO_ReadInputDataBit(TYPEC_GPIO_Port,TYPEC_Pin) == Bit_SET) {
        htypec.typec_state = TYPEC_STATE_IN;
    }
    else{
        htypec.typec_state = TYPEC_STATE_OUT;
    }
}

 /**
  * @brief TYPEC Init 放于0.5ms定时中断中 5ms执行一次
  */
void TYPEC_Tick(void) {
    if(typec_tick == 10) {
        typec_tick = 0;
        TYPEC_Update();
    }
    typec_tick++;
}

/**
 * @brief TYPEC GPIO Init
 * 
 */
void TYPEC_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOD,ENABLE);

    GPIO_InitStruct.GPIO_Pin = TYPEC_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(TYPEC_GPIO_Port,&GPIO_InitStruct);
}