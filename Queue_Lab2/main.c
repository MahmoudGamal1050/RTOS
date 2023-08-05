/*********************************************************************************
 ******************* LAB2 Task To ISR Synch. using Semaphore *********************
 ********************************************************************************/


#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "LCD_interface.h"
#include "UART_interface.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

void SystemInit(void);

void LCD_Task(void *pv);
void UART_Task(void *pv);

xQueueHandle buffer = NULL;

int main(void)
{

	SystemInit();

	buffer = xQueueCreate(10,sizeof(uint8));
	xTaskCreate(UART_Task, NULL, 150, NULL, 1, NULL);
	xTaskCreate(LCD_Task, NULL, 150, NULL, 2, NULL);


	vTaskStartScheduler();

}

void SystemInit(void)
{
	LCD_voidInit(); 	/* initialize LCD driver */
	LCD_voidCursorOff();
	UART_voidInit();
	DIO_voidSetPinDirection(DIO_PIND0, DIO_INPUT);
	DIO_voidSetPinDirection(DIO_PINA0, DIO_OUTPUT);


	asm("SEI");

}
void LCD_Task(void *pv)
{
	LCD_voidClearScreen();

	static uint8 Rdata;

	while(1)
	{
		if(xQueueReceive(buffer, &Rdata, portMAX_DELAY)==pdPASS)
		{
			LCD_voidWriteData(Rdata);
			switch(Rdata)
			{
			case 'A':
				DIO_voidSetPinValue(DIO_PINA0, DIO_HIGH);
				break;
			case 'B':
				DIO_voidSetPinValue(DIO_PINA0, DIO_LOW);
				break;
			case 'C':
				LCD_voidClearScreen();
				break;

			}
		}


		vTaskDelay(50);
	}

}

void UART_Task(void *pv)
{
	static uint8 data;
	while(1)
	{
		data = UART_u8ReceiveByte();
		xQueueSend(buffer,&data,portMAX_DELAY);
		vTaskDelay(50);

	}

}







