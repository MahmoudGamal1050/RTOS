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

static uint16 Digital;
static uint16 Analog;

void SystemInit(void);
void ADC_notification(void);

void LCD_Task(void *pv);
void ADC_Task(void *pv);
void POT_Task(void *pv);

xSemaphoreHandle sem = NULL;


int main(void)
{

	SystemInit();

	xTaskCreate(ADC_Task  , NULL, 100, NULL, 1, NULL);
	xTaskCreate(POT_Task  , NULL, 100, NULL, 2, NULL);
	xTaskCreate(LCD_Task, NULL, 150, NULL, 3, NULL);

	sem = xSemaphoreCreateBinary();
	vTaskStartScheduler();

}


void ADC_Task(void *pv)
{

	while(1)
	{
		ADC_voidStartConversionWithInterrupt(CH_A0);
		ADC_voidSetCallBack(ADC_notification);
		ADC_voidInterruptEnable();

		if(xSemaphoreTake(sem, 2000) == pdPASS)
		{
			Digital = ADC_u16ADCRead();

		}

		vTaskDelay(100);
	}
}


void POT_Task(void *pv)
{
	while(1)
	{
		Analog = (Digital*5000UL)/1023;
		vTaskDelay(100);
	}
}


void LCD_Task(void *pv)
{
	LCD_voidClearScreen();

	LCD_voidSetPosition(0, 0);
	LCD_voidWriteString("POT=");

	LCD_voidSetPosition(0, 10);
	LCD_voidWriteString("mv");

	while(1)
	{
		LCD_voidSetPosition(0, 5);
		LCD_voidWriteString("	");
		LCD_voidSetPosition(0, 5);
		LCD_voidWriteNumber(Analog);

		vTaskDelay(150);
	}

}


void ADC_notification(void)
{

	xSemaphoreGive(sem);
}


void SystemInit(void)
{
	LCD_voidInit(); 	/* initialize LCD driver */
	LCD_voidCursorOff();

	ADC_voidInit();		/* initialize ADC driver */
	asm("SEI");

}


