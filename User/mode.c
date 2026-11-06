/**
 * @file mode.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-08-31
 * 
 * @copyright Copyright (c) 2026
 * 
 */
 #include "mode.h"

 Mode_Handle_t ModeHandle;

 /**
  * @brief Mode Machine Init
  * 
  */
void Mode_MachineInit(void) {
    ModeHandle.CurrMode = 0;
    ModeHandle.NextMode = 0;
}

 /**
  * @brief MODE 状态机，将该函数放于main函数主循环中
  * 
  */
void Main_ModeMachine(Mode_Handle_t *mode_handle) {
    if((mode_handle->CurrMode == 0) && (mode_handle->NextMode == 0)) {
        //按住按键抽，松开停止
        if(KeyHandle.isHOLD == 1) {
            MotorHandle.isRUN = 1;
        }
        else {
            MotorHandle.isRUN = 0;
        }

        if(KeyHandle.DOUBLE == 1) {
            KeyHandle.DOUBLE = 0;
            mode_handle->NextMode = 1;
        }
    }

    if((mode_handle->CurrMode == 0) && (mode_handle->NextMode == 1)) {
        //Mode0 Exit 
        MotorHandle.isRUN = 0;

        //Mode1 Init
        KeyHandle.SINGLE = 0;
        mode_handle->CurrMode = mode_handle->NextMode;
    }

    if((mode_handle->CurrMode == 1) && (mode_handle->NextMode == 1)) {
        //单击启动，单击停止
        if(KeyHandle.SINGLE == 1) {
            KeyHandle.SINGLE = 0;
            if(MotorHandle.isRUN == 1) {
                MotorHandle.isRUN = 0;
            }else {
                MotorHandle.isRUN = 1;
            }
        }

        if(KeyHandle.DOUBLE == 1) {
            KeyHandle.DOUBLE = 0;
            mode_handle->NextMode = 0;
        }
    } 

    if((mode_handle->CurrMode == 1) && (mode_handle->NextMode == 0)) {
        //Mode0 Exit 
        MotorHandle.isRUN = 0;

        //Mode1 Init
        mode_handle->CurrMode = mode_handle->NextMode;
    }
}