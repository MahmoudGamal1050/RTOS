

#include "TMU_config.h"
#include "TMU_private.h"
#include "TMU_interface.h"
#include "avr/io.h"


static u8 Num_ISR;
static u8 Count_ISR;


void TMU_Init(void)
{
	#if TIM_CH == CH0

		TCCR0 = 0x0D;
		TIMSK |= (1<<1);

		#if OS_TICK <= 16 && OS_TICK > 0

			OCR0 = (OS_TICK * F_cpu)/(1024000);
			Num_ISR = 1;
			Count_ISR = Num_ISR;

		#elif OS_TICK > 16

			u8 max;
			for(u8 i=1; i<=16; i++)
			{
				if(OS_TICK%i == 0)
				{
					max = i;
				}
			}

			OCR0 = (max * F_cpu)/(1024000ul);
			Num_ISR = (OS_TICK / max);
			Count_ISR = Num_ISR;

		#else
			#error "your os tick exceed ( ) msec"
		#endif


	#elif TIM_CH == CH1

		TCCR1A = 0x00;
		TCCR1B = 0x0D;
		TIMSK |= (1<<4);

		#if OS_TICK <= 4194 &&OS_TICK>0
			u16 counts =(OS_TICK * F_cpu)/(1024000ul);
			OCR1AH = (u8)(counts>>8);
			OCR1AL = (u8)(counts);
			Num_ISR = 1;
			Count_ISR = Num_ISR;
		#else
			#error "your os tick exceed ( 4194) msec"
		#endif

	#elif TIM_CH == CH2

		TCCR2 = 0x0F;
		TIMSK |= (1<<7);

		#if OS_TICK <= 16 && OS_TICK > 0

			OCR2 = (OS_TICK * F_cpu)/(1024000ul);
			Num_ISR = 1;
			Count_ISR = Num_ISR;

		#elif OS_TICK > 16 /// 1 2 3 ....16 ---- 28 14 7 2

			u8 max; //28
			for(u8 i=1; i<=16; i++)
			{
				if(OS_TICK%i == 0)
				{
					max = i;
				}
			}

			OCR2 = (max * F_cpu)/(1024000ul);
			Num_ISR = (OS_TICK / max);
			Count_ISR = Num_ISR;

		#else
			#error "your os tick exceed ( ) msec"
		#endif


	#else
		#error "selection of timer channel is wrong"
	#endif
}



/*   ISRs   */
#if TIM_CH == CH0
/* timer0 ISR*/

void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	Count_ISR --;

	if(Count_ISR == 0)
	{

		PORTC ^= (1<<PC0);
		Count_ISR = Num_ISR;
	}

}

#elif TIM_CH == CH1
/* timer1 ISR*/
void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
	Count_ISR --;

	if(Count_ISR == 0)
	{
		PORTC ^= (1<<PC0);
		Count_ISR = Num_ISR;
	}


}

#elif TIM_CH == CH2
/* timer2 ISR*/
void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
	Count_ISR --;
	if(Count_ISR == 0)
	{
		PORTC ^= (1<<PC0);
		Count_ISR = Num_ISR;
	}


}

#else
	#error "selection of timer channel is wrong"
#endif
