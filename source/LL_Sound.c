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

mm_sfxhand sound_motor;

void sound_menuInit()
{
	mmInitDefaultMem((mm_addr)soundbank_bin);


	mmLoad(MOD_69213_SCZ);
	mmStart(MOD_69213_SCZ, MM_PLAY_LOOP);

}

void sound_gameInit()
{
	//mmStop();

	mmLoad(MOD_SPACEEXPLORATION_GAME);
	mmLoadEffect(SFX_EXPLOSION_X);
	mmLoadEffect(SFX_WIND);

	mmStart(MOD_SPACEEXPLORATION_GAME, MM_PLAY_LOOP);

	sound_motor = mmEffect(SFX_WIND);
	mmEffectVolume(sound_motor, 100);
}

void sound_gameOver()
{
	mmEffect(SFX_EXPLOSION_X);
}

void sound_gameUpdate(Coordonnee speed)
{
	int speedTot = sqrt(speed.x*speed.x + speed.y*speed.y);

	sound_motor = mmEffect(SFX_WIND);
	mmEffectRate(sound_motor, 1024 + speedTot/10);
	mmEffectVolume(sound_motor, 70);

}

