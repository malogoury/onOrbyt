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

#define	SIZE_SCREEN_X	256
#define	SIZE_SCREEN_Y	192
#define SIZE_TILE		32
#define SIZE_SPRITE		64

#define	PI				3.14159
#define N_PLANET_MAX	5

// sub slot memory
#define MAP_SUB	0
#define TILE_SUB	11
#define BMP_PANEL	8
#define BMP_ARROW	4

#define POS_LED		19*32 + 16
#define POS_SCORE	21*32
#define TIMER_LED	10
#define TIMER_LED2	4
#define TIMER_SCORE	5000
#define	SCALE_POWER	8
#define SCALE_SPEED	3

#define EMPTY_TILE	0
#define	MEDIUM_TILE	1
#define POWER_TILE	2
#define LED_TILE	3

u16 *gfx_Spaceship = NULL;

u8 emptyTile[64] =
{
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
};

u8 mediumTile[64] =
{
		1,1,1,1,1,1,1,1,
		1,1,3,3,3,3,1,1,
		1,3,3,3,3,3,3,1,
		1,3,3,3,3,3,3,1,
		1,3,3,3,3,3,3,1,
		1,3,3,3,3,3,3,1,
		1,1,3,3,3,3,1,1,
		1,1,1,1,1,1,1,1

};

u8 powerTile[64] =
{
		1,1,1,1,1,1,1,1,
		3,3,3,3,3,3,3,3,
		5,5,5,5,5,5,5,5,
		5,5,5,5,5,5,5,5,
		5,5,5,5,5,5,5,5,
		5,5,5,5,5,5,5,5,
		3,3,3,3,3,3,3,3,
		1,1,1,1,1,1,1,1
};

u8 LEDTile[64] =
{
		1,1,1,1,1,1,1,1,
		1,1,3,3,3,3,1,1,
		1,3,3,5,5,3,3,1,
		1,3,5,5,5,5,3,1,
		1,3,5,5,5,5,3,1,
		1,3,3,5,5,3,3,1,
		1,1,3,3,3,3,1,1,
		1,1,1,1,1,1,1,1
};




void setUp_Spaceship_Background();
void setUp_MAP(struct Planets *Planet);;
void setUp_gameSub();
void setUp_UpperMenu();
void setUp_LowerMenu();
void update_Spaceship(Coordonnee* location, Coordonnee dir);
void update_flamme(Coordonnee* location);
void rotoscaleSpaceship(double angle, int size);
void draw_Power_Spaceship(int power);
void draw_Speed_Spaceship(int speed);
void draw_Time_Spaceship(int speed);
void draw_Led_Spaceship();
void draw_Led2_Spaceship();




//--------INITIALIZATION-----------------------------------------//


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



//--------MEMORY SET-UP-----------------------------------------//

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

    BGCTRL_SUB[2] = BG_BMP_BASE(8) |(u16)BgSize_B8_256x256;

    //Affine Matrix Transformation
    REG_BG2PA_SUB = 256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 256;

    REG_BG2X_SUB = 0;
    REG_BG2Y_SUB = 0;

    swiCopy(menu_lowerPal, BG_PALETTE_SUB, menu_lowerPalLen);
    swiCopy(menu_lowerBitmap, BG_BMP_RAM_SUB(16), menu_lowerBitmapLen/2);
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

	BGCTRL[3] = BG_BMP_BASE(0)|(u16)BgSize_B8_256x256; // Background for the map
	BGCTRL[2] = BG_BMP_BASE(8)|(u16)BgSize_B16_256x256; // Background for the flame



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
 * Set up memory bank and control register for displaying the arrow on the lower screen
 *
 */
