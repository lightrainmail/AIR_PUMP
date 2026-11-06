/**
 * @file adc.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-06-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */
 #ifndef __AIR_PUMP_ADC_H
 #define __AIR_PUMP_ADC_H

#include "ch32v00X.h"
#include "ch32v00X_adc.h"
#include "ch32v00X_dma.h"
#include "ch32v00X_rcc.h"
#include "key.h"
#include "math.h"
#include "disp.h"
#include "typec.h"
#include "motor.h"

#define ADC_CHANNEL_COUNT   3   //ADC_CH0 ADC_CH1 内部电压基准
#define ADC_BUff_LENGTH     10 //控制滑动窗口滤波器的窗口长度

extern uint16_t adc_values[ADC_CHANNEL_COUNT];
extern volatile uint8_t ADC_CouvFinish_FLAG;
extern uint16_t adc_buff[ADC_BUff_LENGTH]; 

extern uint8_t batter_percentage;
extern uint8_t BATTER_PERCNETAGE_OK_FLAG;
extern uint8_t ADC_BUFF_FULL;

typedef struct
{
    float real_voltage;         //实际电池电压
    float virtual_voltage;      //虚拟电池电压
    uint8_t real_percentage;
    uint8_t virtual_percentage;
    uint16_t times;             //时间计数
    uint16_t delay;             //按键松开后延迟时间
    uint16_t num;               //adc buff第几个数字
    uint16_t virtual_times;
    uint8_t filter_num;
} BatHandle;

extern BatHandle hbat;

typedef struct {
    float Uout;
    float U1;
    float Iout;
    float Pout;

    uint32_t p_time;
} PowerHandle;

extern PowerHandle hpower;

 /**
  * @brief 使用ADC连续转换 + DMA搬运数据的方式
  * 
  */
  void ADC_DMA_Init(void);

  /**
 * @brief ADC Tick 10ms执行一次 放于TIM2的 0.5ms定时中断函数中
 * 
 */
void ADC_Tick(void);

 #endif