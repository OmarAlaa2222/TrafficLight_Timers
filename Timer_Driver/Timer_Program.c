/*
 * Timer_Program.c
 *
 *  Created on: Jul 14, 2023
 *      Author: Lenovo
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU     8000000UL
#include <util/delay.h>
#include "Timer_Config.h"
#include "Timer_Interface.h"
#include "Timer_Private.h"
#include "Timer_Register.h"


static void(*TMRS_pfTimer0OVF)(void)= NULL ;
static void(*TMRS_pfTimer0CTC)(void)= NULL ;

void TMRS_voidTMR0Init(void){

#if TMR_MODE == NORMAL

	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_WGM00_PIN);
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_WGM01_PIN);

	TMRS_u8_TCNT0_REG=PRELOAD_VALUE;

	SET_BIT(TMRS_u8_TIMSK_REG,TMRS_u8_TOIE0_PIN);


#elif TMR_MODE == PWM_PHASE

#if TMR_ACTION == NORMAL_1

	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM01_PIN);
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM00_PIN);

#elif TMR_ACTION == NON_INVERTING

	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM01_PIN);
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM00_PIN);

#elif TMR_ACTION == INVERTING
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM01_PIN);
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM00_PIN);

#endif


	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_WGM00_PIN);
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_WGM01_PIN);



#elif TMR_MODE == CTC

#if TMR_ACTION == NORMAL_1

	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM01_PIN);
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM00_PIN);

#elif TMR_ACTION == TOGGLE
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM01_PIN);
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM00_PIN);

#elif TMR_ACTION == CLEAR

	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM01_PIN);
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM00_PIN);

#elif TMR_ACTION == SET
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM01_PIN);
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM00_PIN);

#endif

	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_WGM00_PIN);
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_WGM01_PIN);

	SET_BIT(TMRS_u8_TIMSK_REG,TMRS_u8_OCIE0_PIN);

#elif TMR_MODE == FAST_PWM

#if TMR_ACTION == NORMAL_1

	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM01_PIN);
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM00_PIN);

#elif TMR_ACTION == NON_INVERTING

	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM01_PIN);
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM00_PIN);

#elif TMR_ACTION == INVERTING
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM01_PIN);
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_COMM00_PIN);

#endif

	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_WGM00_PIN);
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_WGM01_PIN);

#endif

#if CLK_PreScalar == NO_CLK_SOURCE

	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS02_PIN);
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS01_PIN);
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS00_PIN);

#elif CLK_PreScalar == NO_DIV

	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS02_PIN);
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS01_PIN);
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS00_PIN);


#elif CLK_PreScalar == DIV_BY_8

	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS02_PIN);
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS01_PIN);
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS00_PIN);

#elif CLK_PreScalar == DIV_BY_64

	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS02_PIN);
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS01_PIN);
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS00_PIN);


#elif CLK_PreScalar == DIV_BY_256

	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS02_PIN);
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS01_PIN);
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS00_PIN);

#elif CLK_PreScalar == DIV_BY_1024

	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS02_PIN);
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS01_PIN);
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS00_PIN);

#elif CLK_PreScalar == COUNTER_FALL

	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS02_PIN);
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS01_PIN);
	CLR_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS00_PIN);

#elif CLK_PreScalar == COUNTER_RISE

	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS02_PIN);
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS01_PIN);
	SET_BIT(TMRS_u8_TCCR0_REG,TMRS_u8_CS00_PIN);

#endif



}



void TMRS_voidTimer0SetCompareMatchValue(u8 Copy_u8_Value){

	TMRS_u8_OCR0_REG=Copy_u8_Value;
}

void TMRS_voidTimer0SetCallBack(void (*Copy_pf) (void)){

	if (Copy_pf != NULL ){
		TMRS_pfTimer0OVF=Copy_pf;
	}

}


#if TMR_MODE == NORMAL

void __vector_11(void) __attribute__((signal));

void __vector_11(void) {

	if (TMRS_pfTimer0OVF != NULL){
		TMRS_pfTimer0OVF();
	}
}



/*void __vector_11(void) __attribute__((signal));

void __vector_11(void) {




static u16 Local_u16CounterTMR0_OVF = 0;
Local_u16CounterTMR0_OVF++ ;

if( Local_u16CounterTMR0_OVF == 19532 )          // INCASE OF 5 SECONDS   EQUALS 19531.25  PRELOAD VALUE == 192
{
                                                 // INCASE 1 SECONDS EQUALS 3906.25     PRELOAD VALUE == 192
	TMRS_u8_TCNT0_REG=PRELOAD_VALUE;
	Local_u16CounterTMR0_OVF = 0;
	TMRS_pfTimer0OVF();
}
} */


#elif TMR_MODE == CTC

void __vector_10(void) __attribute__((signal));

void __vector_10(void)

if (TMRS_pfTimer0OVF != NULL){
	TMRS_pfTimer0OVF();
}
}


/*{

static u16 Local_u16CounterTMR0_CTC = 0;
Local_u16CounterTMR0_CTC++ ;


if( Local_u16CounterTMR0_CTC == 10000 )    // 10 000 CTC Interrupts is 100*(1us) * 10k = 1s   OSCR 100              COMP MATCH COUNT=1*10^(6)/100 == 10000
{
	Local_u16CounterTMR0_CTC = 0;
	TMRS_pfTimer0OVF();
}
}
*/
#endif



void TMRS_voidTMR1Init(void){
//FAST PWM Mode, Mode 14:
	SET_BIT(TMRS_u8_TCCR1A_REG,1);
	CLR_BIT(TMRS_u8_TCCR1A_REG,0);

	SET_BIT(TMRS_u8_TCCR1B_REG,4);
	SET_BIT(TMRS_u8_TCCR1B_REG,3);


    //Selecting the action to be done on HW  pin in case of compare match
	//In case of Fast PWM:


	CLR_BIT(TMRS_u8_TCCR1A_REG, 6);
	SET_BIT(TMRS_u8_TCCR1A_REG, 7);  //SET OC1A @TOP, clear it on @CM




	//Prescaler

    CLR_BIT(TMRS_u8_TCCR1B_REG,2);
    SET_BIT(TMRS_u8_TCCR1B_REG,1);
    CLR_BIT(TMRS_u8_TCCR1B_REG,0); //Here we selected p.s of 8, our clk = 8MHz
}

void TMRS_voidTimer1SetCompareMatchValue(u16 Copy_u8OCR1Value) {

	TMRS_u16_OCR1A_REG = Copy_u8OCR1Value;
}

void TMRS_voidTimer1SetOverflowValue(u16 Copy_u8ICR1Value) {

TMRS_u16_ICR1_REG = Copy_u8ICR1Value ;

}



void ServoSwing (u8 Copy_u8ServoAngle) {

     switch(Copy_u8ServoAngle) {

     case 0:

	TMRS_u16_OCR1A_REG = 999;
     _delay_ms(500);  break;

     case 90:

	TMRS_u16_OCR1A_REG = 1499;
     _delay_ms(500); break;

     case 180:

	TMRS_u16_OCR1A_REG = 1999;
     _delay_ms(500); break;

     default: break;

     }


}

