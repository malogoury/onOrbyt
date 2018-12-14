
//{{BLOCK(testplanet)

//======================================================================
//
//	testplanet, 256x192@8, 
//	+ palette 256 entries, not compressed
//	+ 307 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x24 
//	Total size: 512 + 19648 + 1536 = 21696
//
//	Time-stamp: 2018-12-14, 18:03:50
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TESTPLANET_H
#define GRIT_TESTPLANET_H

#define testplanetTilesLen 19648
extern const unsigned int testplanetTiles[4912];

#define testplanetMapLen 1536
extern const unsigned short testplanetMap[768];

#define testplanetPalLen 512
extern const unsigned short testplanetPal[256];

#endif // GRIT_TESTPLANET_H

//}}BLOCK(testplanet)
