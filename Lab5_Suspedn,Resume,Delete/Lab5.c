

#include <avr/io.h>
#include "TMU_interface.h"
#include "STD_TYPES.h"

void Task0(void);
void Task1(void);
void Task2(void);
void Task3(void);



int main(void)
{
	DDRC  |= 0X0F;         // Configure the led pin as output pin.
	PORTC &= 0XF0;        // LED is off at the beginning (Positive Logic).
	TMU_CreateTask( Task0,53 ,0,0 );
	TMU_CreateTask( Task1,117,1,0 );
	TMU_CreateTask( Task2,153,2,0 );
	TMU_CreateTask( Task3,216,3,0);

	TMU_Init(); // Start the timer.
	TMU_StartScheduler();

}


void Task0(void)
{
	PORTC ^= (1<<PC0);
	static u8 i;
	i++;
	if((i==12))
	{
		TMU_DeleteTask(2);
		TMU_DeleteTask(3);


	}
}
void Task1(void)
{
	PORTC ^= (1<<PC1);
	static u8 i;
	i++;
	if((i==12))
	{
		 TMU_CreateTask( Task2,153,2,0);

	}


}
void Task2(void )
{
	PORTC ^= (1<<PC2);


}
void Task3(void )
{
	PORTC ^= (1<<PC3);

}
