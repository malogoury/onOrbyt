/*
 * LL_Sound.h
 *
 *  Created on: Dec 28, 2018
 *      Author: nds
 */

#ifndef LL_SOUND_H_
#define LL_SOUND_H_


#endif /* LL_SOUND_H_ */

#include <nds.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"
#include "onOrbyt/Map.h"

void sound_menuInit();
void sound_gameInit();
void sound_gameOver();
void sound_gameUpdate(Coordonnee speed);
