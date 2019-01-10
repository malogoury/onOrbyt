/*
 * Graphic.c
 *
 *  Created on: Dec 9, 2018
 *      Author: nds
 *
 *  Low level functions to display graphics
 */

#include <nds.h>
#include <math.h>
#include "LL_Graphic.h"

#define	SLOPE_ARROW		5
#define	SIZE_SCREEN_X	256
#define	SIZE_SCREEN_Y	192
#define NB_UPDATE		3

#define SIZE_SPRITE		64
#define	PI				3.14159

#define N_PLANET_MAX	5

u16 *gfx_Spaceship = NULL;


void setUp_Spaceship_Background();
void setUp_MAP(struct Planets *Planet);;
void setUp_gameSub();
void setUp_UpperMenu();
void setUp_LowerMenu();
void update_Spaceship(Coordonnee* location, Coordonnee dir);
void update_flamme(Coordonnee* location);
void drawLineRotation(double angle, int size);



/**
 * Setup upper and lower graphic for the game phase
 *
 */
void graphic_gameInit(Planet* Planet)
{
	setUp_MAP(Planet);

	setUp_Spaceship_Background();

	setUp_gameSub();
}

/**
 * Setup upper and lower graphic for the menu phase
 *
 */
void graphic_menuInit()
{
	setUp_UpperMenu();
	setUp_LowerMenu();
}


/**
 * Update the upper graphic (Spaceship and its flame)
 *
 */
void graphic_gameUpdate(Coordonnee* location, Coordonnee dir)
{
	update_Spaceship(location, dir);
	update_flamme(location);
}

/**
 * Update the lower graphic
 *
 */
void graphic_gameUpdateSub(Coordonnee p0, Coordonnee p1)
{
	static int counter = 0;

	if (counter > NB_UPDATE) // update the arrow only once in a while
	{
		double angle = atan2( (p1.x-p0.x),(p1.y-p0.y) ); // angle of the arrow
		int size = sqrt((p0.x-p1.x)*(p0.x-p1.x) + (p0.y-p1.y)*(p0.y-p1.y)); // length of the arrow

		drawLineRotation(angle, size);
		counter = 0;
	}
	counter ++;

}

/**
 * Set up memory bank and control register for upper menu image
 *
 */
void setUp_UpperMenu()
{
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;

	BGCTRL[2] = BG_BMP_BASE(0) |(u16)BgSize_B8_256x256;

    // Affine Matrix Transformation
    REG_BG2PA = 256;
    REG_BG2PC = 0;
    REG_BG2PB =  0;
    REG_BG2PD = 256;

	swiCopy(menu_imgPal, BG_PALETTE, menu_imgPalLen);
	swiCopy(menu_imgBitmap, BG_GFX, menu_imgBitmapLen/2);
}

/**
 * Set up memory bank and control register for lower menu image
 *
 */
void setUp_LowerMenu()
{
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE;

	VRAM_C_CR = VRAM_ENABLE| VRAM_C_SUB_BG;

    BGCTRL_SUB[2] = BG_BMP_BASE(16) |(u16)BgSize_B8_256x256;

    //Affine Matrix Transformation
    REG_BG2PA_SUB = 256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 256;

    swiCopy(menu_lowerPal, BG_PALETTE_SUB, menu_lowerPalLen);
    swiCopy(menu_lowerBitmap, BG_BMP_RAM_SUB(16), menu_lowerBitmapLen/2);
}

/**
 * Set up sprite mode for the spaceship
 *
 */
void setUp_Spaceship_Background()
{
	VRAM_E_CR = VRAM_ENABLE | VRAM_E_MAIN_SPRITE;
	oamInit(&oamMain, SpriteMapping_1D_32, false);

	gfx_Spaceship = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

    swiCopy(spaceshipPal, SPRITE_PALETTE, spaceshipPalLen/2);
    swiCopy((u16*)spaceshipTiles, gfx_Spaceship, spaceshipTilesLen/2);
}


/**
 * Display the new position of the spaceship
 *
 */
void update_Spaceship(Coordonnee* location, Coordonnee dir)
{
    float theta=( atan2(dir.y,dir.x) +PI/2)*32768/(2*PI); // angle of rotation of the spaceship

    s16 s = sinLerp(theta) >> 4;
    s16 c = cosLerp(theta) >> 4;

    // rotate spaceship's sprite
    oamMain.oamRotationMemory->hdx = c;
    oamMain.oamRotationMemory->hdy = s;
    oamMain.oamRotationMemory->vdx = -s;
    oamMain.oamRotationMemory->vdy = c;

    // translate spaceship's sprite
    oamSet(&oamMain,
    		0,
    		location[0].x/N_POS - SIZE_SPRITE/2, location[0].y/N_POS - SIZE_SPRITE/2,
    		0,
    		0,
    		SpriteSize_32x32,
    		SpriteColorFormat_256Color,
    		gfx_Spaceship,
    		0,
    		true,
    		false,
    		false, false,
    		false);

    // update display of the sprite
    oamUpdate(&oamMain);
}

/**
 * Set up memory bank and control register for displaying the map and the flame of the spaceship
 * Display the map chosen by the player
 *
 */
