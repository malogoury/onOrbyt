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
#include "onOrbyt_defines.h"

typedef struct Coordonnees Coordonnee;
struct Coordonnees
{
	int x,y;
};

typedef struct Spacecrafts Spacecraft;
struct Spacecrafts
{
	Coordonnee pos[NB_POS];			// mpix
	Coordonnee speed;				// mpix/ms
};

Spacecraft dragon;

void physic_updatePos(void)
{
	dragon.speed.x = 0;
	dragon.speed.y = 4;
	int i;
	for(i=0;i<NB_POS;i++)
	{
		dragon.pos[i].x = i;
		dragon.pos[i].y = i;
		printf("pos x = %d and pos y = %d \n", dragon.pos[i].x, dragon.pos[i].y);
	}

	printf("speed x = %d and speed y = %d \n", dragon.speed.x, dragon.speed.y);
}
