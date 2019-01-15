/*
 * LL_Graphic.h
 *
 *  Created on: Dec 14, 2018
 *      Author: nds
 */

#ifndef LL_GRAPHIC_H_
#define LL_GRAPHIC_H_


#endif /* LL_GRAPHIC_H_ */

#include "onOrbyt/Map.h"
#include "spaceship.h"
#include "menu_img.h"
#include "menu_lower.h"
#include "MAP1.h"
#include "MAP2.h"
#include "MAP3.h"
#include "MAP4.h"
#include "arrow_space.h"
#include "arrow_spaceship.h"
#include "arrow_wireframe.h"
#include "panel_control.h"

void graphic_gameInit(Planet* Planet);
void graphic_gameUpdate(Coordonnee* location, Coordonnee dir);
void graphic_gameUpdateSub(Coordonnee p0, Coordonnee p1, Coordonnee speed);
void graphic_menuInit();
