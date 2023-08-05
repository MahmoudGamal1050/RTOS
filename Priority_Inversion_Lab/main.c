

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "UART_interface.h"
#include <util/delay.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

xSemaphoreHandle sem;
TaskHandle_t xHandle;
void SystemInit(void);
void LPT(void *pv);
void MPT(void *pv);
void HPT(void *pv);

int main(void)
{
	SystemInit();
	sem = xSemaphoreCreateMutex();
	//vSemaphoreCreateBinary(sem);

	xTaskCreate(LPT, NULL, 150, NULL, 1, &xHandle);
	vTaskStartScheduler();

	while(1)
	{

	}

}

void SystemInit(void)
{
	DIO_voidSetPinDirection(DIO_PIND0, DIO_INPUT );
	DIO_voidSetPinDirection(DIO_PIND1, DIO_OUTPUT);

	UART_voidInit();
	//UART_voidSendStringBlocking("System Started\r\n");
}


void LPT(void *pv)
{
	UART_voidSendStringBlocking("LPT Started\r\n");

	UART_voidSendStringBlocking("LPT priority before HPT created: ");
	UART_voidWriteDecimalNumber(uxTaskPriorityGet(xHandle));

	if(xSemaphoreTake(sem,portMAX_DELAY)==pdPASS)
	{
		UART_voidSendStringBlocking("\r\nLPT took semaphore\r\n");
		xTaskCreate(HPT, NULL, 150, NULL, 3, NULL);

		xTaskCreate(MPT, NULL, 150, NULL, 2, NULL);
		UART_voidSendStringBlocking("LPT priority after MPT created: ");
		UART_voidWriteDecimalNumber(uxTaskPriorityGet(xHandle));
		UART_voidSendStringBlocking("\r\n");

		UART_voidSendStringBlocking("LPT Running\r\n");

		UART_voidSendStringBlocking("LPT gave semaphore\r\n");
		xSemaphoreGive(sem);


	}
	vTaskDelay(1000);  //1 Sec



	while(1)
	{



	}
}

void MPT(void *pv)
{
	//UART_voidSendStringBlocking("MPT Started\r\n");
	UART_voidSendStringBlocking("MPT waiting \r\n");
	_delay_ms(1000);
	//UART_voidSendStringBlocking("MPT waiting \r\n");

	vTaskDelay(1000);  //1 Sec

	while(1)
	{
	}
}

void HPT(void *pv)
{
	//UART_voidSendStringBlocking("HPT Started\r\n");
	if(xSemaphoreTake(sem,portMAX_DELAY)==pdPASS)
	{
		UART_voidSendStringBlocking("HPT Running\r\n");
		UART_voidSendStringBlocking("LPT priority after HPT took semaphore: ");
		UART_voidWriteDecimalNumber(uxTaskPriorityGet(xHandle));
		UART_voidSendStringBlocking("\r\n");

		xSemaphoreGive(sem);

		//vTaskDelay(1000);  //1 Sec

	}




	while(1)
	{


	}
}

