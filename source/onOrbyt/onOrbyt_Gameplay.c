/*
 * onOrbyt_Gameplay.c
 *
 *  Created on: Dec 9, 2018
 *      Author: nds
 *
 *  FSM controlling the different phases of the game
 *
 */

#include <stdio.h>
#include <nds.h>
#include "onOrbyt_Gameplay.h"

void ISR_VBLANK();
FSM state=IDLE;

void gameplay_main()
{
	if(state==MENU)
	{
		menu_init();
		state = GAME;
	}
	if (state==GAME) game_init();
}

void gameplay_init(void)
{
	irqSet(IRQ_VBLANK,&ISR_VBLANK);
	irqEnable(IRQ_VBLANK);
	state = MENU;
	gameplay_main();
}

void gameplay_update(void)
{
	if(state==MENU);
	else if (state == GAME);
		game_update();
}

void gameplay_displayUpdate(void)
{
	if(state==GAME);
		game_displayUpdate();
}

void ISR_VBLANK()
{
	gameplay_displayUpdate();
}
