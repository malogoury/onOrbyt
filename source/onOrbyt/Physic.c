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

void addBufferPos(Coordonnee* pos, Coordonnee new_pos, int length);

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

void physic_updatePos(Spacecraft* spacecraft)
{
	Coordonnee new_pos = {0,0};
	new_pos.x = (spacecraft->pos[0].x+500)%(NPIX_X*1000);
	new_pos.y = (spacecraft->pos[0].y+500)%(NPIX_Y*1000);
	addBufferPos(spacecraft->pos, new_pos, NB_POS);
}

void addBufferPos(Coordonnee* pos, Coordonnee new_pos, int length)
{
	int i;
	for(i=length-1;i>0; i--)
	{
		pos[i]=pos[i-1];
	}
	pos[0] = new_pos;
}
