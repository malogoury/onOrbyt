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
#define	OFFSET_PALETTE	0
#define	SLOP_PALETTE	10
#define COLOR_ARROW		200
#define	SLOPE_ARROW		5
#define	SIZE_SCREEN_X	256
#define	SIZE_SCREEN_Y	192

#define SIZE_SPRITE		32

u16 *gfx_Planet = NULL;
u16 *gfx_Spaceship = NULL;

void setUp_Stars_Background();
void setUp_Spaceship_Background();
void setUp_Planet_Background(struct Planets *Planet);
void setUpPaletteRGB();
void setUpPaletteRB();
void setUp_gameSub();
void drawLine(Coordonnee* fleche);
void drawLineRotation(double angle, int size);

void graphic_gameInit(Planet* Planet)
{

	setUpPaletteRGB();

	setUp_Stars_Background();
	setUp_Planet_Background(Planet);
	setUp_Spaceship_Background();

	setUp_gameSub();

}

void graphic_menuInit()
{
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

	BGCTRL[2] = BG_BMP_BASE(0) | BgSize_B8_256x256;

    //Affine Marix Transformation
    REG_BG2PA = 256;
    REG_BG2PC = 0;
    REG_BG2PB =  0;
    REG_BG2PD = 256;

	swiCopy(menu_imgPal, BG_PALETTE, menu_imgPalLen);
	swiCopy(menu_imgBitmap, BG_GFX, menu_imgBitmapLen);
}

