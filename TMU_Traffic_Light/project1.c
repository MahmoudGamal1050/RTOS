/*
 * Project1.c
 *
 * Created: 1/21/2023 11:29:49 PM
 * Author: Mahmoud G
 */

#include <avr/io.h>
#include "TMU_interface.h"
#include "STD_TYPES.h"

/* Tasks Prototypes*/
void Task1(void);
void Task2(void);
void Task3(void);
void Task4(void);
void Task5(void);


u8 HighestCountFirstDigit=0X5;
u8 HighestCountSecondDigit=0X1;

u8 CounterFirstDigit=0X5;
u8 CounterSecondDigit=0X1;



int main(void)
{
	DDRC  = 0XFF;       	   // Configure SevenSeg port as output .
	DDRD  = 0XFF;       	   // Another sevenSeg to display highest count .
	PORTC = 0X15; 			  // initialize both seven segments with 15
	PORTD = 0X15;

	DDRA  = 0X07;       	   /* Configure the leds PA0:PA2 as outputs
							     and PA4,PA5 as input for switches*/
	PORTA = 0X31;      	       /*  enable internal pull up for switches*/
	/* The osTick is 100ms*/
	 TMU_CreateTask( Task1,10 ,0 );	/*Seven Segment decrement every 1s*/
	 TMU_CreateTask( Task2,10,1 ); /*Green Led Toggle every 15s*/
	 TMU_CreateTask( Task3,10 ,2 ); /*Yellow Led off for  12s then on for 3s*/
	 TMU_CreateTask( Task4,10,3 ); /*Red Led Toggle every 15s*/
	 TMU_CreateTask( Task5,2  ,4 );    /*Check if Button is pressed*/




	TMU_Init(); // Start the timer.
	TMU_StartScheduler(); //Start the scheduler
	while(1)
	{

	}

}



/*Seven Segment decrement every 1s*/
void Task1(void)
{
	CounterFirstDigit--;
	PORTC = (CounterSecondDigit<<4)|CounterFirstDigit;

	if((CounterSecondDigit==0)&&(CounterFirstDigit==1))
	{
		CounterFirstDigit = HighestCountFirstDigit+1;
		CounterSecondDigit = HighestCountSecondDigit;

	}

	if(CounterFirstDigit== 0)
	{
		CounterFirstDigit= 0x0A;
		CounterSecondDigit--;
	}

}

/*Green Led Toggle every 15s*/
void Task2(void)
{
	if((CounterFirstDigit==HighestCountFirstDigit)&&
	   (CounterSecondDigit==HighestCountSecondDigit))

		PORTA ^= (1<<PA0);
}

/*Yellow Led off for  12s then on for 3s*/
void Task3(void)
{
	 u8 temp1 = (CounterSecondDigit<<4)|CounterFirstDigit;
	 u8 temp2 = (HighestCountSecondDigit<<4)|HighestCountFirstDigit;

	if((temp1<=3)||(temp1==temp2+1))
	{
		PORTA |= (1<<PA1);

	}
	else
	{
		PORTA &= ~(1<<PA1);
	}

}
/*Red Led Toggle every 15s*/
void Task4(void)
{
	if((CounterFirstDigit==HighestCountFirstDigit)&&
	   (CounterSecondDigit==HighestCountSecondDigit))

		PORTA ^= (1<<PA2);
}

void Task5(void)
{
	if(!(PINA & 0X10))
	{
		if(HighestCountFirstDigit!=9)
		{
			HighestCountFirstDigit++;
		}
		else
		{
			HighestCountFirstDigit=0;
			HighestCountSecondDigit++;
		}
	}
	if(!(PINA & 0X20))
	{
		if(HighestCountFirstDigit!=0)
		{
			HighestCountFirstDigit--;

		}
		else
		{
			HighestCountFirstDigit=9;
			HighestCountSecondDigit--;
		}
	}
	PORTD = (HighestCountSecondDigit<<4)|HighestCountFirstDigit;
}


