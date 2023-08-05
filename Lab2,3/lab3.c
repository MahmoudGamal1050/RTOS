/*
 * Exercise2_CTC_Mode.c
 *
 * Created: 1/21/2014 11:29:49 PM
 * Author: Mohamed Tarek
 */

#include <avr/io.h>
#include "TMU_interface.h"
#include "STD_TYPES.h"


int main(void)
{
	DDRC  |= 0X0F;         // Configure the led pin as output pin.
	PORTC &= 0XF0;        // LED is off at the beginning (Positive Logic).
	TMU_Init(); // Start the timer.
	asm("SEI");

    while(1)
    {

    }
}

