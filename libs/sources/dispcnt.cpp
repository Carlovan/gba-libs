#include "../dispcnt.h"
#include "../gba.h"


	void initialize(u32 mode){
		unsetBits(REG_DISPCNT, ~0);
		setBits(REG_DISPCNT, mode);
	}
