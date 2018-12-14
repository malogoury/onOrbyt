/*
 * Game.c
 *
 *  Created on: Dec 9, 2018
 *      Author: nds
 *
 *  Functions for the game phase
 */

#include <stdio.h>
#include "Game.h"

Spacecraft orion;
Planet planets[NB_PLANETS];

void game_init(void)
{
	physic_init(&orion);
	map_init(planets, MAP1);
	printf("planet x = %d, y = %d \n", planets[0].pos.x, planets[0].pos.y);
	graphic_gameInit(planets);
}
void game_update(void)
{
	physic_updatePos(&orion, planets);
}

void game_displayUpdate(void)
{
	graphic_gameUpdate(orion.pos);
}
