/*
 * Timer_Register.h
 *
 *  Created on: Jul 14, 2023
 *      Author: Lenovo
 */

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

// TMR0 registers


#define TMRS_u8_TCCR0_REG *((volatile u8 *)0x53)
#define TMRS_u8_TCNT0_REG *((volatile u8 *)0x52)
#define TMRS_u8_TIMSK_REG *((volatile u8 *)0x59)
#define TMRS_u8_TIFR_REG *((volatile u8 *)0x58)
#define TMRS_u8_OCR0_REG *((volatile u8 *)0x5C)

//TMR0 Pins


//TCCR0 Pins
#define TMRS_u8_FOCO_PIN    7
#define TMRS_u8_WGM00_PIN   6
#define TMRS_u8_WGM01_PIN   3
#define TMRS_u8_COMM01_PIN  5
#define TMRS_u8_COMM00_PIN  4
#define TMRS_u8_CS02_PIN    2
#define TMRS_u8_CS01_PIN    1
#define TMRS_u8_CS00_PIN    0

//-------------------------------------------------------------------

//TIMSK PINS

#define TMRS_u8_OCIE0_PIN    1
#define TMRS_u8_TOIE0_PIN    0




/* TMR1 */
//TMR1 Registers

#define TMRS_u8_TCCR1A_REG       *((volatile u8 *)(0x4F))
#define TMRS_u8_TCCR1B_REG        *((volatile u8 *)(0x4E))
#define TMRS_u8_TCNT1H_REG        *((volatile u8 *)(0x4D))
#define TMRS_u8_TCNT1L_REG        *((volatile u8 *)(0x4C))
#define TMRS_u16_TCNT1_REG         *((volatile u16 *)(0x4C))
#define TMRS_u8_ICR1H_REG        *((volatile u8 *)(0x47))
#define TMRS_u8_ICR1L_REG        *((volatile u8 *)(0x46))
#define TMRS_u16_ICR1_REG        *((volatile u16 *)(0x46))

#define TMRS_u8_OCR1AL_REG        *((volatile u8 *)(0x4A))
#define TMRS_u8_OCR1AH_REG        *((volatile u8 *)(0x4B))
#define TMRS_u16_OCR1A_REG        *((volatile u16 *)(0x4A))

#define TMRS_u8_OCR1BL_REG        *((volatile u8 *)(0x48))
#define TMRS_u8_OCR1BH_REG        *((volatile u8 *)(0x49))
#define TMRS_u16_OCR1B_REG        *((volatile u16 *)(0x48))   //The pointer that will read/write the value of OBR1B as a whole >> OCR1AH concat with OCR1AL






#endif /* TIMER_REGISTER_H_ */
