/*
 * Game.c
 *
 *  Created on: Dec 9, 2018
 *      Author: nds
 *
 *  Functions for the game phase
 */

#include <stdio.h>
#include <nds.h>
#include "Game.h"

Spacecraft orion;
Planet planets[NB_PLANETS];
FSM_game state_game=IDLE_game;
Coordonnee arrow[2]={{0,0},{0,0}};

void game_main();
void game_reset();
void game_GameOver();

void game_init(Maps map)
{
	map_init(planets, map);
	game_reset();
	game_main();
}
void game_reset()
{
	graphic_gameInit(planets);
	physic_init(&orion);
	state_game=INIT_game;
}
void game_update(void)
{
	if(state_game==PLAY_game)
	{
		physic_updatePos(&orion, planets);
		game_GameOver();
	}
}

void game_GameOver()
{
	int i,dist2=0;
	for(i=0;i<NB_PLANETS;i++)
	{
		dist2=physic_dist(orion.pos[0],planets[i].pos);
		if(dist2<=planets[i].radius*planets[i].radius)
		{
			state_game=GAME_OVER_game;
			break;
		}
	}
}
void game_displayUpdate(void)
{

	graphic_gameUpdate(orion.pos,orion.speed);
	if(state_game==INIT_game)
		graphic_gameUpdateSub(arrow[FRONT],arrow[TAIL]);
}

void game_main()
{
	FSM_sub state_arrow=INIT_sub;
	touchPosition touch;
	while(1)
	{
		if(state_game==GAME_OVER_game)
			game_reset();
		scanKeys();
		if(keysDown() & KEY_TOUCH)
		{
			touchRead(&touch);
			if((touch.px || touch.py) && state_arrow==INIT_sub)
			{
				if(state_game == PLAY_game)
					game_reset();
				arrow[FRONT].x=touch.px;
				arrow[FRONT].y=touch.py;
				state_arrow=DRAG_sub;
			}
		}
		else if(keysUp() & KEY_TOUCH && state_arrow==DRAG_sub)
		{
			Coordonnee vect;
			vect.x = arrow[FRONT].x-arrow[TAIL].x;
			vect.y = arrow[FRONT].y-arrow[TAIL].y;
			orion.speed = physic_velocityInit(vect);
			state_arrow=INIT_sub;
			state_game=PLAY_game;
		}
		if(keysHeld() & KEY_TOUCH && state_arrow==DRAG_sub)
		{
			touchRead(&touch);
			arrow[TAIL].x=touch.px;
			arrow[TAIL].y=touch.py;
		}
		if(keysDown() & KEY_RIGHT)
		{
			if(state_game==INIT_game)
			{
				orion.speed.x = VX_INIT*N_VEL;
				orion.speed.y = VY_INIT*N_VEL;
				state_game=PLAY_game;
			}
		}
		else if(keysDown() & KEY_DOWN)
		{
			if(state_game == PLAY_game)
				game_reset();
		}
		if(keysDown() & KEY_START)
		{
			state_game = RESET_game;
			break;
		}
		game_displayUpdate();
		swiWaitForVBlank();
	}
}
