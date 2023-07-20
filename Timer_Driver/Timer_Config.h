/*
 * Timer_Config.h
 *
 *  Created on: Jul 14, 2023
 *      Author: Lenovo
 */

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_
// TIMER 0
// Timer Mode
// NORMAL -- CTC -- FAST_PWM -- PWM_PHASE

#define TMR_MODE NORMAL

// Timer Action
// if CTC Normal -- Toggle -- Set - Clear
// if Fast PWM  Normal -- Inverting -- Non Inverting
// if Phase PWM Normal -- Inverting -- Non Inverting

#define TMR_ACTION CLEAR

// CLOCK PRE SCALAR No Clk Source - No div - Div by 8 ,64 ,265 ,1024 - Counter Fall / Rise

#define CLK_PreScalar DIV_BY_8


#define PRELOAD_VALUE 192

// TIMER 1


//TIMER CHANNEL A - B

#define CHANNEL



// Timer Mode
// NORMAL -- CTC -- FAST_PWM -- PWM_PHASE

#define TMR_MODE NORMAL

#endif /* TIMER_CONFIG_H_ */
