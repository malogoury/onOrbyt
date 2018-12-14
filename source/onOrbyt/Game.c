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
#include "Physic.h"

Spacecraft orion;
Planet planets[NB_PLANETS];

void game_init(void)
{
	physic_init(&orion);
	//map_init(planets);
}
void game_update(void)
{
	physic_updatePos(&orion, planets);
	// TO DO: call graphics
}
