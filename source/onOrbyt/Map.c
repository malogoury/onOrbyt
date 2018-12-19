/*
 * Map.c
 *
 *  Created on: Dec 14, 2018
 *      Author: nds
 */

#include "Map.h"

void map1_init(Planet* planets);

void map_init(Planet* planets, Maps map)
{
	switch(map)
	{
		case MAP1:
			map1_init(planets);
			break;
		default:
			break;
	}
}

void map1_init(Planet *planets)
{
	int i;

	planets[0].mu = 60;
	planets[0].pos.x = NPIX_X*1000/2;
	planets[0].pos.y = NPIX_Y*1000/2;
	planets[0].radius = 1;

	for(i=1;i<NB_PLANETS;i++)
	{
		planets[i].mu = 0;
		planets[i].pos.x = 0;
		planets[i].pos.y = 0;
		planets[i].radius = 0;
	}
}
