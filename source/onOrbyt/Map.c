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
	planets[0].radius = R_LARGE;

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
	int i;

	planets[0].mu = 60000;
	planets[0].pos.x = NPIX_X/3;
	planets[0].pos.y = NPIX_Y/3;
	planets[0].radius = R_MEDIUM;

	planets[1].mu = 60000;
	planets[1].pos.x = 2*NPIX_X/3;
	planets[1].pos.y = 2*NPIX_Y/3;
	planets[1].radius = R_MICRO;

	for(i=2;i<NB_PLANETS;i++)
	{
		planets[i].mu = 0;
		planets[i].pos.x = 0;
		planets[i].pos.y = 0;
		planets[i].radius = 0;
	}
}

void map3_init(Planet *planets)
{
	int i;

	planets[2].mu = 60000;
	planets[2].pos.x = NPIX_X/3;
	planets[2].pos.y = NPIX_Y/4;
	planets[2].radius = R_SMALL;

	planets[1].mu = 60000;
	planets[1].pos.x = 2*NPIX_X/3;
	planets[1].pos.y = NPIX_Y/4;
	planets[1].radius = R_SMALL;

	planets[0].mu = 60000;
	planets[0].pos.x = NPIX_X/2;
	planets[0].pos.y = 3*NPIX_Y/4;
	planets[0].radius = R_MEDIUM;

	for(i=3;i<NB_PLANETS;i++)
	{
		planets[i].mu = 0;
		planets[i].pos.x = 0;
		planets[i].pos.y = 0;
		planets[i].radius = 0;
	}
}

void map4_init(Planet *planets)
{
	planets[3].mu = 60000;
	planets[3].pos.x = NPIX_X/4;
	planets[3].pos.y = NPIX_Y/4;
	planets[3].radius = R_MEDIUM;

	planets[1].mu = 60000;
	planets[1].pos.x = 3*NPIX_X/4;
	planets[1].pos.y = NPIX_Y/4;
	planets[1].radius = R_SMALL;

	planets[2].mu = 60000;
	planets[2].pos.x = 3*NPIX_X/4;
	planets[2].pos.y = 3*NPIX_Y/4;
	planets[2].radius = R_SMALL;

	planets[0].mu = 60000;
	planets[0].pos.x = NPIX_X/4;
	planets[0].pos.y = 3*NPIX_Y/4;
	planets[0].radius = R_MICRO;

	planets[4].mu = 60000;
	planets[4].pos.x = NPIX_X/2;
	planets[4].pos.y = NPIX_Y/2;
	planets[4].radius = R_LARGE;
}
