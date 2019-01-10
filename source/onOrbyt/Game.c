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

/**
 * inits map (planets for physics) and sound
 */
void game_init(Maps map)
{
	map_init(planets, map);
	sound_gameInit();
	game_reset();
	game_main();
}

/**
 * inits graphics and physic
 */
void game_reset()
{
	graphic_gameInit(planets);
	physic_init(&orion);
	state_game=INIT_game;
}

/**
 * called every 10ms by the timer ISR
 * updates physics and detect if game over
 */
void game_update(void)
{
	if(state_game==PLAY_game)
	{
		physic_updatePos(&orion, planets);
		game_GameOver();
	}
}

/**
 * Detects if spacecraft is inside the radius of a planet
 */
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

/**
 * updates main and sub graphics
 */
void game_displayUpdate(void)
{
	graphic_gameUpdate(orion.pos,orion.speed);
	if(state_game==INIT_game || state_game==PLAY_game)
		graphic_gameUpdateSub(arrow[FRONT],arrow[TAIL]);
}

/**
 * key pooling and FSMs update
 */
void game_main()
{
	FSM_sub state_arrow=INIT_sub;
	touchPosition touch;
	while(1)
	{
		// resets graphics and physics in case of game over or new init vector
		if(state_game==GAME_OVER_game)
		{
			sound_gameOver();
			game_reset();
		}

		scanKeys();

		// save vector initial coordinates
		if(keysDown() & KEY_TOUCH)
		{
			touchRead(&touch);
			if((touch.px || touch.py) && state_arrow==INIT_sub)
			{
				arrow[FRONT].x=touch.px;
				arrow[FRONT].y=touch.py;
				state_arrow=DRAG_sub;
			}
		}
		// creates vector, reset game, launch spacecraft
		else if(keysUp() & KEY_TOUCH && state_arrow==DRAG_sub)
		{
			if(state_game == PLAY_game)
				game_reset();
			Coordonnee vect;
			vect.x = arrow[FRONT].x-arrow[TAIL].x;
			vect.y = arrow[FRONT].y-arrow[TAIL].y;
			orion.speed = physic_velocityInit(vect);
			state_arrow=INIT_sub;
			state_game=PLAY_game;
		}
		// update vector for sub graphics
		if(keysHeld() & KEY_TOUCH && state_arrow==DRAG_sub)
		{
			touchRead(&touch);
			arrow[TAIL].x=touch.px;
			arrow[TAIL].y=touch.py;
		}
		// resets game to return to menu
		if(keysDown() & KEY_START)
		{
			state_game = RESET_game;
			// return to onOrbytGameplay.
			break;
		}
		// update graphic
		game_displayUpdate();
		swiWaitForVBlank();
	}
}
