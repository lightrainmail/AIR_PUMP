/**
 * @file motor.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-06-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */
 #include "motor.h"

 Motor_Handle_t MotorHandle;

 /**
  * @brief TIM1 PWM Init
  * 
  */
void TIM1_PWM_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    TIM_OCInitTypeDef TIM_OCInitStruct = {0};
    TIM_TimeBaseInitTypeDef TIM_TimBaseInitStruct = {0};

    //开启时钟
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_TIM1 | RCC_PB2Periph_GPIOC | RCC_PB2Periph_AFIO,ENABLE);

    //配置PC2为复用推挽输出功能
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIOC,&GPIO_InitStruct);

    //将TIM3_CH1N通道重映射到PC2这个引脚上
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);

    TIM_TimBaseInitStruct.TIM_Period = 1000 - 1;
    TIM_TimBaseInitStruct.TIM_Prescaler = 96 - 1;
    TIM_TimBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimBaseInitStruct.TIM_RepetitionCounter = 0x00;
    TIM_TimeBaseInit(TIM1,&TIM_TimBaseInitStruct);

    //配置PWM模式
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 0;     //初始化时输出占空比0 PWM，这个CH3N输出100%占空比，MOS保持关断状态
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Set;
    TIM_OC3Init(TIM1,&TIM_OCInitStruct);

    //开启PWM输出和使能定时器
    TIM_CtrlPWMOutputs(TIM1,ENABLE);
    TIM_Cmd(TIM1,ENABLE);
}

/**
 * @brief Motor Init
 * 
 */
void Motor_Init(void) {
    TIM1_PWM_Init();
    //Init Motor Handle
    MotorHandle.duty = 500;
    MotorHandle.isRUN = 0;
    MotorHandle.tick = 0;
    MotorHandle.period = MOTOR_UPDATE_PERIOD;
}

/**
 * @brief 设定MOTOR PWM 波的占空比
    @param duty 占空比 0 ~ 999
 * 
 */
void Motor_Update(Motor_Handle_t *motor_handle) {
    motor_handle->tick ++;
    if(motor_handle->tick == motor_handle -> period) {
        motor_handle->tick = 0;

         if(motor_handle->isRUN == 1){
            TIM_SetCompare3(TIM1,motor_handle->duty);
        }
        else if(motor_handle -> isRUN == 0) {
            TIM_SetCompare3(TIM1,0);
        }
    }
}

/**
 * @brief Motor Tick Function
 * 
 */
void Motor_Tick(void) {
    Motor_Update(&MotorHandle);
}