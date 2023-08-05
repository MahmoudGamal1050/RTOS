/*********************************************************************************
 ******************* LAB2 Task To ISR Synch. using Semaphore *********************
 ********************************************************************************/


#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "ADC_interface.h"
#include "LCD_interface.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#define SENSORS_NUM 4
static uint16 Digital[SENSORS_NUM]={0};
static uint32 Analog[SENSORS_NUM]={0};
static uint8 Ch_Num=1 ;
void SystemInit(void);
void ADC_notification(void);

void LCD_Task(void *pv);
void ADC_Task(void *pv);
void POT1_Task(void *pv);
void POT2_Task(void *pv);
void POT3_Task(void *pv);
void TempSensor_Task(void *pv);



xSemaphoreHandle sem = NULL;


int main(void)
{

	SystemInit();

	xTaskCreate(ADC_Task  , NULL, 100, NULL, 1, NULL);
	xTaskCreate(TempSensor_Task  , NULL, 100, NULL, 2, NULL);
	xTaskCreate(POT1_Task  , NULL, 100, NULL, 2, NULL);
	xTaskCreate(POT2_Task  , NULL, 100, NULL, 2, NULL);
	xTaskCreate(POT3_Task  , NULL, 100, NULL, 2, NULL);

	xTaskCreate(LCD_Task, NULL, 150, NULL, 3, NULL);

	sem = xSemaphoreCreateBinary();
	vTaskStartScheduler();

}


void ADC_Task(void *pv)
{
	static uint16 count =0;
	while(1)
	{
		ADC_voidStartConversionWithInterrupt(Ch_Num);
		ADC_voidSetCallBack(ADC_notification);
		ADC_voidInterruptEnable();

		if(xSemaphoreTake(sem, 2000) == pdPASS)
		{

			Digital[count] = ADC_u16ADCRead();
			count++;
			if(count==SENSORS_NUM)
			{
				count =0;
			}

		}

		vTaskDelay(100);
	}
}


void POT1_Task(void *pv)
{
	while(1)
	{
		Analog[0] = (Digital[0]*5000UL)/1023;
		vTaskDelay(100);
	}
}
void POT2_Task(void *pv)
{
	while(1)
	{
		Analog[1] = (Digital[1]*5000UL)/1023;
		vTaskDelay(100);
	}
}
void POT3_Task(void *pv)
{
	while(1)
	{
		Analog[2] = (Digital[2]*5000UL)/1023;
		vTaskDelay(100);
	}
}
void TempSensor_Task(void *pv)
{
	while(1)
	{
		Analog[3] = (Digital[3]*500)/(1023);
		vTaskDelay(100);
	}
}

void LCD_Task(void *pv)
{
	LCD_voidClearScreen();

	LCD_voidSetPosition(0, 0);
	LCD_voidWriteString("1:");
	LCD_voidSetPosition(0, 8);
	LCD_voidWriteString("2:");
	LCD_voidSetPosition(1, 0);
	LCD_voidWriteString("3:");
	LCD_voidSetPosition(1, 8);
	LCD_voidWriteString("4:");

	while(1)
	{
		LCD_voidSetPosition(0, 3);
		LCD_voidWriteString("	");
		LCD_voidSetPosition(0, 3);
		LCD_voidWriteNumber(Analog[0]);
		LCD_voidSetPosition(0,11 );
		LCD_voidWriteString("	");
		LCD_voidSetPosition(0, 11);
		LCD_voidWriteNumber(Analog[1]);

		LCD_voidSetPosition(1, 3);
		LCD_voidWriteString("	");
		LCD_voidSetPosition(1, 3);
		LCD_voidWriteNumber(Analog[2]);

		LCD_voidSetPosition(1, 11);
		LCD_voidWriteString("	");
		LCD_voidSetPosition(1, 11);
		LCD_voidWriteNumber(Analog[3]);

		vTaskDelay(100);
	}

}


void ADC_notification(void)
{
	Ch_Num++;
	if(Ch_Num==SENSORS_NUM)
	{
		Ch_Num=0;
	}
	xSemaphoreGive(sem);
}


void SystemInit(void)
{
	LCD_voidInit(); 	/* initialize LCD driver */
	LCD_voidCursorOff();

	ADC_voidInit();		/* initialize ADC driver */
	asm("SEI");

}


