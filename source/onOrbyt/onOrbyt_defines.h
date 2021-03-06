/*
 * onOrbyt_defines.h
 *
 *  Created on: Dec 14, 2018
 *      Author: nds
 */

#ifndef ONORBYT_DEFINES_H_
#define ONORBYT_DEFINES_H_

// Physics defines
#define NB_POS			200
#define NB_PLANETS		5
#define X_INIT 			256/2		// pix
#define Y_INIT			50			// pix
#define VX_INIT			42			// pix/s
#define VY_INIT			0			// pix/s
#define RATIO_VEL_INIT	2			//
#define dT				10			// ms

// Map define
#define R_MICRO			7			// pix
#define R_SMALL			9			// pix
#define R_MEDIUM		17			// pix
#define R_LARGE			25			// pix

// NDS define
#define NPIX_X			256
#define	NPIX_Y			192

// Define to avoid overflows in phyisics computations
#define N_ACC			1000		// Ratio to correct acceleration unit
#define N_VEL			1000		// Ratio to correct velocity unit
#define	N_POS			1000000		// Ratio to correct position unit

// velocity vector define
#define FRONT			0
#define	TAIL			1
#endif /* ONORBYT_DEFINES_H_ */
