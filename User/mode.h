/**
 * @file mode.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-08-31
 * 
 * @copyright Copyright (c) 2026
 * 
 */
 #ifndef __MODE_H
 #define __MODE_H

 #include "ch32v00X.h"
 #include "key.h"
 #include "motor.h"

 typedef struct {
    uint8_t CurrMode;
    uint8_t NextMode;
 } Mode_Handle_t;

extern Mode_Handle_t ModeHandle;

 /**
  * @brief Mode Machine Init
  * 
  */
void Mode_MachineInit(void);

 /**
  * @brief MODE 状态机，将该函数放于main函数主循环中
  * 
  */
void Main_ModeMachine(Mode_Handle_t *mode_handle);

 #endif
