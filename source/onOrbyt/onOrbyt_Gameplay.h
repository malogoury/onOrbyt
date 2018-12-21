/*
 * onOrbyt_Gameplay.h
 *
 *  Created on: Dec 9, 2018
 *      Author: nds
 */

#ifndef ONORBYT_GAMEPLAY_H_
#define ONORBYT_GAMEPLAY_H_

#include "Game.h"
#include "Menu.h"

typedef enum FSM{IDLE,MENU,GAME,RESET,ERROR} FSM;

void gameplay_init(void);
void gameplay_update(void);
void gameplay_displayUpdate(void);

#endif /* ONORBYT_GAMEPLAY_H_ */
