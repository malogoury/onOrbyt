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
Coordonnee calc_acc(Coordonnee posPl, Coordonnee posSp, int mu);
Coordonnee calc_pos(Coordonnee posSp, Coordonnee velSp, Coordonnee acc);

void physic_init(Spacecraft* spacecraft)
{
	int i=0;
	for(i=0;i<NB_POS;i++)
	{
		spacecraft->pos[i].x = X_INIT*N_POS;
		spacecraft->pos[i].y = Y_INIT*N_POS;
	}
	spacecraft->speed.x = 0;
	spacecraft->speed.y = 0;
}

void physic_updatePos(Spacecraft* spacecraft, Planet* planets)
{

	/////////////////////////// diagonal flow ////////////////////////////////////////
//	Coordonnee new_pos = {0,0};
//	new_pos.x = (spacecraft->pos[0].x+500)%(NPIX_X*1000);
//	new_pos.y = (spacecraft->pos[0].y+500)%(NPIX_Y*1000);
//	addBufferPos(spacecraft->pos, new_pos, NB_POS);
//	/////////////////////////// constant velocity ////////////////////////////////////////
//	Coordonnee new_pos = {0,0};
//	new_pos.x = (spacecraft->pos[0].x+spacecraft->speed.x*dT)%(NPIX_X*1000);
//	new_pos.y = (spacecraft->pos[0].y+spacecraft->speed.y*dT)%(NPIX_Y*1000);
//	addBufferPos(spacecraft->pos, new_pos, NB_POS);


	/////////////////////////// integer implementation ////////////////////////////////////////

	Coordonnee acc = {0,0}, new_pos = {0,0};
	Coordonnee tmp_acc={0,0};
	int i;
	for(i=0;i<NB_PLANETS;i++)
	{
		if(planets[i].mu != 0)
		{
			tmp_acc=calc_acc(planets[i].pos,spacecraft->pos[0],planets[i].mu);
			acc.x+=tmp_acc.x;
			acc.y+=tmp_acc.y;
		}
	}
	//printf("acc   = %d %d \n", acc.x, acc.y);
	new_pos = calc_pos(spacecraft->pos[0],spacecraft->speed,acc);
	addBufferPos(spacecraft->pos,new_pos,NB_POS);
	//printf("pos   = %d %d \n",spacecraft->pos[0].x,spacecraft->pos[0].y);
	spacecraft->speed.x+=acc.x*dT/N_ACC;
	spacecraft->speed.y+=acc.y*dT/N_ACC;
	//printf("speed = %d %d \n",spacecraft->speed.x,spacecraft->speed.y);
}

Coordonnee calc_pos(Coordonnee posSp, Coordonnee velSp, Coordonnee acc)
{
	Coordonnee new_pos={0,0};
	new_pos.x=(posSp.x)+(velSp.x*dT)+(acc.x*dT*dT/(2*N_ACC));
	new_pos.y=(posSp.y)+(velSp.y*dT)+(acc.y*dT*dT/(2*N_ACC));
	return new_pos;
}
Coordonnee calc_acc(Coordonnee posPl, Coordonnee posSp, int mu)
{
	Coordonnee acc={0,0}, delta={0,0};
	int r2=0,r=0;
	delta.x=posPl.x-posSp.x/N_POS;					// delta.x max = 256
	delta.y=posPl.y-posSp.y/N_POS;					// delta.y max = 192

	r2=delta.x*delta.x+delta.y*delta.y;				// r2 max = 256*256+192*192 = 102'400
	r=(int)sqrt(r2);								// r max = 320

	acc.x=(mu*delta.x)/(r2*r/N_ACC);				// r2*r max = 38'000'000 et mu*delta.x max = 15'360
	acc.y=(mu*delta.y)/(r2*r/N_ACC);				// r2*r max = 38'000'000 et mu*delta.y max = 11'520

	return acc;
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
	velocity.x = vect.x*N_VEL/RATIO_VEL_INIT;
	velocity.y = vect.y*N_VEL/RATIO_VEL_INIT;
	return velocity;
}
