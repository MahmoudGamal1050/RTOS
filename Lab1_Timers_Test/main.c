
#include <avr/io.h>
#include "TMU_interface.h"
#include "STD_TYPES.h"


int main(void)
{
	DDRC  |= 0X01;         // Configure pc0 as output pin.
	PORTC &= 0XFE;        // LED is off at the beginning (Positive Logic).
	TMU_Init(); // Start the timer.
	SREG  |= (1<<7);           // Enable global interrupts in MC.

    while(1)
    {

    }
}

