/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>
#include "LL_Graphic.h"
#include "onOrbyt/onOrbyt_Gameplay.h"
#include "LL_Timer.h"

int main(void) {
	// Initialisations

    consoleDemoInit();
    printf("\nHello World!\n");

    irqInit();
    timer_init();
    gameplay_init();


    Planet Planet_test[2];
    Planet_test[0].pos.x = 100;
    Planet_test[0].pos.y = 100;

    game_Display_init(Planet_test);

    // Main infinite loop
    while(1)
        swiWaitForVBlank();	
}
