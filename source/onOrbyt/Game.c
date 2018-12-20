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

void game_init(void)
{
	map_init(planets, MAP1);
	//printf("planet x = %d, y = %d \n", planets[0].pos.x, planets[0].pos.y);
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
	static Coordonnee touched = {0,0};
	unsigned keysPressed,keysReleased;
	touchPosition touch;
	while(1)
	{
		scanKeys();
		keysPressed = keysDown();
		keysReleased = keysUp();
		if(keysPressed & KEY_TOUCH)
		{
			touchRead(&touch);
			//printf("%d %d \n",touch.px,touch.py);
			if(touch.px || touch.py)
			{
				touched.x=touch.px;
				touched.y=touch.py;
				printf("Hello there \n");
			}
		}
		else if(keysReleased & KEY_TOUCH)
		{
			touchRead(&touch);
			if(state_game == INIT_game && (touch.px || touch.py))
			{
				Coordonnee vect;
				vect.x = touched.x-touch.px;
				vect.y = touched.y-touch.py;
				orion.speed = physic_velocityInit(vect);
				//state_game=PLAY_game;
			}
		}
		else if(keysPressed & KEY_RIGHT)
		{
			if(state_game==INIT_game)
			{
				orion.speed.x = VX_INIT;
				orion.speed.y = VY_INIT;
				state_game=PLAY_game;
			}
		}
		else if(keysPressed & KEY_DOWN)
		{
			if(state_game==PLAY_game)
			{
				state_game = INIT_game;
				//orion.speed.x = VY_INIT;
				//orion.speed.y = VX_INIT;
			}
		}
	}
}
