/*
 * Menu.h
 *
 *  Created on: Dec 9, 2018
 *      Author: nds
 */

#ifndef MENU_H_
#define MENU_H_


#endif /* MENU_H_ */

#include "../LL_Graphic.h"
#include "Map.h"

typedef enum FSM_menu {IDLE_menu,INIT_menu,SELECT_menu,PLAY_menu,
	RESET_menu,ERROR_menu} FSM_menu;

void menu_init(Maps* map);
