/*
 * Game.h
 *
 *  Created on: Dec 9, 2018
 *      Author: nds
 *
 *  Header file for Game.c
 */
#pragma once

#include "../LL_Graphic.h"
#include "Physic.h"
#include "onOrbyt_defines.h"

typedef enum FSM_game {IDLE_game,INIT_game,PLAY_game,GAME_OVER_game,
	RESET_game,ERROR_game} FSM_game;
typedef enum FSM_sub {IDLE_sub,INIT_sub,DRAG_sub} FSM_sub;
void game_init(void);
void game_update(void);
void game_displayUpdate(void);
