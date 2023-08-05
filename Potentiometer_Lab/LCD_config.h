/*****************************************************************************/
/* Title        	: 	LCD Driver									         */
/* File Name    	: 	LCD_config.h                                         */
/* Author       	: 	Fahd Badi                                            */
/* Version      	: 	1.0.0                                                */
/* Origin Date  	: 	16/10/2020                                           */
/* Notes        	: 	None                                                 */
/*****************************************************************************/

/******************************************************************************
* Description 	: Guard to protect this File from include more 			      *
*                 than one time.                               	 	 		  *
******************************************************************************/

#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H

/******************************************************************************
* !comment : LCD Select Mode Options.  			         	                  *
*            MODE_4_BIT                                                       *
*            MODE_8_BIT                                                       *
******************************************************************************/
#define  LCD_MODE    MODE_8_BIT

/******************************************************************************
* !comment : LCD PINs Definition, Select PINs Options:   			          *
* 		   	 DIO_PINA0 - DIO_PINA7                                            *
* 		   	 DIO_PINB0 - DIO_PINB7                                            *
* 		   	 DIO_PINC0 - DIO_PINC7                                            *
* 		   	 DIO_PIND0 - DIO_PIND7                                            *
******************************************************************************/
#if (LCD_MODE == MODE_8_BIT)
#define LCD_D0_PIN       DIO_PINC0
#define LCD_D1_PIN       DIO_PINC1
#define LCD_D2_PIN       DIO_PINC2
#define LCD_D3_PIN       DIO_PINC3
#define LCD_D4_PIN       DIO_PINC4
#define LCD_D5_PIN       DIO_PINC5
#define LCD_D6_PIN       DIO_PINC6
#define LCD_D7_PIN       DIO_PINC7

#elif (LCD_MODE == MODE_4_BIT)
#define LCD_D4_PIN       DIO_PINC3
#define LCD_D5_PIN       DIO_PINC2
#define LCD_D6_PIN       DIO_PINC1
#define LCD_D7_PIN       DIO_PINC0

#endif

/* LCD Control Pins */
#define LCD_RS_PIN	    DIO_PIND4
#define LCD_RW_PIN      DIO_PIND5
#define LCD_EN_PIN      DIO_PIND6




#endif 
/*** !comment : End of gaurd [LCD_CONFIG_H] **********************************/
