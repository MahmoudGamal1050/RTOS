

#ifndef TMU_INTERFACE_H
#define TMU_INTERFACE_H

#include "STD_TYPES.h"
void TMU_Init(void);
void TMU_CreateTask( void(*Fptr)(void),u16 Periodicity,u8 Priority,u16 FirstDelay);
void TMU_StartScheduler(void);
void TMU_SuspendTask(u8 Priority);
void TMU_ResumeTask(u8 Priority);
void TMU_DeleteTask(u8 Priority);




#endif 
