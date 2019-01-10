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

 	// 10ms interruption for game's physics update
    timer_init();

    // infinite loop for gameplay FSM: 
    while(1)
    	gameplay_init();
    	// return from gameplay_init() is done only in case of a game reset

    return 0;
}