void graphic_gameUpdate(Coordonnee* location)
{
    oamSet(&oamMain,
    		0,
    		location[0].x/N_POS - SIZE_SPRITE/2, location[0].y/N_POS - SIZE_SPRITE/2,
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


void graphic_gameUpdateSub(Coordonnee p0, Coordonnee p1)
{
	double angle = atan2( (p1.x-p0.x),(p1.y-p0.y) );
	int size = sqrt((p0.x-p1.x)*(p0.x-p1.x) + (p0.y-p1.y)*(p0.y-p1.y));
	drawLineRotation(angle, size);




}


void setUp_Stars_Background()
{
	u16 i =0;

	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG0_ACTIVE;
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

	BGCTRL[2] = BG_BMP_BASE(0)|BgSize_B8_256x256;


    //SetUp for stars
    REG_BG2PA = 256;
    REG_BG2PC = 0;
    REG_BG2PB = 0;
    REG_BG2PD = 256;

    u8 *ptrGFX = (u8*)BG_GFX;

    for(i=0;i<256*192;i++)
    {
    	ptrGFX[i] = *( (u8*)stars_backgroundBitmap + i) + 252;
    }


}

void setUp_Planet_Background(struct Planets *Planet)
{
	int row, column;

	BGCTRL[0] = BG_COLOR_256 | BG_MAP_BASE(26) | BG_TILE_BASE(4) | BG_32x32;
	swiCopy(planetBWTiles, (u32*)BG_TILE_RAM(4), planetBWTilesLen/2);

	u16 i = 0, j=0;

	// Clear memory from menu image
	for(i=0; i<32; i++)
	{
		for(j=0; j<32;j++)
		{
			BG_MAP_RAM(26)[32*i+j] = 0;
		}
	}

	i = 0;
	j = 0;

	// Display planets
	while(Planet[i].pos.x && Planet[i].pos.y)
	{
	    for(row = (Planet[i].pos.y)/8 -2; row< (Planet[i].pos.y)/8 +2; row++)
	    {
	    	for(column=(Planet[i].pos.x)/8 ; column< 4+(Planet[i].pos.x)/8 ; column++)
	    	{
	    		BG_MAP_RAM(26)[row*32 + column-2 ] = planetBWMap[j];
	    		j++;

	    	}
	    }
	    i++;
	}

}

void setUp_Spaceship_Background()
{

	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;
	oamInit(&oamMain, SpriteMapping_1D_32, false);

	gfx_Spaceship = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

    swiCopy(spaceshipPal, SPRITE_PALETTE, spaceshipPalLen/2);

    swiCopy((u16*)spaceshipTiles, gfx_Spaceship, spaceshipTilesLen/2);

}

void setUpPaletteRGB()
{
	int r,g,b,i=0;
	u16 *ptr_palette = BG_PALETTE;


	for(r=0; r<6;r++)
	{
		for(g=0; g<6;g++)
		{
			for(b=0; b<7;b++)
			{

				ptr_palette[i] = ARGB16(1,(31/5)*r,(31/5)*g,(31/6)*b);
				i++;

			}
		}
	}

	int j = i;
	while(i<255)
	{
		ptr_palette[i] = ARGB16(1,(i-j)*7/(255-j), (i-j)*7/(255-j), (i-j)*7/(255-j) );
		i++;
	}
	ptr_palette[255] = ARGB16(1, 10, 10, 10);

	for(i=0; i<256; i++)
	{
		//printf("palette n%d = %d  %d\n",i,ptr_palette[i],j);
	}

}

void setUpPaletteRB()
{
	int r,b,i=0;
	u16 *ptr_palette = BG_PALETTE;


	for(r=0; r<16;r++)
	{
		for(b=0; b<16;b++)
		{
			if(i<255)
			{
				ptr_palette[i] = ARGB16(1, (31/16)*r,0,(31/16)*b);
			}
			i++;
		}
	}

	int j = i;
	while(i<=255)
	{
		ptr_palette[i] = ARGB16(1,(i-j)*31/(255-j), (i-j)*31/(255-j), (i-j)*31/(255-j) );
		i++;
	}

}

void setUp_gameSub()
{
	VRAM_C_CR = VRAM_ENABLE| VRAM_C_SUB_BG;

	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE;

    BGCTRL_SUB[2] = BG_BMP_BASE(0) | BgSize_B8_256x256;

    //Affine Marix Transformation
    REG_BG2PA_SUB = 256;
    REG_BG2PC_SUB = 0;
    REG_BG2PB_SUB = 0;
    REG_BG2PD_SUB = 256;

    u16 i;
    u16 *ptr_palette_sub = BG_PALETTE_SUB;
    u8 *ptr_GFX_sub = (u8*)BG_GFX_SUB;

    for(i=0; i<255; i++)
    {
    	ptr_palette_sub[i] = ARGB16(1,(20*i)/256, 0, (31*i)/256);
    }

    for(i=0; i<256*208 ; i++)
    {
    	ptr_GFX_sub[i] = 0;
    }

}


void drawLine(Coordonnee* fleche)
{
	u8 *ptr_GFX_sub = (u8*)BG_GFX_SUB;

	if((fleche[0].x)||(fleche[0].y))
	{
		return;
	}
	if(fleche[0].x<0 || fleche[0].x>256 || fleche[0].y<0 || fleche[0].y>192) //check boundaries
	{
		return;
	}
	if(fleche[1].x<0 || fleche[1].x>256 || fleche[1].y<0 || fleche[1].y>192) //check boundaries
	{
		return;
	}

	// Let's see all possibilities
	int i= 0,j= 0;

	if((fleche[0].y>fleche[1].y)) // 0 to pi radian
	{
		if((fleche[0].x<fleche[1].x)) // 0 to pi/2 radian
		{
			int slope = (fleche[0].y-fleche[1].y)/(fleche[1].x-fleche[0].x);
			if(slope == 0)  		  // 0 to pi/4 radian
			{
				slope = (fleche[1].x-fleche[0].x)/(fleche[1].y-fleche[0].y);

				j = fleche[0].y;
				for(i = fleche[0].x; i < fleche[1].x; i++)
				{
					/*for(k=(-1)*thickness; k<thickness; k++)
					{
						ptr_GFX_sub[256*i + j +k] = 100 +k;
					}*/

					ptr_GFX_sub[256*j + i] = COLOR_ARROW;
					//thickness++;
					if( ((i-fleche[0].x)%slope)==0 )
					{
						j++;
					}
				}

			}
			else		// pi/4 to pi/2 radian
			{
				j = fleche[1].x;
				for(i = fleche[1].y; i < fleche[0].y; i++)
				{
					/*for(k=(-1)*thickness; k<thickness; k++)
					{
						ptr_GFX_sub[256*i + j +k] = 100 +k;
					}*/

					ptr_GFX_sub[256*i + j] = COLOR_ARROW;
					//thickness++;
					if( (i-fleche[1].y)%slope == 0)
					{
						j--;
					}
				}
			}
		}
		else	// pi/2 to pi radian
		{
			int slope = (fleche[0].x-fleche[1].x)/(fleche[0].y-fleche[1].y );
			if(slope == 0)  		  // pi/2 to 3pi/4 radian
			{
				slope = (fleche[0].y-fleche[1].y)/(fleche[0].x-fleche[1].x);

				j = fleche[1].x;
				for(i = fleche[1].y; i < fleche[0].y; i++)
				{
					/*for(k=(-1)*thickness; k<thickness; k++)
					{
						ptr_GFX_sub[256*i + j +k] = 100 +k;
					}*/

					ptr_GFX_sub[256*i + j] = COLOR_ARROW;
					//thickness++;
					if( ((i-fleche[1].y)%slope)== 0 )
					{
						j++;
					}
				}

			}
			else		// pi/4 to pi/2 radian
			{
				j = fleche[1].x;
				for(i = fleche[1].y; i < fleche[0].y; i++)
				{
					/*for(k=(-1)*thickness; k<thickness; k++)
					{
						ptr_GFX_sub[256*i + j +k] = 100 +k;
					}*/

					ptr_GFX_sub[256*i + j] = COLOR_ARROW;
					//thickness++;
					if( (i-fleche[1].y)%slope == 0)
					{
						j--;
					}
				}
			}

		}
	}
}


void drawLineRotation(double angle, int size)
{
	if(size>SIZE_SCREEN_Y)
	{
		size = SIZE_SCREEN_Y;
	}

	u8 *ptr_GFX_sub = (u8*)BG_GFX_SUB;
	int row, column, t, thickness =1;

	for(row=0; row<SIZE_SCREEN_Y; row++)
	{
		for(column = 0; column < SIZE_SCREEN_X; column++)
		{

			ptr_GFX_sub[row*256 + column] = 0;
		}

		if( (row<SIZE_SCREEN_Y/2 +size/2) && (row>SIZE_SCREEN_Y/2 -size/2) )
		{
			for(t= -thickness/2; t< thickness/2; t++)
			{
				ptr_GFX_sub[row*SIZE_SCREEN_X + SIZE_SCREEN_X/2 + t] = COLOR_ARROW ;
			}

			if( ((row-SIZE_SCREEN_Y/2))%(SLOPE_ARROW) == 0 )
			{
				thickness++;
			}

		}

	}

    REG_BG2PA_SUB = cos(angle)*256;
    REG_BG2PC_SUB = sin(angle)*256;
    REG_BG2PB_SUB = (-1)*sin(angle)*256;
    REG_BG2PD_SUB = cos(angle)*256;

    REG_BG2X_SUB = ( (-SIZE_SCREEN_X/2)*(cos(angle)-1) + (SIZE_SCREEN_Y/2)*sin(angle) )*256;
    REG_BG2Y_SUB = ( (-SIZE_SCREEN_X/2)*sin(angle) - (SIZE_SCREEN_Y/2)*(cos(angle)-1) )*256;

}


