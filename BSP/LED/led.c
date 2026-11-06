/**
 * @file led.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-18
 * 
 * @copyright Copyright (c) 2026
 * 
 */
 #include "led.h"

uint16_t led_tick = 0;
LED_Handle_t hled1 = {50,5,5};
LED_Handle_t hled2 = {5,50,5};
LED_Handle_t hled3 = {5,5,100};

 /**
  * @brief LED GPIO Init
  * 
  */
  void LED_Init(void) {
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOC,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure = {0};

    GPIO_InitStructure.GPIO_Pin = LED_EN_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(LED_EN_Port,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LED_DATA_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(LED_DATA_Port,&GPIO_InitStructure);

    GPIO_WriteBit(LED_EN_Port,LED_EN_Pin,Bit_SET);
    GPIO_WriteBit(LED_DATA_Port,LED_DATA_Pin,Bit_RESET);
  }

  /**
   * @brief Open LED Power
   * 
   */
   void LED_POWER_ON(void) {
     GPIO_WriteBit(LED_EN_Port,LED_EN_Pin,Bit_RESET);
   }

/**
 * @brief Close LED Power
 * 
 */
void LED_POWER_OFF(void) {
    GPIO_WriteBit(LED_EN_Port,LED_EN_Pin,Bit_SET);
}
 
/**
 * @brief 提供延迟基准 _NOP() 0.166us
 * 
 */
 void DELAY_0_3US(void) {
    __NOP();
    __NOP();
 }

void DELAY_0_9US(void) {
    __NOP();
    __NOP();
    __NOP();
    __NOP();
}

void DELAY_0_7US(void) {
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
}

void DELAY_0_5US(void) {
    __NOP();
    __NOP();
}

/**
 * @brief Send 0
 * 
 */
void LED_Send_0(void){
   LED_DATA_Port->BSHR = LED_DATA_Pin;
    DELAY_0_3US();
    LED_DATA_Port->BCR = LED_DATA_Pin;
    DELAY_0_9US();
}

/**
 * @brief Send 1
 * 
 */
 void LED_Send_1(void){
    LED_DATA_Port->BSHR = LED_DATA_Pin;
    DELAY_0_7US();
    LED_DATA_Port->BCR = LED_DATA_Pin;
    DELAY_0_5US();
}

/**
 * @brief LED 发送颜色数据
 * 
 * @param green 
 * @param red 
 * @param blue 
 */
void LED_Send_Color(uint8_t red,uint8_t green,uint8_t blue) {
    // 发送绿色8位（高位在前）
    for (int i = 7; i >= 0; i--) {
        if (red & (0x01 << i)) LED_Send_1();
        else LED_Send_0();
    }
    // 发送红色8位
    for (int i = 7; i >= 0; i--) {
        if (green & (0x01 << i)) LED_Send_1();
        else LED_Send_0();
    }
    // 发送蓝色8位
    for (int i = 7; i >= 0; i--) {
        if (blue & (0x01 << i)) LED_Send_1();
        else LED_Send_0();
    }
}

/**
 * @brief RESET
 * 
 */
void LED_RESET(void) {
    LED_DATA_Port->BCR = LED_DATA_Pin;
    Delay_Us(100);
}

/**
 * @brief LED color control
 * 
 */
void LED_Color_Control(void) {
}

/**
 * @brief LED Update Function
 * 
 */
void LED_Update(void) {
    LED_Color_Control();
    LED_RESET();
    LED_Send_Color(hled1.red,hled1.green,hled1.blue);  //第一颗灯
    LED_Send_Color(hled2.red,hled2.green,hled2.blue);  //第二颗灯
    LED_Send_Color(hled3.red,hled3.green,hled3.blue);  //第三颗灯
    LED_RESET();
}

/**
 * @brief LED Tick function 设定10ms执行一次
 * 
 */
void LED_Tick(void){
    if(led_tick == 20) {
        led_tick = 0;
        LED_Update();
    }
    led_tick++;
}
