

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "UART_interface.h"
#include <util/delay.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

xSemaphoreHandle sem = NULL;

void SystemInit(void);
void Button(void *pv);
void Led(void *pv);


int main(void)
{
	SystemInit();
	//sem = xSemaphoreCreateMutex();
	sem = xSemaphoreCreateBinary();
	xTaskCreate(Button, NULL, 150, NULL, 1, NULL);
	xTaskCreate(Led, NULL, 150, NULL, 2, NULL);

	vTaskStartScheduler();


}

void SystemInit(void)
{
	DIO_voidSetPinDirection(DIO_PINC0, DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PINC3, DIO_INPUT );
	DIO_voidSetPinValue(DIO_PINC3, DIO_HIGH);


}


void Button(void *pv)
{
	while(1)
	{
		if(!DIO_u8GetPinValue(DIO_PINC3))
		{
			while(!DIO_u8GetPinValue(DIO_PINC3))
			{
				vTaskDelay(200);

			}
			xSemaphoreGive(sem);
		}
		vTaskDelay(200);
	}
}

void Led(void *pv)
{
	while(1)
	{
		if(xSemaphoreTake(sem,portMAX_DELAY)==pdPASS)
		{
			DIO_voidTogglePin(DIO_PINC0);
		}
	}
}


