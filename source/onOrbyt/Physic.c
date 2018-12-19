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
#include <math.h>
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

void physic_updatePos(Spacecraft* spacecraft, Planet* planets)
{
//	Coordonnee new_pos = {0,0};
//	new_pos.x = (spacecraft->pos[0].x+500)%(NPIX_X*1000);
//	new_pos.y = (spacecraft->pos[0].y+500)%(NPIX_Y*1000);
//	addBufferPos(spacecraft->pos, new_pos, NB_POS);

	Coordonnee new_pos = {0,0};
	new_pos.x = (spacecraft->pos[0].x+spacecraft->speed.x*dT)%(NPIX_X*1000);
	new_pos.y = (spacecraft->pos[0].y+spacecraft->speed.y*dT)%(NPIX_Y*1000);
	addBufferPos(spacecraft->pos, new_pos, NB_POS);

//	Coordonnee acc = {0,0}, delta = {0,0}, new_pos = {0,0};
//	static double ax = 0.0, ay = 0.0;
//	unsigned int r2=0,r=0;
//	int i;
//	for(i=0;i<NB_PLANETS;i++)
//	{
//		if(planets[i].mu != 0)
//		{
//			//printf("%d %d %d %d \n", spacecraft->pos[0].x, spacecraft->pos[0].y, planets[i].pos.x, planets[i].pos.y);
//			delta.x = planets[i].pos.x/1000 - spacecraft->pos[0].x/1000; // delta.x max = 256
//			delta.y = planets[i].pos.y/1000 - spacecraft->pos[0].y/1000; // delta.y max = 192
//			r2 = delta.x*delta.x + delta.y*delta.y;			// r2 max = 256*256+192*192 = 102'400
//			r = (unsigned int)sqrt(r2);		// r max = 320
//			//printf("%lu, %d, %d \n", r2, delta.x, delta.y);
//			ax+=(planets[i].mu*delta.x)/(r2*r);   // r2*r max = 38'000'000 et mu*delta.x max = 15'360
//			ay+=(planets[i].mu*delta.y)/(r2*r);	// r2*r max = 38'000'000 et mu*delta.y max = 11'520
//			//printf("%d, %d, %d \n", i, acc.x, acc.y);
//		}
//	}
//	if(ax>=1.0)
//	{
//		acc.x=(int)ax;
//		ax=ax-acc.x;
//	}
//	if(ay>=1.0)
//	{
//		acc.y=(int)ay;
//		ay=ay-acc.y;
//	}
//	printf("%d %d \n", acc.x, acc.y);
//	new_pos.x=(spacecraft->pos[0].x)+(spacecraft->speed.x*dT)+(acc.x*dT*dT/2);
//	new_pos.y=(spacecraft->pos[0].y)+(spacecraft->speed.y*dT)+(acc.y*dT*dT/2);
//	addBufferPos(spacecraft->pos,new_pos,NB_POS);
//	//printf("%d %d \n",spacecraft->pos[0].x,spacecraft->pos[0].y);
//	spacecraft->speed.x+=acc.x*dT/1000;
//	spacecraft->speed.x+=acc.x*dT/1000;
}

void addBufferPos(Coordonnee* pos, Coordonnee new_pos, int length)
{
	int i;
	for(i=length-1;i>0; i--)
		pos[i]=pos[i-1];
	pos[0] = new_pos;
}

Coordonnee physic_velocityInit(Coordonnee vect)
{
	Coordonnee velocity;
	velocity.x = vect.x*RATIO_VEL_INIT;
	velocity.y = vect.y*RATIO_VEL_INIT;
	return velocity;
}
