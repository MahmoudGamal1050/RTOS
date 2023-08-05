 /***************************************************************
 ******************* LAB1 --> Using FreeRTOS ********************
 ***************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "FreeRTOS.h"
#include "task.h"

void SystemInit(void);

void Task1(void *pv);
void Task2(void *pv);
void Task3(void *pv);
void Task4(void *pv);
int main(void)
{
	SystemInit();

	xTaskCreate(Task1, NULL, 100, NULL, 4, NULL);
	xTaskCreate(Task2, NULL, 100, NULL, 1, NULL);
	xTaskCreate(Task3, NULL, 100, NULL, 1, NULL);
	xTaskCreate(Task4, NULL, 100, NULL, 1, NULL);

	vTaskStartScheduler();

	while(1)
	{

	}

}


void SystemInit(void)
{
	/* Configure PC0:PC2 as output for LEDs*/
	DIO_voidSetPinDirection(DIO_PINC0, DIO_OUTPUT);		
	DIO_voidSetPinDirection(DIO_PINC1, DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PINC2, DIO_OUTPUT);
	/* The LEDs are off at the beginning*/
	DIO_voidSetPinValue(DIO_PINC0, DIO_LOW);
	DIO_voidSetPinValue(DIO_PINC1, DIO_LOW);
	DIO_voidSetPinValue(DIO_PINC2, DIO_LOW);
	/* Configure PC3 as input for the switch 
	   and enable internal pull up resistance */
	DIO_voidSetPinDirection(DIO_PINC3, DIO_INPUT);
	DIO_voidSetPinValue(DIO_PINC3, DIO_HIGH);


}


void Task1(void *pv)
{
	while(1)
	{
		/*Stay at this task as long as the switch is off 
		  because it has the highest priority*/
		/* Check if the switch is pressed*/
		if(!DIO_u8GetPinValue(DIO_PINC3))
		{
			while(!DIO_u8GetPinValue(DIO_PINC3));
			vTaskDelay(200); 	/* Leave this task to toggle the leds */

		}


	}
}

void Task2(void *pv)
{


	while(1)
	{
		/* Toggle LED1 */
		DIO_voidTogglePin(DIO_PINC0);
		vTaskDelay(200);  
	}
}

void Task3(void *pv)
{

	while(1)
	{
		/* Toggle LED2*/
		DIO_voidTogglePin(DIO_PINC1);
		vTaskDelay(200);  

	}
}

void Task4(void *pv)
{

	while(1)
	{		
		/* Toggle LED1 */
		DIO_voidTogglePin(DIO_PINC2);
		vTaskDelay(200);  

	}
}
