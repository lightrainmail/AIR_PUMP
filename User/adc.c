/**
 * @file adc.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-06-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */
 #include "adc.h"


 const float Verfint = 1.1962896214896215f;

uint16_t adc_values[ADC_CHANNEL_COUNT];  //DMA自动填充，数组的顺序即为配置的采样顺序
uint8_t adc_tick = 0;

uint16_t adc_buff[ADC_BUff_LENGTH];     //100个ADC值，窗口滤波器的窗口
uint8_t ADC_BUFF_FULL = 0;      //ADC BUFF 已满标志位
uint32_t sumADC = 0;
uint32_t adcTemp = 0;

 // 电压-电量查找表 (电压单位: mV, 电量单位: 1%)
// 注意: 这是示例数据，请务必根据您实际使用的电池进行校准
const float voltage_table[] = {4.2f, 4.1f, 4.0f, 3.9f, 3.8f, 3.7f, 3.6f, 3.5f, 3.4f, 3.3f, 3.2f, 3.1f, 3.0f};   //13
const uint8_t soc_table[] =   {100,   95,   90,   85,   75,   60,   45,   30,   20,   13,   8,    4,    0};
// 表中条目数量
#define TABLE_SIZE (sizeof(voltage_table) / sizeof(voltage_table[0]))

BatHandle hbat = {0,.times = 0,.delay = 0,.num = 0,.virtual_times = 0,.filter_num = 0};
uint8_t VIRTUAL_FALG = 0;

PowerHandle hpower = {.Uout = 0,.U1 = 0,.Iout = 0,.Pout = 0};

 /**
  * @brief 使用ADC连续转换 + DMA搬运数据的方式
  * 
  */
void ADC_DMA_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    ADC_InitTypeDef ADC_InitStruct = {0};
    DMA_InitTypeDef DMA_InitStruct = {0};

    //使能时钟
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOA | RCC_PB2Periph_ADC1,ENABLE);

    //配置PA1 PA2引脚
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA,&GPIO_InitStruct);

    //开启DMA时钟
    RCC_HBPeriphClockCmd(RCC_HBPeriph_DMA1,ENABLE);

    //开启ADC时钟
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_ADC1,ENABLE);
    

    
    //配置DMA接收ADC数据 ADC的数据走的DMA channel1（查看寄存器手册）
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->RDATAR;    //ADC的数据寄存器地址
    DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)adc_values;           //内存地址
    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;                     //外设 -> 内存
    DMA_InitStruct.DMA_BufferSize = ADC_CHANNEL_COUNT;                  //传输数量
    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;       //设定外设地址不自增
    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;                //设定内存地址自增
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;    //16bit
    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;            //16bit
    DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;                        //循环模式
    DMA_InitStruct.DMA_Priority = DMA_Priority_High;                  //设定优先级中等
    DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1,&DMA_InitStruct);

    //使能DMA通道（必须在ADC开始转换前调用，否则数据与通道不对应）
    DMA_Cmd(DMA1_Channel1,ENABLE);

    //配置ADC 扫描模式
    ADC_DeInit(ADC1);
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStruct.ADC_ScanConvMode = ENABLE;       //开启扫描模式,多通道所以要扫描模式
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE; //开启连续转换模式
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;    //不用外部触发条件，软件触发即可
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_NbrOfChannel = ADC_CHANNEL_COUNT;    //3个通道
    ADC_Init(ADC1,&ADC_InitStruct);

    //配置ADC时钟8分频 48MHz / 8
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);   

    // 5. 配置规则组通道顺序和采样时间[reference:11]
    //    ADC_RegularChannelConfig(ADC1, channel, order, SampleTime)
    //    参数说明：order 为转换顺序（1-based），数值越小越靠前转换
    ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_CyclesMode7);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,2,ADC_SampleTime_CyclesMode7);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_Vrefint,3,ADC_SampleTime_CyclesMode7);

    //使能ADC的DMA请求
    ADC_DMACmd(ADC1,ENABLE);

    //开启ADC，并开始转换 
    ADC_Cmd(ADC1,ENABLE);

    //启动ADC转换
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}


/**
 * @brief 根据电池电压，返回电压百分比
 * 
 */
