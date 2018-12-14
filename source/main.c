/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <stdio.h>

#include "onOrbyt/Game.h"

int main(void) {
	
    consoleDemoInit();
    printf("\nHello World!\n");
    game_update();
    while(1)
        swiWaitForVBlank();	
}
