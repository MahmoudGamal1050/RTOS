

#ifndef TMU_PRIVATE_H
#define TMU_PRIVATE_H

#define  CH0   1
#define  CH1   2
#define  CH2   3




/* Timer0 Registers*/
#define  OCR0      *((volatile u8*) 0x5C)
#define  TIMSK     *((volatile u8*) 0x59)
#define  TIFR      *((volatile u8*) 0x58)
#define  TCCR0     *((volatile u8*) 0x53)
#define  TCNT0     *((volatile u8*) 0x52)

/* Timer1 Registers*/
#define  PORTC     *((volatile u8*) 0x35)

#define  TCCR1A    *((volatile u8*) 0x4F)
#define  TCCR1B    *((volatile u8*) 0x4E)
#define  TCNT1H    *((volatile u8*) 0x4D)
#define  TCNT1L    *((volatile u8*) 0x4C)
#define  OCR1AH    *((volatile u8*) 0x4B)
#define  OCR1AL    *((volatile u8*) 0x4A)
#define  OCR1BH    *((volatile u8*) 0x49)
#define  OCR1BL    *((volatile u8*) 0x48)
#define  ICR1H     *((volatile u8*) 0x47)
#define  ICR1L     *((volatile u8*) 0x46)

/* Timer2 Registers*/
#define  TCCR2     *((volatile u8*) 0x45)
#define  TCNT2     *((volatile u8*) 0x44)
#define  OCR2      *((volatile u8*) 0x43)

#endif 
