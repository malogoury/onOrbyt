/*
 * Physic.c
 *
 *  Created on: Dec 9, 2018
 *      Author: nds
 *
 *  Equation and constant to run the simulation
 */

#include <stdio.h>
#include <stdlib.h>
#include "Physic.h"



void physic_init(Spacecraft* spacecraft)
{
	int i=0;
	for(i=0;i<NB_POS;i++)
	{
		spacecraft->pos[i].x = X_INIT;
		spacecraft->pos[i].y = Y_INIT;
	}
	spacecraft->speed.x = 0;
	spacecraft->speed.y = 0;
}

void physic_updatePos(void)
{

}