void setUp_gameSub()
{
	u16 i;

	VRAM_C_CR = VRAM_ENABLE| VRAM_C_SUB_BG;
	VRAM_I_CR = VRAM_ENABLE | VRAM_I_SUB_BG_0x06208000;

	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE;

	BGCTRL_SUB[1] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(MAP_SUB) | BG_TILE_BASE(TILE_SUB); // Background for animation
	BGCTRL_SUB[2] = BG_BMP_BASE(BMP_ARROW) |(u16)BgSize_B8_256x256; // Background for rotating spaceship
	BGCTRL_SUB[3] = BG_BMP_BASE(BMP_PANEL) |(u16)BgSize_B8_256x256; // Background for control panel




    //Affine Matrix Transformation

    REG_BG2PA_SUB = 256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 256;

    REG_BG2X_SUB = 0;
    REG_BG2Y_SUB = 0;

    REG_BG3PA_SUB = 256;
    REG_BG3PC_SUB = 0;
    REG_BG3PB_SUB = 0;
    REG_BG3PD_SUB = 256;

    REG_BG3X_SUB = 0;
    REG_BG3Y_SUB = 0;
;
	// create palette
	swiCopy(panel_controlPal, BG_PALETTE_SUB, panel_controlPalLen);

    // clear the screen
	u8 *ptr_GFX_sub = (u8*)BG_BMP_RAM_SUB(BMP_PANEL);
    for(i=0; i<(SIZE_SCREEN_X*SIZE_SCREEN_X)-1 ; i++)
    {
    	ptr_GFX_sub[i] = 0;
    }

    // Display panel control and rotating spaceship
    ptr_GFX_sub = (u8*)BG_BMP_RAM_SUB(BMP_PANEL);
    swiCopy(panel_controlBitmap, ptr_GFX_sub, panel_controlBitmapLen/2);
    ptr_GFX_sub = (u8*)BG_BMP_RAM_SUB(BMP_ARROW);
    swiCopy(arrow_spaceshipBitmap, ptr_GFX_sub, arrow_spaceshipBitmapLen/2);

    dmaCopy(emptyTile, &BG_TILE_RAM_SUB(TILE_SUB)[EMPTY_TILE*SIZE_TILE], SIZE_TILE*2);
    dmaCopy(mediumTile, &BG_TILE_RAM_SUB(TILE_SUB)[MEDIUM_TILE*SIZE_TILE], SIZE_TILE*2);
    dmaCopy(powerTile, &BG_TILE_RAM_SUB(TILE_SUB)[POWER_TILE*SIZE_TILE], SIZE_TILE*2);
    dmaCopy(LEDTile, &BG_TILE_RAM_SUB(TILE_SUB)[LED_TILE*SIZE_TILE], SIZE_TILE*2);

    for(i=0; i<32*32;i++)
    {
    	BG_MAP_RAM_SUB(MAP_SUB)[i] = EMPTY_TILE;
    }


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




//--------GRAPHIC UPDATE-----------------------------------------//

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
void graphic_gameUpdateSub(Coordonnee p0, Coordonnee p1, Coordonnee speed)
{


	double angle = atan2( (p1.x-p0.x),(p1.y-p0.y) ); // angle of the arrow
	int size = sqrt((p0.x-p1.x)*(p0.x-p1.x) + (p0.y-p1.y)*(p0.y-p1.y)); // length of the arrow

	rotoscaleSpaceship(angle, size);
	draw_Power_Spaceship(size);
	draw_Led_Spaceship();
	draw_Led2_Spaceship();

	// scale the speed to normal units
	speed.x = speed.x/N_VEL;
	speed.y = speed.y/N_VEL;

	draw_Speed_Spaceship(sqrt(speed.x*speed.x + speed.y*speed.y));
	draw_Time_Spaceship(sqrt(speed.x*speed.x + speed.y*speed.y));
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
 * Update the color and position of the spaceship's flame
 *
 */
void update_flamme(Coordonnee* location)
{
	int i;
	u16 *ptr_GFX = BG_BMP_RAM(8);

	// Display the actual flame
	for(i=0; i< NB_POS-1; i++)
	{
		ptr_GFX[ (location[i].y/N_POS)*SIZE_SCREEN_X + (location[i].x/N_POS)] = ARGB16(1, 31-i*31/NB_POS, 10-i*10/NB_POS, 7);
	}

	// Display a faint trace of the spaceship
	ptr_GFX[ (location[i].y/N_POS)*SIZE_SCREEN_X + (location[i].x/N_POS)] = ARGB16(1,5,2,2);

}

/**
 * Draw a line of tiles proportional to the initial speed of the spaceship
 *
 */
void draw_Power_Spaceship(int power)
{
	int i;

	power = power/SCALE_POWER; // scale to fit in the screen

	// check boundaries
	if(power > SIZE_TILE)
	{
		power = SIZE_TILE;
	}
	if(power<0)
	{
		power = 0;
	}

	// Clear previous speed
    for(i=0; i<(2*SIZE_TILE);i++)
    {
    	BG_MAP_RAM_SUB(MAP_SUB)[i] = EMPTY_TILE;
    }
    // Draw actual speed
    for(i=0; i<power;i++)
    {
    	BG_MAP_RAM_SUB(MAP_SUB)[i] = POWER_TILE;
    	BG_MAP_RAM_SUB(MAP_SUB)[i + 32] = POWER_TILE;
    }

}
/**
 *  Draw a line of tiles proportional to the actual speed of the spaceship
 *
 */
void draw_Speed_Spaceship(int speed)
{
	int i;
	speed = speed/SCALE_SPEED; // scale to fit in the screen

	// Check boundaries
	if(speed>SIZE_TILE)
	{
		speed = SIZE_TILE;
	}
	if(speed<1)
	{
		speed = 0;
	}

	// Clear previous speed
    for(i=0; i<(2*SIZE_TILE);i++)
    {
    	BG_MAP_RAM_SUB(MAP_SUB)[22*SIZE_TILE + i] = EMPTY_TILE;
    }
    // Draw actual speed
    for(i=0; i<speed;i++)
    {
    	BG_MAP_RAM_SUB(MAP_SUB)[22*SIZE_TILE + i] = POWER_TILE;
    	BG_MAP_RAM_SUB(MAP_SUB)[23*SIZE_TILE + i] = POWER_TILE;
    }
}

/**
 * Draw a line of tiles proportional to the time of flight of the spaceship
 *
 */
void draw_Time_Spaceship(int speed)
{
	static int i = 0;
	static int distance = 0;

	if(speed == 0) // reset command
	{
		i = 0;
	}

	distance += speed; // integrate speed to get the distance

	// draw a new tile when the distance cross the threshold
	if(distance > TIMER_SCORE && i < SIZE_TILE)
	{
		BG_MAP_RAM_SUB(MAP_SUB)[POS_SCORE + i] = LED_TILE;
		i++;
		distance = 0;
	}

}

/**
 * Blink a LED at regular interval
 *
 */
void draw_Led_Spaceship()
{
	static int counter = 0;

	if(counter > 2*TIMER_LED)// turn off the LED
	{
		BG_MAP_RAM_SUB(MAP_SUB)[POS_LED] = EMPTY_TILE;
	}
	if(counter > 3*TIMER_LED)// transitional state of the LED
	{
		BG_MAP_RAM_SUB(MAP_SUB)[POS_LED] = MEDIUM_TILE;
	}
	if(counter > 4*TIMER_LED)// turn on the LED
	{
		BG_MAP_RAM_SUB(MAP_SUB)[POS_LED] = LED_TILE;
		counter = 0;
	}
	counter++;
}

/**
 * Blink another LED at regular interval
 *
 */
void draw_Led2_Spaceship()
{
	static int counter = 0;

	if(counter > 2*TIMER_LED2)// turn off the LED
	{
		BG_MAP_RAM_SUB(MAP_SUB)[POS_LED-1] = EMPTY_TILE;
	}
	if(counter > 3*TIMER_LED2)// transitional state of the LED
	{
		BG_MAP_RAM_SUB(MAP_SUB)[POS_LED-1] = MEDIUM_TILE;
	}
	if(counter > 4*TIMER_LED2)// turn on the LED
	{
		BG_MAP_RAM_SUB(MAP_SUB)[POS_LED-1] = LED_TILE;
		counter = 0;
	}
	counter++;
}

/**
 * Rotate the spaceship to show direction of impulse
 *
 */
void rotoscaleSpaceship(double angle, int size)
{
	// rotate the Spaceship image

    REG_BG2PA_SUB = cos(angle)*256;
    REG_BG2PC_SUB = sin(angle)*256;
    REG_BG2PB_SUB = (-1)*sin(angle)*256;
    REG_BG2PD_SUB = cos(angle)*256;

    // Bring the image back to the center of the screen
    REG_BG2X_SUB = ( (-SIZE_SCREEN_X/2)*(cos(angle)-1) + (SIZE_SCREEN_Y/2)*sin(angle) )*256;
    REG_BG2Y_SUB = ( (-SIZE_SCREEN_X/2)*sin(angle) - (SIZE_SCREEN_Y/2)*(cos(angle)-1) )*256;


}
