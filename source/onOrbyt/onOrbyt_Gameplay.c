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

/**
 * stay in menu until map is selected
 */
void gameplay_main()
{
	Maps map=MAP1;
	if(state==MENU)
	{
		menu_init(&map);
		state = GAME;
	}
	if (state==GAME) game_init(map);
	// return from game_init in case of a reset to come back to the menu
}

/**
 * start the gameplay with menu
 */
void gameplay_init(void)
{
	state = MENU;
	gameplay_main();
}

/**
 * called every 10ms by the timer ISR
 * used only in the game state for physics' update
 */
void gameplay_update(void)
{
	if(state==MENU);
	else if (state == GAME)
		game_update();
}
