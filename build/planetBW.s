
@{{BLOCK(planetBW)

@=======================================================================
@
@	planetBW, 32x32@8, 
@	+ palette 256 entries, not compressed
@	+ 17 tiles (t|f reduced) not compressed
@	+ regular map (flat), not compressed, 4x4 
@	Total size: 512 + 1088 + 32 = 1632
@
@	Time-stamp: 2018-12-19, 13:08:10
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global planetBWTiles		@ 1088 unsigned chars
planetBWTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x060C0000
	.word 0x00000000,0x03150000,0x00000000,0x0D140600,0x00000000,0x0814030C,0x0C000000,0x01140306
	.word 0x00000000,0x0D141506,0x14150C00,0x0F01080D,0x080D0306,0x040F0101,0x12080803,0x07040F0F
	.word 0x1208120D,0x070E0909,0x0F080808,0x10100904,0x0F011212,0x10070E04,0x040F0F0F,0x07070E04
	.word 0x030D0808,0x0000000C,0x0E040409,0x00030104,0x0210100E,0x04020202,0x10100207,0x0B0B1302
	.word 0x10101010,0x0B0B0B13,0x02021010,0x0B0B0B02,0x13021010,0x0B0B1313,0x13020707,0x0B0B1302

	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000003,0x00000000,0x000C0102,0x00000000
	.word 0x0C090B0B,0x00000000,0x090B0B13,0x0000000C,0x0B0B0B0B,0x00000001,0x05050505,0x0000140B
	.word 0x0C000000,0x01141403,0x0C0C0000,0x120D1414,0x060C0000,0x12140303,0x150C0000,0x0F0D1415
	.word 0x150C0000,0x0F120D06,0x060C0000,0x0F010815,0x06000C00,0x0F0F0114,0x15000000,0x09040F0D
	.word 0x0E040901,0x0E0E0404,0x0E0E0401,0x0404090E,0x07100401,0x09090F09,0x04100401,0x04090909
	.word 0x040E0E12,0x070E010F,0x04040412,0x07070F01,0x090F0401,0x04070409,0x0F080F09,0x0E070904
	.word 0x0210070E,0x050B0B13,0x0210070E,0x050B0B13,0x1007100E,0x0505050B,0x10020207,0x0B05050B
	.word 0x1302100E,0x0B050513,0x13130204,0x130B0513,0x13130207,0x0B0B0513,0x02130210,0x05050B10

	.word 0x0A050505,0x000C070A,0x05050B05,0x000D0A0A,0x05050B0B,0x000E110A,0x0A0A0B0B,0x150B110A
	.word 0x110A050B,0x080A110A,0x11110A05,0x0411110A,0x11110A0A,0x10161111,0x110A0A0A,0x02161111
	.word 0x15000000,0x09090908,0x15000000,0x0F09090D,0x15000000,0x01090F0D,0x06000000,0x12090114
	.word 0x06000000,0x010F0103,0x0C0C0000,0x0F010103,0x060C0000,0x01011203,0x06000000,0x0F121215
	.word 0x09080F09,0x0E070F04,0x04010F01,0x0E0E0F09,0x04090112,0x070E0E09,0x04090112,0x07070E09
	.word 0x040F1208,0x07070704,0x07010808,0x0E0E0E04,0x04010801,0x0E0E0904,0x01121201,0x040E090F
	.word 0x130B0207,0x0A0A0502,0x130B100E,0x0A0A0513,0x1302070E,0x0A05050B,0x1007070E,0x11050B05
	.word 0x020E040E,0x11050B0B,0x100E040E,0x0A050502,0x100E0E04,0x050B0B10,0x100E070E,0x05131310

	.word 0x110A0A0A,0x02161111,0x0A0A0A0A,0x10111111,0x110A0A0A,0x04111111,0x110A110A,0x120A1111
	.word 0x110A110A,0x150B1111,0x110A0A11,0x00071111,0x0A050A0A,0x000D0511,0x0A05050A,0x000C070A
	.word 0x0C000000,0x0F080D06,0x00000000,0x0F080306,0x00000000,0x1214060C,0x00000000,0x0D060C00
	.word 0x00000000,0x06000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x0112120F,0x09040901,0x0108120F,0x0F090909,0x0108010F,0x0409040F,0x010F0F12,0x0909090F
	.word 0x0F09120D,0x09040409,0x090F1406,0x09040409,0x12030C00,0x0F090F01,0x0C000000,0x080D0306
	.word 0x10071007,0x050B0207,0x0E0E100E,0x050B0210,0x040E070E,0x050B1007,0x040E0404,0x0B0B1007
	.word 0x0F090909,0x0B13100E,0x04090F09,0x0910070E,0x040F010F,0x00030109,0x15140D08,0x0000000C

	.word 0x0A050505,0x0000140B,0x05050505,0x00000001,0x09050505,0x0000000C,0x0C090B0B,0x00000000
	.word 0x000C0102,0x00000000,0x00000003,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global planetBWMap		@ 32 unsigned chars
planetBWMap:
	.hword 0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,0x0008
	.hword 0x0009,0x000A,0x000B,0x000C,0x000D,0x000E,0x000F,0x0010

	.section .rodata
	.align	2
	.global planetBWPal		@ 512 unsigned chars
planetBWPal:
	.hword 0x0000,0x2529,0x4210,0x1084,0x318C,0x4E73,0x0842,0x39CE
	.hword 0x1CE7,0x2D6B,0x5294,0x4A52,0x0421,0x18C6,0x35AD,0x294A
	.hword 0x3DEF,0x56B5,0x2108,0x4631,0x14A5,0x0C63,0x5AD6,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(planetBW)
