

#include <avr/io.h>
#include "TMU_interface.h"
#include "STD_TYPES.h"
u8 counter=1;

void Task1(void)
{
	PORTC ^= (1<<PC0);
}
void Task2(void)
{
	PORTC ^= (1<<PC1);

}
void Task3(void)
{
	PORTC ^= (1<<PC2);

}
void Task4(void)
{
	PORTC ^= (1<<PC3);

}

int main(void)
{
	DDRC  |= 0X0F;         // Configure the led pin as output pin.
	PORTC &= 0XF0;        // LED is off at the beginning (Positive Logic).
	//SREG  |= (1<<7);           // Enable global interrupts in MC.
	 TMU_CreateTask( Task1,53 ,0 );
	 TMU_CreateTask( Task2,117,1 );
	 TMU_CreateTask( Task3,153,2 );
	 TMU_CreateTask( Task4,216,3 );

	TMU_Init(); // Start the timer.
	TMU_StartScheduler();

}

