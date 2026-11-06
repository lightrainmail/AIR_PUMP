/**
 * @file disp.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-30
 * 
 * @copyright Copyright (c) 2026
 * 
 */

 #include "disp.h"

uint8_t tick = 0; 		//Tick 
int times = 1;		//当前进程

uint8_t num = 0;	//要显示的数字
 uint8_t Flash_FLAG = 0;	//数码管闪电图标与数字是否显示 0:不显示 1:显示
 uint8_t TURBO_FLAG = 0;	//turbo模式是否开启	0不开启 1开启
 uint8_t units = 0;
 uint8_t tens = 0;
 uint8_t hundreds = 0;

 /**
  * @brief LED PIN Input Mode
  * 
  */
void DISP_GPIO_Input(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOD,ENABLE);

    GPIO_InitStruct.GPIO_Pin = LED1_Pin | LED2_Pin | LED3_Pin | LED4_Pin | LED5_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(LED_GPIO_Port,&GPIO_InitStruct);
}

  /**
   * @brief LED1 GPIO Out Mode
   * 
   */
   void DISP_LED1_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOD,ENABLE);

    GPIO_InitStruct.GPIO_Pin = LED1_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(LED_GPIO_Port,&GPIO_InitStruct);
}

     /**
   * @brief LED2 GPIO Out Mode
   * 
   */
   void DISP_LED2_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOD,ENABLE);

    GPIO_InitStruct.GPIO_Pin = LED2_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(LED_GPIO_Port,&GPIO_InitStruct);
}

     /**
   * @brief LED3 GPIO Out Mode
   * 
   */
   void DISP_LED3_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOD,ENABLE);

    GPIO_InitStruct.GPIO_Pin = LED3_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(LED_GPIO_Port,&GPIO_InitStruct);
}

     /**
   * @brief LED4 GPIO Out Mode
   * 
   */
   void DISP_LED4_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOD,ENABLE);

    GPIO_InitStruct.GPIO_Pin = LED4_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(LED_GPIO_Port,&GPIO_InitStruct);
}

// 请务必添加FLASH操作相关的头文件，如 #include "ch32v00x_flash.h"

void PD7_To_GPIO_Init(void) {
    // 1. 解锁FLASH，允许修改配置
    FLASH_Unlock();

    // 2. 修改用户选项字节
    // 关键函数：FLASH_UserOptionByteConfig
    // 参数依次为：看门狗，待机复位，复位引脚使能，启动模式
    // **核心参数是第三个，设为DISABLE即可禁用PD7的复位功能**
    FLASH_UserOptionByteConfig(OB_IWDG_SW, OB_STDBY_NoRST, OB_RST_NoEN, OB_PowerON_Start_Mode_BOOT);

    // 3. 重新锁定FLASH
    FLASH_Lock();

    // 4. 触发系统复位，让新的配置生效
    NVIC_SystemReset();
}

     /**
   * @brief LED5 GPIO Out Mode
   * 
   */
   void DISP_LED5_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOD,ENABLE);

    GPIO_InitStruct.GPIO_Pin = LED5_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(LED_GPIO_Port,&GPIO_InitStruct);
}

