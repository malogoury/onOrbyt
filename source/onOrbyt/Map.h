/*
 * Map.h
 *
 *  Created on: Dec 14, 2018
 *      Author: nds
 */

#ifndef MAP_H_
#define MAP_H_

typedef struct Coordonnees Coordonnee;
struct Coordonnees
{
	int x,y;
};

typedef struct Planets Planet;
struct Planets {
	int mu;
	Coordonnee pos;
	int radius;
};

#endif /* MAP_H_ */
