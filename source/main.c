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

    // Main infinite loop
    while(1){
        //swiWaitForVBlank();
    }
}
