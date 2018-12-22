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

void game_main();
void game_reset();

void game_init(void)
{
	if (state_game==IDLE_game)
		map_init(planets, MAP1);
	graphic_gameInit(planets);
	physic_init(&orion);
	state_game=INIT_game;
	game_main();
}
void game_update(void)
{
	if(state_game==PLAY_game)
		physic_updatePos(&orion, planets);
}

void game_displayUpdate(void)
{
	graphic_gameUpdate(orion.pos);
}

void game_main()
{
	FSM_sub state_arrow=INIT_sub;
	Coordonnee touched = {0,0};
	Coordonnee tmp_touch = {0,0};
	touchPosition touch;
	while(1)
	{
		scanKeys();
		if(keysDown() & KEY_TOUCH)
		{
			touchRead(&touch);
			if((touch.px || touch.py) && state_arrow==INIT_sub)
			{
				if(state_game == PLAY_game)
					game_init();
				touched.x=touch.px;
				touched.y=touch.py;
				printf("%d %d \n",touched.x,touched.y);
				state_arrow=DRAG_sub;
			}
		}
		else if(keysUp() & KEY_TOUCH)
		{
			touchRead(&touch);
			Coordonnee vect;
			vect.x = touched.x-tmp_touch.x;
			vect.y = touched.y-tmp_touch.y;
			printf("%d,%d\n",touched.x,touched.y);

			orion.speed = physic_velocityInit(vect);
			state_game=PLAY_game;
		}
		if(keysHeld() & KEY_TOUCH)
		{
			touchRead(&touch);
			if(state_arrow==DRAG_sub)
			{
				tmp_touch.x=touch.px;
				tmp_touch.y=touch.py;
				//printf("%d,%d\n",tmp_touch.x,tmp_touch.y);
			}
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
			{
				game_init();
			}
		}
		game_displayUpdate();
		swiWaitForVBlank();
	}
}
