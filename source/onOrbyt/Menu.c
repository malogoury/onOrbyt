/*
 * Menu.c
 *
 *  Created on: Dec 9, 2018
 *      Author: nds
 *
 *  Functions for the menu phase of the game
 */

#include <nds.h>
#include <stdio.h>
#include "Menu.h"

FSM_menu state_menu = IDLE_menu;

void menu_main(Maps* map);
void menu_init(Maps* map)
{
	graphic_menuInit();
	sound_initMenu();
	state_menu=INIT_menu;
	menu_main(map);
}

void menu_main(Maps* map)
{
	while(1)
	{
		scanKeys();
		if(keysDown() & KEY_DOWN && state_menu==SELECT_menu)
		{
			*map=MAP4;
			break;
		}
		else if(keysDown() & KEY_RIGHT && state_menu==SELECT_menu)
		{
			*map=MAP2;
			break;
		}
		else if(keysDown() & KEY_LEFT && state_menu==SELECT_menu)
		{
			*map=MAP3;
			break;
		}
		else if(keysDown() & KEY_UP && state_menu==SELECT_menu)
		{
			*map=MAP1;
			break;
		}
		state_menu=SELECT_menu;
		swiWaitForVBlank();
	}
}