void setUp_MAP(struct Planets *Planet)
{
	// Set up memory and register for the map and the spaceship flame
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG3_ACTIVE| DISPLAY_BG2_ACTIVE;

	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG; // memory for the map
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_BG; // memory for the flame

	BGCTRL[3] = BG_BMP_BASE(0)|(u16)BgSize_B8_256x256; // map
	BGCTRL[2] = BG_BMP_BASE(8)|(u16)BgSize_B16_256x256; // flame



    //Affine Matrix
    REG_BG3PA = 256;
    REG_BG3PC = 0;
    REG_BG3PB = 0;
    REG_BG3PD = 256;


    // load image map depending on the choice of map
    if(Planet[N_PLANET_MAX-1].mu)
    {
    	swiCopy(MAP4Pal, BG_PALETTE, MAP4PalLen);
    	swiCopy(MAP4Bitmap, BG_GFX, MAP4BitmapLen/2);

    }
    else if (Planet[N_PLANET_MAX-3].mu)
    {
    	swiCopy(MAP3Pal, BG_PALETTE, MAP3PalLen/2);
    	swiCopy(MAP3Bitmap, BG_GFX, MAP3BitmapLen/2);
    }
    else if (Planet[N_PLANET_MAX-4].mu)
    {
    	swiCopy(MAP2Pal, BG_PALETTE, MAP2PalLen);
    	swiCopy(MAP2Bitmap, BG_GFX, MAP2BitmapLen);
    }
    else if (Planet[N_PLANET_MAX-5].mu)
    {
    	swiCopy(MAP1Pal, BG_PALETTE, MAP1PalLen);
    	swiCopy(MAP1Bitmap, BG_GFX, MAP1BitmapLen);
    }

	// clear previous flame
	int i = 0;
	u16 *ptr_GFX = BG_BMP_RAM(8);
	for(i=0; i<SIZE_SCREEN_X*SIZE_SCREEN_Y; i++)
	{
		ptr_GFX[i] = ARGB16(0,0,0,0);
	}
}

/**
 * Update the color and position of the spaceship's flame
 *
 */
void update_flamme(Coordonnee* location)
{
	int i;
	u16 *ptr_GFX = BG_BMP_RAM(8); // slot 8 correspond to the VRAM B

	// Display the actual flame
	for(i=0; i< NB_POS-1; i++)
	{
		ptr_GFX[ (location[i].y/N_POS)*SIZE_SCREEN_X + (location[i].x/N_POS)] = ARGB16(1, 31-i*31/NB_POS, 10-i*10/NB_POS, 7);
	}

	// Display a faint trace of the spaceship
	ptr_GFX[ (location[i].y/N_POS)*SIZE_SCREEN_X + (location[i].x/N_POS)] = ARGB16(1,5,2,2);

}

/**
 * Set up memory bank and control register for displaying the arrow on the lower screen
 *
 */
void setUp_gameSub()
{
	VRAM_C_CR = VRAM_ENABLE| VRAM_C_SUB_BG;

	BGCTRL_SUB[2] = BG_BMP_BASE(16) |(u16)BgSize_B16_256x256;

	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE;



    //Affine Matrix Transformation
    REG_BG2PA_SUB = 256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 256;

    u16 i;
    u16 *ptr_GFX_sub = BG_BMP_RAM_SUB(16); // slot 16 correspond to the VRAM C

    // clear the screen
    for(i=0; i<(SIZE_SCREEN_X*SIZE_SCREEN_X)-1 ; i++)
    {
    	ptr_GFX_sub[i] = ARGB16(1,0,0,0);
    }

}

/**
 * Draw a line representing the initial speed vector of the spaceship
 *
 */
void drawLineRotation(double angle, int size)
{
	// check if the arrow is not too big
	if(size>SIZE_SCREEN_Y)
	{
		size = SIZE_SCREEN_Y;
	}

	u16 *ptr_GFX_sub = (u16*)BG_BMP_RAM_SUB(16); // slot 16 correspond to the VRAM C
	int row, column, t, thickness =1;

	irqDisable(IRQ_TIMER0);

	// draw the arrow vertically
	for(row=0; row<SIZE_SCREEN_Y; row++)
	{
		for(column = 0; column < SIZE_SCREEN_X; column++)
		{

			ptr_GFX_sub[row*256 + column] = ARGB16(1,0,0,0); // clear the screen
		}
		// check if still on the screen
		if( (row<SIZE_SCREEN_Y/2 +size/2) && (row>SIZE_SCREEN_Y/2 -size/2) )
		{
			for(t= -thickness/2; t< thickness/2; t++)
			{
				// draw pixel by pixel
				ptr_GFX_sub[row*SIZE_SCREEN_X + SIZE_SCREEN_X/2 + t] = ARGB16(1,31-2*abs(t)*31/thickness,10-2*abs(t)*10/thickness, 7) ;
			}

			if( ((row-SIZE_SCREEN_Y/2))%(SLOPE_ARROW) == 0 )
			{
				// arrow gets thicker little by little
				thickness++;
			}

		}

	}

	// rotate the arrow around center of the screen

    REG_BG2X_SUB = ( (-SIZE_SCREEN_X/2)*(cos(angle)-1) + (SIZE_SCREEN_Y/2)*sin(angle) )*256;
    REG_BG2Y_SUB = ( (-SIZE_SCREEN_X/2)*sin(angle) - (SIZE_SCREEN_Y/2)*(cos(angle)-1) )*256;

    REG_BG2PA_SUB = cos(angle)*256;
    REG_BG2PC_SUB = sin(angle)*256;
    REG_BG2PB_SUB = (-1)*sin(angle)*256;
    REG_BG2PD_SUB = cos(angle)*256;

    irqEnable(IRQ_TIMER0);
}


