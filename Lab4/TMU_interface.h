

#ifndef TMU_INTERFACE_H
#define TMU_INTERFACE_H
#include "STD_TYPES.h"

void TMU_Init(void);
void TMU_SetCallBack(void(*ptr)(void));
void TMU_CreateTask( void(*Fptr)(void),
					 u16 Periodicity,
					 u8 Priority);

void TMU_Scheduler(void);

void TMU_StartScheduler(void);


#endif 
