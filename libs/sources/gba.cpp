#include "../gba.h"

u32* OAMmem        =  (u32*)0x7000000;
u16* VideoBuffer   =  (u16*)0x6000000;
u16* OAMData       =  (u16*)0x6010000;
u16* BGPaletteMem  =  (u16*)0x5000000;
u16* OBJPaletteMem =  (u16*)0x5000200;

//Wait for the screen to stop drawing
inline void waitForVsync()
{
	while((volatile u16)REG_VCOUNT != 160);
}

// 
inline void dmaCopy(const void* source, void* dest, u32 count, u32 mode){
	REG_DM3CNT = 0;
	REG_DM3SAD = (u32)source;
	REG_DM3DAD = (u32)dest;
	REG_DM3CNT = count | mode;
}

// Mette in pausa il programma per ms 1024esimi di secondo
inline void sleep(int ms){
	int counter = 0;
	int prev = 0;
	REG_TM0D = 0;
	REG_TM0CNT = TM_FREQ_1024 | TM_ENABLE;
	while(counter < (ms<<4)){
		while(REG_TM0D == prev);
		counter++;
		prev = REG_TM0D;
	}
}

// Returns absolute value of the given number
inline int abs(int a){
	return (a<0?-a:a);
}

// Modify parameter and returns the given number with 1-bits of flag toggled (example: toggleBits(0b1001, 0b101) = 0b1100)
inline u32 toggleBits(u32& n, u32 flag){
	return n = (n & ~flag) | ((n & flag) ^ flag);
}

inline u32 setBits(u32& n, u32 mask){
	return n |= mask;
}

inline u32 unsetBits(u32& n, u32 mask){
	return n &= ~mask;
}