/*
 * Graphic.c
 *
 *  Created on: Dec 9, 2018
 *      Author: nds
 *
 *  Low level functions to display graphics
 */

#include <nds.h>
#include "LL_Graphic.h"

u16 *gfx_Planet = NULL;
u16 *gfx_Spaceship = NULL;

void setUp_Stars_Background();
void setUp_Planet_Background(struct Planets *Planet);

void graphic_gameInit(Planet* Planet)
{
	setUp_Stars_Background();
	setUp_Planet_Background(Planet);

}

void graphic_gameUpdate(Coordonnee* location)
{
    oamSet(&oamMain,
    		1,
    		location[0].x/1000, location[0].y/1000,
    		0,
    		0,
    		SpriteSize_32x32,
    		SpriteColorFormat_256Color,
    		gfx_Spaceship,
    		-1,
    		false,
    		false,
    		false, false,
    		false);
    oamUpdate(&oamMain);
}


void setUp_Stars_Background()
{
	VRAM_A_CR = VRAM_ENABLE //Enable
			| VRAM_A_MAIN_BG; //Bank for the main engine

	REG_DISPCNT = MODE_0_2D | DISPLAY_BG0_ACTIVE;

	BGCTRL[0] = BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_32x32;

    /*REG_BG2PA = 256;
    REG_BG2PC = 0;
    REG_BG2PB = 0;
    REG_BG2PD = 256;*/


    swiCopy(stars_backgroundTiles, BG_TILE_RAM(1), stars_backgroundTilesLen/2);
    swiCopy(stars_backgroundPal, BG_PALETTE, stars_backgroundPalLen/2);
    swiCopy(stars_backgroundMap, BG_MAP_RAM(0), stars_backgroundMapLen/2);

}

void setUp_Planet_Background(Planet *Planet)
{

	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;
	oamInit(&oamMain, SpriteMapping_1D_32, false);

	gfx_Planet = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	gfx_Spaceship = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

    swiCopy(jupiterPal, SPRITE_PALETTE, jupiterPalLen/2);
    swiCopy(jupiterTiles, gfx_Planet, jupiterTilesLen/2);

    //swiCopy(spaceshipPal, SPRITE_PALETTE+jupiterPalLen/2, spaceshipPalLen/2);
    swiCopy(spaceshipTiles, gfx_Spaceship, spaceshipTilesLen/2);


    oamSet(&oamMain,
    		0,
    		Planet[0].pos.x/1000, Planet[0].pos.y/1000,
    		0,
    		0,
    		SpriteSize_32x32,
    		SpriteColorFormat_256Color,
    		gfx_Planet,
    		-1,
    		false,
    		false,
    		false, false,
    		false);

    oamUpdate(&oamMain);

}
