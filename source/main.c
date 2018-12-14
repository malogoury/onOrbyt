/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>

#include "onOrbyt/Game.h"

int main(void) {
	// Initialisations

    consoleDemoInit();
    printf("\nHello World!\n");

    game_init();

    // Main infinite loop
    while(1)
        swiWaitForVBlank();	
}
