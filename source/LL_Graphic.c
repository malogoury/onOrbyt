/*
 * Graphic.c
 *
 *  Created on: Dec 9, 2018
 *      Author: nds
 *
 *  Low level functions to display graphics
 */

#include "LL_Graphic.h"
#include "stars_background.h"
#include "earth1.h"

void game_Display_init(struct Planets *Planet)
{
	setUp_Stars_Background();
	setUp_Planet_Background(Planet);

}


void setUp_Stars_Background()
{
	VRAM_A_CR = VRAM_ENABLE //Enable
			| VRAM_A_MAIN_BG; //Bank for the main engine

	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;

	BGCTRL[2] = BG_MAP_BASE(0) | BgSize_B8_256x256;

    REG_BG2PA = 256;
    REG_BG2PC = 0;
    REG_BG2PB = 0;
    REG_BG2PD = 256;


    swiCopy(stars_backgroundPal, BG_PALETTE, stars_backgroundPalLen);
    swiCopy(stars_backgroundBitmap, BG_GFX, stars_backgroundBitmapLen);

}

void setUp_Planet_Background(struct Planets *Planet)
{
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;
	oamInit(&oamMain, SpriteMapping_1D_32, false);

	u16 *gfx = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

    swiCopy(earth1Pal, SPRITE_PALETTE, earth1PalLen/2);
    swiCopy(earth1Tiles, gfx, earth1TilesLen/2);


    oamSet(&oamMain,
    		0,
    		Planet[0].pos.x, Planet[0].pos.y,
    		0,
    		0,
    		SpriteSize_32x32,
    		SpriteColorFormat_256Color,
    		gfx,
    		-1,
    		false,
    		false,
    		false, false,
    		false);

    swiWaitForVBlank();

    oamUpdate(&oamMain);

}
