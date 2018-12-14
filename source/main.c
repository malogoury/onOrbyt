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


    Planet Planet_test[2];
    Planet_test[0].pos.x = 100;
    Planet_test[0].pos.y = 100;

    Coordonnee location;
    location.x = 0;
    location.y = 0;


    game_Display_init(Planet_test);

    irqInit();
    timer_init();
    gameplay_init();

    // Main infinite loop
    while(1){
        swiWaitForVBlank();	
        /*game_Display_update(location);
        location.x ++;
        location.y ++;*/
    }
}
