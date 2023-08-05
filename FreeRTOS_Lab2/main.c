 /***************************************************************
 ******************* LAB1 --> Using FreeRTOS ********************
 ***************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"

uint8 SevenSeg;
uint8 UpFlag;
uint8 DownFlag;


void SystemInit(void);

void Task1(void *pv);
void Task2(void *pv);
void Task3(void *pv);
void Task4(void *pv);



int main(void)
{
	SystemInit();

	xTaskCreate(Task1, NULL, 100, NULL, 4, NULL);
	xTaskCreate(Task2, NULL, 100, NULL, 4, NULL);
	xTaskCreate(Task3, NULL, 100, NULL, 4, NULL);
	xTaskCreate(Task4, NULL, 100, NULL, 4, NULL);




	vTaskStartScheduler();

	while(1)
	{

	}

}


void SystemInit(void)
{
	/* Configure PC0:PC3 as output for the seven segment*/
	DIO_voidSetPortDirection(DIO_PORTC, DIO_PORT_HIGH);
	/* Seven Segment is zero at the beginning */
	DIO_voidSetPortValue(DIO_PORTC, 0X00);

	/* Configure PA0,PA1 as output for the Switches*/
	DIO_voidSetPinDirection(DIO_PINA0, DIO_INPUT);
	DIO_voidSetPinDirection(DIO_PINA1, DIO_INPUT);
	/* Enable internal pull up resistors*/
	DIO_voidSetPinValue(DIO_PINA0, DIO_HIGH);
	DIO_voidSetPinValue(DIO_PINA1, DIO_HIGH);

}

/* This task checks if the up switch is pressed*/
void Task1(void *pv)
{
	while(1)
	{
		if(!DIO_u8GetPinValue(DIO_PINA0))
		{
			UpFlag =1;
			while(!DIO_u8GetPinValue(DIO_PINA0));

		}
		vTaskDelay(200);

	}
}

/* This task checks if the down switch is pressed*/
void Task2(void *pv)
{
	while(1)
	{
		if(!DIO_u8GetPinValue(DIO_PINA1))
		{
			DownFlag = 1;
			while(!DIO_u8GetPinValue(DIO_PINA1));

		}
		vTaskDelay(200);

	}
}

/* This task increases the seven segment */
void Task3(void *pv)
{


	while(1)
	{
		if(UpFlag==1)
		{
			if(SevenSeg!=9)
			{
				SevenSeg++;
			}
			else
			{
				SevenSeg=0;
			}

			DIO_voidSetPortValue(DIO_PORTC, SevenSeg);
		}
		UpFlag=0;
		vTaskDelay(200);
	}
}

/* This task decreases the seven segment */
void Task4(void *pv)
{


	while(1)
	{
		if(DownFlag==1)
		{
			if(SevenSeg!=0)
			{
				SevenSeg--;
			}
			else
			{
				SevenSeg=9;
			}

			DIO_voidSetPortValue(DIO_PORTC, SevenSeg);
		}
		DownFlag=0;
		vTaskDelay(200);
	}
}

