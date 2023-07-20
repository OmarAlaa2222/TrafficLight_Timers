/*
 * main.c
 *
 *  Created on: Jul 14, 2023
 *      Author: Lenovo
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU     8000000UL
#include <util/delay.h>

/* MCAL */
#include "DIO_Interface.h"
#include "Timer_interface.h"
#include "GIE_interface.h"

#include "LCD_Interface.h"
#include "KPD_Interface.h"




void Traffic_Light (void){
	static u16 Local_u16Counter=0;
	static u8 State=0;

	Local_u16Counter++;
	if (Local_u16Counter == 19532){
		Local_u16Counter=0;


		if (State == 0){
			DIO_voidSetPinValue(DIO_u8_PORTD,DIO_u8_PIN1,DIO_u8_LOW);
			DIO_voidSetPinValue(DIO_u8_PORTD,DIO_u8_PIN2,DIO_u8_LOW);
			DIO_voidSetPinValue(DIO_u8_PORTD,DIO_u8_PIN0,DIO_u8_HIGH);


		}
		else if (State == 1){

			DIO_voidSetPinValue(DIO_u8_PORTD,DIO_u8_PIN2,DIO_u8_LOW);
			DIO_voidSetPinValue(DIO_u8_PORTD,DIO_u8_PIN0,DIO_u8_LOW);
			DIO_voidSetPinValue(DIO_u8_PORTD,DIO_u8_PIN1,DIO_u8_HIGH);
			Local_u16Counter=14000;      // To Make it 1 second

		}
		else if (State == 2){

			DIO_voidSetPinValue(DIO_u8_PORTD,DIO_u8_PIN0,DIO_u8_LOW);
			DIO_voidSetPinValue(DIO_u8_PORTD,DIO_u8_PIN1,DIO_u8_LOW);
			DIO_voidSetPinValue(DIO_u8_PORTD,DIO_u8_PIN2,DIO_u8_HIGH);
		}

		if (State <2){
			State++;
		}
		else if (State ==2 ){
			State = 0;
		}




	}





}


void Green_Blink (void){
	static u16 Local_u16Counter=0;
	static u8 Local_u8Flag=0;
	Local_u16Counter++;

	if (Local_u16Counter == 3907){
     TOGGLE_BIT(Local_u8Flag,0);
     DIO_voidSetPinValue(DIO_u8_PORTD,DIO_u8_PIN2,Local_u8Flag);
     Local_u16Counter=0;

	}


}

void STALL(void){
	static u16 Local_u16Counter=0;
	static u8 Local_u8Flag=0;
	DIO_voidSetPortValue(DIO_u8_PORTD,0);





}

void LCD (void){
	LCD_voidGoToPos(0,6);
		LCD_voidSendString("WELCOME");
		LCD_voidGoToPos(1,4);
		LCD_voidSendString("TO TIMERS");

		_delay_ms(3000);
		LCD_voidClearDisplay();

		LCD_voidSendString("OPTION 1");
		LCD_voidGoToPos(1,0);
		LCD_voidSendString("Traffic Light");
		_delay_ms(3000);
		LCD_voidClearDisplay();


		LCD_voidSendString("OPTION 2");
		LCD_voidGoToPos(1,0);
		LCD_voidSendString("Green Blink");
		_delay_ms(3000);
		LCD_voidClearDisplay();

		LCD_voidSendString("FOR RESET");
		LCD_voidGoToPos(1,0);
		LCD_voidSendString("PRESS 0");
		_delay_ms(3000);
		LCD_voidClearDisplay();

		LCD_voidSendString("OPTION1 PRESS 1");
		LCD_voidGoToPos(1,0);
		LCD_voidSendString("OPTION2 PRESS 2");

}

void main (void){
	u8 Reading;

	PORT_voidInit();
	TMRS_voidTMR0Init();
	LCD_voidInit();
	GIE_voidEnable();
	LCD();





	while(1) {
		Reading=KPD_u8GetPressedKey();


		if (Reading !=0xff){
			if (Reading == '4'){
				LCD_voidClearDisplay();
				LCD_voidSendString("TrafficLight");
				LCD_voidGoToPos(1,0);
				LCD_voidSendString("ACTIVATED");
				TMRS_voidTimer0SetCallBack(&Traffic_Light);

				}


			else if (Reading == '7'){


				LCD_voidClearDisplay();
				LCD_voidSendString("GreenBlink");
				LCD_voidGoToPos(1,0);
				LCD_voidSendString("ACTIVATED");
				TMRS_voidTimer0SetCallBack(&Green_Blink);

				}

		 else if (Reading == 'A'){

				LCD_voidClearDisplay();
				LCD_voidSendString("OPTION1 PRESS 1");
				LCD_voidGoToPos(1,0);
				LCD_voidSendString("OPTION2 PRESS 2");
				TMRS_voidTimer0SetCallBack(&STALL);






			}
		}

		}
}













