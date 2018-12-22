/*
 * Map.c
 *
 *  Created on: Dec 14, 2018
 *      Author: nds
 */

#include "Map.h"

void map1_init(Planet* planets);
void map2_init(Planet* planets);
void map3_init(Planet* planets);
void map4_init(Planet* planets);

void map_init(Planet* planets, Maps map)
{
	switch(map)
	{
		case MAP1:
			map1_init(planets);
			break;
		case MAP2:
			map2_init(planets);
			break;
		case MAP3:
			map3_init(planets);
			break;
		case MAP4:
			map4_init(planets);
			break;
		default:
			break;
	}
}

void map1_init(Planet *planets)
{
	int i;

	planets[0].mu = 60000;
	planets[0].pos.x = NPIX_X/2;
	planets[0].pos.y = NPIX_Y/2;
	planets[0].radius = 1;

	for(i=1;i<NB_PLANETS;i++)
	{
		planets[i].mu = 0;
		planets[i].pos.x = 0;
		planets[i].pos.y = 0;
		planets[i].radius = 0;
	}
}

void map2_init(Planet *planets)
{

}

void map3_init(Planet *planets)
{

}

void map4_init(Planet *planets)
{

}
