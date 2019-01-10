/*
 * Sound.c
 *
 *  Created on: Dec 9, 2018
 *      Author: nds
 *
 *  Low level functions to generate sound
 */

#include "LL_Sound.h"
#include <math.h>

/**
 * Load the menu's music and start playing it
 *
 */
void sound_menuInit()
{
	mmInitDefaultMem((mm_addr)soundbank_bin);

	mmLoad(MOD_69213_SCZ);
	mmStart(MOD_69213_SCZ, MM_PLAY_LOOP);
}

/**
 * Load the game's music and start playing it
 * Load explosion effect
 *
 */
void sound_gameInit()
{
	mmLoad(MOD_SPACEEXPLORATION_GAME);
	mmLoadEffect(SFX_EXPLOSION_X);

	mmStart(MOD_SPACEEXPLORATION_GAME, MM_PLAY_LOOP);
}

/**
 * Play explosion effect, called when spaceship crashes into a planet
 *
 */
void sound_gameOver()
{
	mmEffect(SFX_EXPLOSION_X);
}

