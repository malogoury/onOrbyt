/*
 * LL_Timer.c
 *
 *  Created on: Dec 9, 2018
 *      Author: nds
 *
 *  Low level functions to handle timer interrupt
 */

#include <nds.h>
#include "LL_Timer.h"

void ISR_TIMER0()
{
	gameplay_update();
}



void timer_init(void)
{
	//Configure the timer0 for 10ms interrupt
	TIMER_DATA(0) = TIMER_FREQ_1024(100);
	TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	irqSet(IRQ_TIMER0, &ISR_TIMER0);
	irqEnable(IRQ_TIMER0);
}


void timer_sound(void)
{
	TIMER_DATA(1) = TIMER_FREQ_1024(1);
	TIMER1_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
	irqSet(IRQ_TIMER1, &ISR_TIMER0);
	irqEnable(IRQ_TIMER0);

}

