////////////////////////////////////////////////////////////////////////
// File:        dispcnt.h                                             //
// Description: Contains all the relevant defines for the REG_DISPCNT //
//              register which can be found in gba.h                  //
// Author:      dovoto (modified by gbajunkie)                        //
// Date:        9th January 2002                                      //
////////////////////////////////////////////////////////////////////////
#ifndef DISPCNT_H
#define DISPCNT_H

#include "gba.h"

// Constants to control the display
namespace Display{
	enum Flags{
		// Bits to select display mode
		MODE_0     = 0x0,
		MODE_1     = 0x1,
		MODE_2     = 0x2,
		MODE_3     = 0x3,
		MODE_4     = 0x4,
		MODE_5     = 0x5,

		// Screen size
		WIDTH      = 240,
		HEIGHT     = 160,

		// Bits to enable backgrounds and sprites
		BG0_ENABLE = 0x100,
		BG1_ENABLE = 0x200,
		BG2_ENABLE = 0x400,
		BG3_ENABLE = 0x800,
		SPR_ENABLE = 0x1000,

		// Bits to select sprites mapping mode (matrix (2D) or vector (1D))
		SPR_MAP_2D = 0x0,
		SPR_MAP_1D = 0x40
	};

	
}
void initialize(u32 mode);


// --- Not used yet --- //

//Define the buffer which is used to set the active buffer
//when using double buffering
#define BACKBUFFER     0x10

//This bit, when set allows OAM(Object Attribute Memory) to
//be updated during a horizontal blank
#define H_BLANK_OAM    0x20

//Causes the screen to go white by using a forced blank
#define FORCE_BLANK    0x80

//allows window displays (dont worry about these)
#define WIN1_ENABLE    0x2000
#define WIN2_ENABLE    0x4000
#define WINSPR_ENABLE  0x8000




#endif
