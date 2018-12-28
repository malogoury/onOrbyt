/*
 * Sound.c
 *
 *  Created on: Dec 9, 2018
 *      Author: nds
 *
 *  Low level functions to generate sound
 */

#include "LL_Sound.h"


void sound_initMenu()
{
	mmInitDefaultMem((mm_addr)soundbank_bin);

	mmLoad(MOD_ENACOSTIONE_MENU);

	mmStart(MOD_ENACOSTIONE_MENU, MM_PLAY_LOOP);
}


