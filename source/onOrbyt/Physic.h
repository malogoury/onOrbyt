/*
 * Physic.h
 *
 *  Created on: Dec 9, 2018
 *      Author: nds
 */

#include "onOrbyt_defines.h"
#include "Map.h"

typedef struct Spacecrafts Spacecraft;
struct Spacecrafts
{
	Coordonnee pos[NB_POS];			// mpix
	Coordonnee speed;				// mpix/ms
};

void physic_init(Spacecraft* spacecraft);
void physic_updatePos(Spacecraft* spacecraft, Planet* planets);

