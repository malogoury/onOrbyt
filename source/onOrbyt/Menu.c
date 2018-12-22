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

void menu_main(Maps* map);
void menu_init(Maps* map)
{
	graphic_menuInit();
	menu_main(map);
}

void menu_main(Maps* map)
{
	printf("press down to select unique map MAP1\n");
	while(1)
	{
		scanKeys();
		if(keysDown() & KEY_DOWN)
		{
			*map=MAP1;
			break;
		}
		swiWaitForVBlank();
	}
}
