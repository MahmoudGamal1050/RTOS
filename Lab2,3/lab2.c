/*
 * Exercise2_CTC_Mode.c
 *
 * Created: 1/21/2014 11:29:49 PM
 * Author: Mohamed Tarek
 */

#include <avr/io.h>
#include "TMU_interface.h"
#include "STD_TYPES.h"
u8 counter=1;

void lab2(void)
{
	PORTC ^= (1<<PC0);
	if(counter%2==0)
	{
		PORTC ^= (1<<PC1);

	}
	if(counter%3==0)
	{
		PORTC ^= (1<<PC2);

	}
	if(counter%4==0)
	{
		PORTC ^= (1<<PC3);

	}
	counter++;
/* Scheduler */


}
int main(void)
{
	DDRC  |= 0X0F;         // Configure the led pin as output pin.
	PORTC &= 0XF0;        // LED is off at the beginning (Positive Logic).
	TMU_SetCallBack(lab2);
	TMU_Init(); // Start the timer.
	asm("SEI");
    while(1)
    {

    }
}

