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

void game_update(void)
{
	physic_updatePos();
}
