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
void calc_acc(Coordonnee posPl, Coordonnee posSp, int mu, float* aX, float* aY);

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

	Coordonnee acc = {0,0}, delta = {0,0}, new_pos = {0,0};
	int r2=0,r=0;
	int i;
	for(i=0;i<NB_PLANETS;i++)
	{
		if(planets[i].mu != 0)
		{
			//printf("%d %d %d %d \n", spacecraft->pos[0].x, spacecraft->pos[0].y, planets[i].pos.x, planets[i].pos.y);
			delta.x = planets[i].pos.x - spacecraft->pos[0].x/1000000; // delta.x max = 256
			delta.y = planets[i].pos.y - spacecraft->pos[0].y/1000000; // delta.y max = 192
			//printf("delta = %d %d \n",delta.x, delta.y);
			r2 = delta.x*delta.x + delta.y*delta.y;			// r2 max = 256*256+192*192 = 102'400
			r = (int)sqrt(r2);								// r max = 320
			//printf("r2    = %d, %d \n", r2, r);
			acc.x+=(planets[i].mu*delta.x)/(r2*r/N_ACC);   // r2*r max = 38'000'000 et mu*delta.x max = 15'360
			acc.y+=(planets[i].mu*delta.y)/(r2*r/N_ACC);	// r2*r max = 38'000'000 et mu*delta.y max = 11'520
		}
	}
	//printf("acc   = %d %d \n", acc.x, acc.y);
	new_pos.x=(spacecraft->pos[0].x)+(spacecraft->speed.x*dT)+(acc.x*dT*dT/(2*N_ACC));
	new_pos.y=(spacecraft->pos[0].y)+(spacecraft->speed.y*dT)+(acc.y*dT*dT/(2*N_ACC));
	addBufferPos(spacecraft->pos,new_pos,NB_POS);
	//printf("pos   = %d %d \n",spacecraft->pos[0].x,spacecraft->pos[0].y);
	spacecraft->speed.x+=acc.x*dT/N_ACC;
	spacecraft->speed.y+=acc.y*dT/N_ACC;
	//printf("speed = %d %d \n",spacecraft->speed.x,spacecraft->speed.y);

	/////////////////////////// float implementation ////////////////////////////////////////
//	float tmp_aX=0.0,tmp_aY=0.0;
//	float aX=0.0,aY=0.0;
//	int i;
//	for(i=0;i<NB_PLANETS;i++)
//	{
//		if(planets[i].mu != 0)
//		{
//			calc_acc(planets[i].pos,spacecraft->pos[0],planets[i].mu,&tmp_aX,&tmp_aY);
//		}
//	}
}

//void calc_acc(Coordonnee posPl, Coordonnee posSp, int mu, float* aX, float* aY)
//{
//	float dX=0.0, dY=0.0;
//	float r2=0.0,r=0.0;
//
//	dX=posPl.x-(float)(posSp.x/N_POS);
//	dY=posPl.y-(float)(posSp.y/N_POS);
//
//	r2=dX*dX+dY*dY;
//	r=sqrt(r2);
//
//	*aX=(float)(mu*dX)/(r2*r/N_ACC);
//	*aY=(float)(mu*dY)/(r2*r/N_ACC);
//}

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
