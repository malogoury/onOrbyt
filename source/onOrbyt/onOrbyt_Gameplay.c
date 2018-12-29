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

FSM state=IDLE;

void gameplay_main()
{
	Maps map=MAP1;
	if(state==MENU)
	{
		menu_init(&map);
		state = GAME;
	}
	if (state==GAME) game_init(map);
}

void gameplay_init(void)
{
	state = MENU;
	gameplay_main();
}

void gameplay_update(void)
{
	if(state==MENU);
	else if (state == GAME)
	{
		game_update();
	}
}

void gameplay_displayUpdate(void)
{
	if(state==GAME);
		game_displayUpdate();
}
