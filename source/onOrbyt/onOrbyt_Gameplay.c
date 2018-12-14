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
#include "onOrbyt_Gameplay.h"

void gameplay_init(void)
{
	game_init();
}

void gameplay_update(void)
{
	static unsigned long time=0;
	game_update();
	time++;
}

void gameplay_displayUpdate(void)
{
	game_displayUpdate();
}