uint8_t VoltageToPercentage(float voltage) {
    uint8_t percentage = 0;
    if(voltage > 4.2f) {
        voltage = 4.2f;
    }
    if(voltage < 3.01f) {
        voltage = 3.01f;
    }
    uint8_t i = 0;
    while(voltage_table[i] > voltage){
        i++;
    }
    if(i == 0) {
        percentage = 100;
    }
    float k = 0.0f;
    k = (soc_table[i - 1] - soc_table[i]) / (voltage_table[i - 1] - voltage_table[i]);
    percentage = (uint8_t) k * (voltage - voltage_table[i]) + soc_table[i];
    return percentage;
}

/**
 * @brief Batter Update 放于ADC_Tick中
 * 
 */
void Batter_Update(void) {
      if(MotorHandle.isRUN == 0) {
            hbat.delay ++;
            if(hbat.delay >= 24) {
                //按键松手120ms以后才开始读取BATTER电压，其实ADC一直在转换数据，只不过超过120ms后才开始记录
                hbat.delay = 24;
                hbat.times++;
                if(hbat.times >= 24) {
                    hbat.times = 0;
                    adc_buff[hbat.num] = adc_values[2]; //120ms下一个ADC值肯定已经准备好了
                    hbat.num ++;
                    if(ADC_BUFF_FULL == 1) {
                        for(uint8_t i = 0; i < ADC_BUff_LENGTH;i++) {
                            sumADC += adc_buff[i];
                        }
                    adcTemp = (sumADC + ADC_BUff_LENGTH / 2) / ADC_BUff_LENGTH;
                    sumADC = 0;
                        hbat.real_voltage = Verfint * 4095 / adcTemp;
                        hbat.real_percentage = VoltageToPercentage(hbat.real_voltage);
                    }
                    if(hbat.num == ADC_BUff_LENGTH){
                        hbat.num = 0;
                        ADC_BUFF_FULL = 1;
                    }
                }
                
            }
        }
        else{
            hbat.delay = 0;
        }

        hbat.virtual_times ++;
        if(hbat.virtual_times >= 2000) {
            hbat.virtual_times = 0;
            //虚拟电量部分
            if(htypec.typec_state == TYPEC_STATE_IN) {
                if(hbat.real_percentage > hbat.virtual_percentage) {
                    if(hbat.real_percentage - hbat.virtual_percentage >= 3) {
                        if(VIRTUAL_FALG == 0) {
                            hbat.virtual_percentage = hbat.real_percentage;
                            VIRTUAL_FALG = 1;
                        }
                        if(hbat.real_percentage - hbat.virtual_percentage <=7) {
                            hbat.virtual_percentage++;
                            hbat.filter_num = 0;
                        }
                        else if(hbat.real_percentage - hbat.virtual_percentage > 9) {
                            hbat.filter_num ++;
                            if(hbat.filter_num == 5) {
                                hbat.virtual_percentage++;
                            }
                        }
                    }
                }
            }
            if(htypec.typec_state == TYPEC_STATE_OUT) {
                if(hbat.real_percentage < hbat.virtual_percentage) {
                    if(hbat.virtual_percentage - hbat.real_percentage >= 3) {
                        if(hbat.virtual_percentage - hbat.real_percentage <= 7) {
                            hbat.virtual_percentage --;
                            hbat.filter_num = 0;
                        }
                        else if(hbat.virtual_percentage - hbat.real_percentage > 9) {
                            hbat.filter_num ++;
                            if(hbat.filter_num == 5) {
                                hbat.virtual_percentage --;
                            }
                        }
                    }
                }
            }
            
            //满电处理
            if(hbat.real_percentage >= 95) {
                if(htypec.typec_state == TYPEC_STATE_IN) {
                    hbat.virtual_percentage++;
                }
            }
            if(hbat.virtual_percentage >= 100) {
                hbat.virtual_percentage = 100;
            }
        }  
}

/**
 * @brief 用于测量输出功率
 * 
 */
void Power_Update(void){
    hpower.p_time ++;
    if(hpower.p_time >= 20) {
        hpower.p_time = 0;
        hpower.Uout = hbat.real_voltage * adc_values[1] / 4095;
        hpower.U1 = hbat.real_voltage * adc_values[0] / 4095;
        hpower.Iout = (hpower.U1 - hpower.Uout) / 0.5;
        hpower.Pout = hpower.Uout * hpower.Iout;
    }
}
 

/**
 * @brief ADC Tick 5ms执行一次 放于TIM2的 0.5ms定时中断函数中
 * 
 */
void ADC_Tick(void) {
    if(adc_tick == 10) {
        adc_tick = 0;
        Batter_Update();
        Power_Update();
    }
    adc_tick ++;
}