/**
 * @brief Case 1 function
 * 
 */
 void DISP_Case_1(void) {
	DISP_GPIO_Input();
	DISP_LED1_Init();
	GPIO_WriteBit(LED_GPIO_Port,LED1_Pin,Bit_RESET);

	switch(tens){
		case 0:{
			//A1 B1 C1 D1
			DISP_LED2_Init();
			DISP_LED3_Init();
			DISP_LED4_Init();
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED2_Pin | LED3_Pin | LED4_Pin | LED5_Pin;
			break;
		}
		case 1:{
			break;
		}
		case 2:{
			//D1 A1
			DISP_LED5_Init();
			DISP_LED2_Init();
			DISP_LED3_Init();
			LED_GPIO_Port->BSHR = LED2_Pin | LED3_Pin | LED5_Pin;
			break;
		}
		case 3:{
			//D1 A1
			DISP_LED5_Init();
			DISP_LED2_Init();
			LED_GPIO_Port->BSHR = LED5_Pin | LED2_Pin;
			break;
		}
		case 4:{
			//C1
			DISP_LED4_Init();
			LED_GPIO_Port->BSHR = LED4_Pin;
			break;
		}
		case 5:{
			//D1 C1 A1
			DISP_LED5_Init();
			DISP_LED4_Init();
			DISP_LED2_Init();
			LED_GPIO_Port->BSHR = LED5_Pin | LED4_Pin | LED2_Pin;
			break;
		}
		case 6: {
			//A1 B1 C1 D1
			DISP_LED2_Init();
			DISP_LED3_Init();
			DISP_LED4_Init();
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED2_Pin | LED3_Pin | LED4_Pin | LED5_Pin;
			break;
		}
		case 7: {
			//D1
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED5_Pin;
			break;
		}
		case 8: {
			//A1 B1 C1 D1
			DISP_LED2_Init();
			DISP_LED3_Init();
			DISP_LED4_Init();
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED2_Pin | LED3_Pin | LED4_Pin | LED5_Pin;
			break;
		}
		case 9: {
			//C1 D1
			DISP_LED4_Init();
			DISP_LED5_Init();
			DISP_LED2_Init();
			LED_GPIO_Port->BSHR = LED4_Pin | LED5_Pin | LED2_Pin;
			break;
		}
		default:
			break;
	}
 }

 /**
  * @brief DISP Case 2 function
  * 
  */
  void DISP_Case_2(void) {
	DISP_GPIO_Input();
	DISP_LED2_Init();
	LED_GPIO_Port->BCR = LED2_Pin;
	switch(tens) {
		case 0:{
			DISP_LED1_Init();
			DISP_LED3_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED3_Pin;
			break;
		}
		case 1:{
			DISP_LED1_Init();
			DISP_LED3_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED3_Pin;
			break;
		}
		case 2: {
			DISP_LED1_Init();
			DISP_LED4_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED4_Pin;
			break;
		}
		case 3: {
			DISP_LED1_Init();
			DISP_LED3_Init();
			DISP_LED4_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED3_Pin | LED4_Pin;
			break;
		}
		case 4: {
			DISP_LED1_Init();
			DISP_LED3_Init();
			DISP_LED4_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED3_Pin | LED4_Pin;
			break;
		}
		case 5: {
			DISP_LED3_Init();
			DISP_LED4_Init();
			LED_GPIO_Port->BSHR = LED3_Pin | LED4_Pin;
			break;
		}
		case 6: {
			DISP_LED3_Init();
			DISP_LED4_Init();
			LED_GPIO_Port->BSHR = LED3_Pin | LED4_Pin;
			break;
		}
		case 7: {
			DISP_LED1_Init();
			DISP_LED3_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED3_Pin;
			break;
		}
		case 8: {
			DISP_LED1_Init();
			DISP_LED3_Init();
			DISP_LED4_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED3_Pin | LED4_Pin;
			break;
		}
		case 9: {
			DISP_LED1_Init();
			DISP_LED3_Init();
			DISP_LED4_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED3_Pin | LED4_Pin;
			break;
		}
		default:
			break;
	}

	switch (units) {
		case 0: {
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED5_Pin;
			break;
		}
		case 1: {
			break;
		}
		case 2:{
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED5_Pin;
			break;
		}
		case 3:{
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED5_Pin;
			break;
		}
		case 4:{
			break;
		}
		case 5:{
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED5_Pin;
			break;
		}
		case 6: {
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED5_Pin;
			break;
		}
		case 7:{
			break;
		}
		case 8:{
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED5_Pin;
			break;
		}
		case 9:{
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED5_Pin;
			break;
		}
		default:
			break;
	}
  }

/**
 * @brief case 3 function
 * 
 */
void DISP_Case_3(void) {
	DISP_GPIO_Input();
	DISP_LED3_Init();
	LED_GPIO_Port->BCR = LED3_Pin;

	switch (units) {
		case 0:{
			DISP_LED1_Init();
			DISP_LED2_Init();
			DISP_LED4_Init();
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED2_Pin | LED4_Pin | LED5_Pin;
			break;
		}
		case 1 : {
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED5_Pin;
			break;
		}
		case 2:{
			DISP_LED4_Init();
			DISP_LED5_Init();
			DISP_LED1_Init();
			LED_GPIO_Port->BSHR = LED4_Pin | LED5_Pin | LED1_Pin;
			break;
		}
		case 3:{
			DISP_LED4_Init();
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED4_Pin | LED5_Pin;
			break;
		}
		case 4: {
			DISP_LED2_Init();
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED2_Pin | LED5_Pin;
			break;
		}
		case 5: {
			DISP_LED4_Init();
			DISP_LED2_Init();
			LED_GPIO_Port->BSHR = LED4_Pin | LED2_Pin;
			break;
		}
		case 6: {
			DISP_LED1_Init();
			DISP_LED2_Init();
			DISP_LED4_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED2_Pin | LED4_Pin;
			break;
		}
		case 7: {
			DISP_LED4_Init();
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED4_Pin | LED5_Pin;
			break;
		}
		case 8:{
			DISP_LED1_Init();
			DISP_LED2_Init();
			DISP_LED4_Init();
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED2_Pin | LED4_Pin | LED5_Pin;
			break;
		}
		case 9: {
			DISP_LED2_Init();
			DISP_LED4_Init();
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED2_Pin | LED4_Pin | LED5_Pin;
			break;
		}
		default:
			break;
	
	}
}

