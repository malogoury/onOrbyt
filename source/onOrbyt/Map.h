/*
 * Map.h
 *
 *  Created on: Dec 14, 2018
 *      Author: nds
 */

#ifndef MAP_H_
#define MAP_H_

#include "onOrbyt_defines.h"

typedef enum Maps{MAP1,MAP2,MAP3,MAP4} Maps;

typedef struct Coordonnees Coordonnee;
struct Coordonnees
{
	int x,y;
};

typedef struct Planets Planet;
struct Planets {
	int mu;				// mu is G*M
	int radius;
	Coordonnee pos;

};

void map_init(Planet* planets, Maps map);

#endif /* MAP_H_ */
