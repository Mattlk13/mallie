/******************************************************************************/
/*                                                                            */
/*    Copyright (c) 2011, DNA Research, the 3Delight Developers.              */
/*    All Rights Reserved.                                                    */
/*                                                                            */
/******************************************************************************/

#include "half.h"

/*
	basetable and shiftable below are used to convert floating
	point numbers into half floats.

	This method is described in:

	Fast Half Float Conversions by Jeroen van der Zijp
	November 2008 (Revised September 2010)
*/

unsigned short basetable[512] = {
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0001,
	0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080,0x0100,
	0x0200,0x0400,0x0800,0x0c00,0x1000,0x1400,0x1800,0x1c00,
	0x2000,0x2400,0x2800,0x2c00,0x3000,0x3400,0x3800,0x3c00,
	0x4000,0x4400,0x4800,0x4c00,0x5000,0x5400,0x5800,0x5c00,
	0x6000,0x6400,0x6800,0x6c00,0x7000,0x7400,0x7800,0x7c00,
	0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,
	0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,
	0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,
	0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,
	0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,
	0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,
	0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,
	0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,
	0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,
	0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,
	0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,
	0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,
	0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,
	0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,0x7c00,
	0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
	0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
	0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
	0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
	0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
	0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
	0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
	0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
	0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
	0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
	0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
	0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,
	0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8000,0x8001,
	0x8002,0x8004,0x8008,0x8010,0x8020,0x8040,0x8080,0x8100,
	0x8200,0x8400,0x8800,0x8c00,0x9000,0x9400,0x9800,0x9c00,
	0xa000,0xa400,0xa800,0xac00,0xb000,0xb400,0xb800,0xbc00,
	0xc000,0xc400,0xc800,0xcc00,0xd000,0xd400,0xd800,0xdc00,
	0xe000,0xe400,0xe800,0xec00,0xf000,0xf400,0xf800,0xfc00,
	0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,
	0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,
	0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,
	0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,
	0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,
	0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,
	0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,
	0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,
	0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,
	0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,
	0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,
	0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,
	0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,
	0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,0xfc00,
};

unsigned short shifttable[512] = {
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x017,
	0x016,0x015,0x014,0x013,0x012,0x011,0x010,0x00f,
	0x00e,0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,
	0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,
	0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,
	0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x00d,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x017,
	0x016,0x015,0x014,0x013,0x012,0x011,0x010,0x00f,
	0x00e,0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,
	0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,
	0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,
	0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,0x00d,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x018,
	0x018,0x018,0x018,0x018,0x018,0x018,0x018,0x00d,
};

short FloatToHalf( int f )
{
	return basetable[(f>>23)&0x1ff]+((f&0x007fffff)>>shifttable[(f>>23)&0x1ff]);
}