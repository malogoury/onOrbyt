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
#include <nds.h>

void game_Display_init(struct Planets *Planet);
void setUp_Stars_Background();
void setUp_Planet_Background(struct Planets *Planet);
void game_Display_update(struct Coordonnees location);
