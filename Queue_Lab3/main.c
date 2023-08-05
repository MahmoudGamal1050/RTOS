/*********************************************************************************
 ******************* LAB2 Task To ISR Synch. using Semaphore *********************
 ********************************************************************************/


#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "UART_interface.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

void SystemInit(void);

void Send_Task(void *pv);
void UART_Task(void *pv);

xQueueHandle buffer = NULL;

int main(void)
{

	SystemInit();

	buffer = xQueueCreate(5,12*sizeof(uint8));
	xTaskCreate(UART_Task, NULL, 150, NULL, 1, NULL);
	xTaskCreate(Send_Task, NULL, 150, NULL, 2, NULL);


	vTaskStartScheduler();

}

void SystemInit(void)
{

	UART_voidInit();
	DIO_voidSetPinDirection(DIO_PIND1, DIO_OUTPUT);


	asm("SEI");

}
void Send_Task(void *pv)
{

	static uint8 Sdata[][12]={"Mahmoud\r\n" ,"Ahmed\r\n","Ali\r\n",
			"Sayed\r\n","Khaled\r\n"};
	static uint8 counter=0;
	while(1)
	{

		xQueueSend(buffer,&Sdata[counter],portMAX_DELAY);

		counter++;
		if(counter==5)
			counter=0;

		vTaskDelay(500);
	}

}

void UART_Task(void *pv)
{
	static uint8 Rdata[12];
	while(1)
	{
		if(xQueueReceive(buffer, &Rdata, portMAX_DELAY)==pdPASS)
		{
			UART_voidSendStringBlocking(Rdata);

		}
		vTaskDelay(500);

	}

}