/**
 * @brief case 4 function
 * 
 */
 void DISP_Case_4(void) {
	DISP_GPIO_Input();
	DISP_LED4_Init();
	LED_GPIO_Port->BCR = LED4_Pin;
	switch (units) {
		case 0:{
			DISP_LED1_Init();
			LED_GPIO_Port->BSHR = LED1_Pin;
			break;
		}
		case 1: {
			DISP_LED1_Init();
			LED_GPIO_Port->BSHR = LED1_Pin;
			break;
		}
		case 2: {
			DISP_LED2_Init();
			LED_GPIO_Port->BSHR = LED2_Pin;
			break;
		}
		case 3:{
			DISP_LED1_Init();
			DISP_LED2_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED2_Pin;
			break;
		}
		case 4: {
			DISP_LED1_Init();
			DISP_LED2_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED2_Pin;
			break;
		}
		case 5:{
			DISP_LED1_Init();
			DISP_LED2_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED2_Pin;
			break;
		}
		case 6: {
			DISP_LED1_Init();
			DISP_LED2_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED2_Pin;
			break;
		}
		case 7: {
			DISP_LED1_Init();
			LED_GPIO_Port->BSHR = LED1_Pin;
			break;
		}
		case 8: {
			DISP_LED1_Init();
			DISP_LED2_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED2_Pin;
			break;
		}
		case 9: {
			DISP_LED1_Init();
			DISP_LED2_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED2_Pin;
			break;
		}
		default:
			break;
	}

	switch (Flash_FLAG) {
		case 0: {
			break;
		}
		case 1: {
			DISP_LED3_Init();
			DISP_LED5_Init();
			LED_GPIO_Port->BSHR = LED3_Pin | LED5_Pin;
			break;
		}
		default:
			break;
	}
 }

/**
 * @brief case 5 function
 * 
 */
 void DISP_Case_5(void) {
	DISP_GPIO_Input();
	DISP_LED5_Init();
	LED_GPIO_Port->BCR = LED5_Pin;

	switch (hundreds) {
		case 0: {
			break;
		}
		case 1: {
			DISP_LED1_Init();
			DISP_LED2_Init();
			LED_GPIO_Port->BSHR = LED1_Pin | LED2_Pin;
			break;
		}
		default:
			break;
	}

	switch (TURBO_FLAG) {
		case 0: {
			break;
		}
		case 1: {
			DISP_LED3_Init();
			DISP_LED4_Init();
			LED_GPIO_Port->BSHR = LED3_Pin | LED4_Pin;
			break;
		}
		default:
			break;
	}

 }


   /**
    * @brief DISP Update 刷新DISP显示
    * 
    */
void DISP_Update(void) {
	switch(times) {
		case 1:{
			DISP_Case_1();
			break;
		}
		case 2:{
			DISP_Case_2();
			break;
		}
			
		case 3:{
			DISP_Case_3();
			break;
		}
			
		case 4:{
			DISP_Case_4();
			break;
		}
			
		case 5:{
			DISP_Case_5();
			break;
		}
			
		default:
			break;
	}
		
	times = times + 1;
	if(times == 6) {
		times = 1;
	}
}

 /**
* @brief DISP Tick 将其放入定时中断函数中
* 
*/
void DISP_Tick(void) {
	tick++;
	if(tick == 1) {
		tick = 0;
		DISP_Update();
	}
	
}	

/**
 * @brief 控制数码管显示数字
 * 
 */
void DISP_ShowNum(uint8_t shownum) {
	num = shownum;
	units = num % 10;
	tens = (num / 10) % 10;
	if(num >= 100) {
		hundreds = 1;
	}
	else{
		hundreds = 0;
	}
}

/**
 * @brief 控制数码管显示闪电符号
 * @param 1显示FLASH 0不显示FLASH
 */
void DISP_IsShowFlash(uint8_t Flash_EN) {
	if(Flash_EN == 0) {
		Flash_FLAG = 0;
	}
	else {
		Flash_FLAG = 1;
	}
}

 /**
  * @brief 数码管是否显示TURBO
  * @param 1显示TURBO 0不显示TURBO
  */
void DISP_IsShowTURBO(uint8_t TURBO_EN) {
	if(TURBO_EN == 0) {
		TURBO_FLAG = 0;
	}
	else {
		TURBO_FLAG = 1;
	}
}

