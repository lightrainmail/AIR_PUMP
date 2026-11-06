/**
 * @file key.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-06-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */
 #include "key.h"

KEY_Handle_t KeyHandle;

/**
 * @brief 按键初始化函数
 * 
 */
void KEY_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOC,ENABLE);
    GPIO_InitStruct.GPIO_Pin = KEY_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(KEY_GPIO_Port,&GPIO_InitStruct);

    //初始化按键结构体
    KeyHandle.period = KEY_UPDATE_PERIOD;
    KeyHandle.double_time = KEY_INIT_DOUBLE_TIME;
    KeyHandle.tripe_time = KEY_INIT_TRIPE_TIME;
    KeyHandle.long_time = KEY_INIT_LONG_TIME;

    KeyHandle.tick = 0;
    KeyHandle.KeyState = 0;
    KeyHandle.isHOLD = 0;
    KeyHandle.LONG = 0;
    KeyHandle.SINGLE = 0;
    KeyHandle.DOUBLE = 0;
    KeyHandle.TRIPE = 0;
}

/**
 * @brief 返回按键状态
 * 
 */
 void KEY_IsHold(KEY_Handle_t *key_handle_t) {
    if(GPIO_ReadInputDataBit(KEY_GPIO_Port,KEY_Pin) == 1) {
        key_handle_t->isHOLD = 0;
    }
    else {
        key_handle_t->isHOLD = 1;
    }
 }


/**
 * @brief KEY Update 更新按键状态
 * 
 */
void KEY_Update(KEY_Handle_t *key_handle_t) {
    key_handle_t->tick ++;
    if(key_handle_t->tick == key_handle_t->period) {
        key_handle_t->tick = 0;

        KEY_IsHold(key_handle_t);
        switch(key_handle_t->KeyState) {
            case 0:{
                if(key_handle_t->isHOLD == 1) {
                    key_handle_t->KeyState = 1;
                }
                break;
            }
            case 1:{
                key_handle_t->long_time --;
                if(key_handle_t->long_time == 0) {
                    key_handle_t->long_time = KEY_INIT_LONG_TIME;
                    key_handle_t->LONG = 1;
                    key_handle_t->KeyState = 6;
                }

                if(key_handle_t->isHOLD == 0) {
                    key_handle_t->long_time = KEY_INIT_LONG_TIME;
                    key_handle_t->KeyState = 2;
                }
                break;
            }
            case 2:{
                key_handle_t->double_time --;
                if(key_handle_t->double_time == 0) {
                    key_handle_t->double_time = KEY_INIT_DOUBLE_TIME;
                    key_handle_t->SINGLE = 1;
                    key_handle_t->KeyState = 0;
                }

                if(key_handle_t->isHOLD == 1) {
                    key_handle_t->double_time = KEY_INIT_DOUBLE_TIME;
                    key_handle_t->KeyState = 3;
                }
                break;
            }
            case 3:{
                if(key_handle_t->isHOLD == 0) {
                    key_handle_t->KeyState = 4;
                }
                break;
            }
            case 4:{
                key_handle_t->tripe_time --;
                if(key_handle_t->tripe_time == 0) {
                    key_handle_t->tripe_time = KEY_INIT_TRIPE_TIME;
                    key_handle_t->DOUBLE = 1;
                    key_handle_t->KeyState = 0;
                }

                if(key_handle_t->isHOLD == 1) {
                    key_handle_t->tripe_time = KEY_INIT_TRIPE_TIME;
                    key_handle_t->TRIPE = 1;
                    key_handle_t->KeyState = 5;
                }
                break;
            }
            case 5:{
                if(key_handle_t->isHOLD == 0) {
                    key_handle_t->KeyState = 0;
                }
                break;
            }
            case 6: {
                if(key_handle_t->isHOLD == 0) {
                    key_handle_t->KeyState = 0;
                }
            }
            default:
                break;
        }
    }
}

/**
 * @brief KEY tick 放于0.5ms定时中断函数中
 * 
 */
void KEY_Tick(void) {
    KEY_Update(&KeyHandle);
}


