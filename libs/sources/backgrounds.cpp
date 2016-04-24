#include "../gba.h"
#include "../backgrounds.h"
#include "../sincos.h"
#include "../dispcnt.h"

// Initializes the background
void Background::enable(){
	u16 temp;

	tileData = (u16*)CharBaseBlock((u64)(charBaseBlock));
	mapData = (u16*)ScreenBaseBlock((u64)(screenBaseBlock));
	temp = size | (charBaseBlock<<Backgrounds::CHAR_SHIFT) | (screenBaseBlock<<Backgrounds::SCREEN_SHIFT)
		| colorMode | mosaic | wraparound;

	switch(number)
	{
	case 0:
		REG_BG0CNT = temp;
		REG_DISPCNT |= Display::BG0_ENABLE;
		break;
	case 1:
		REG_BG1CNT = temp;
		REG_DISPCNT |= Display::BG1_ENABLE;
		break;
	case 2:
		REG_BG2CNT = temp;
		REG_DISPCNT |= Display::BG2_ENABLE;
		break;
	case 3:
		REG_BG3CNT = temp;
		REG_DISPCNT |= Display::BG3_ENABLE;
		break;
	}
}

// Copies background data to the memory registers
void Background::update(){
	switch(number)
	{
	// It can be only a text background
	case 0:
		// Check if it's enabled in the current mode
		if((REG_DISPCNT & 7) == Display::MODE_0 || (REG_DISPCNT & 7) == Display::MODE_1){
			REG_BG0HOFS = x_scroll;
			REG_BG0VOFS = y_scroll;
			REG_BG0CNT &= ~((u16)3);
			REG_BG0CNT |= (priority & 3);
		}
		break;
	// Samething as background 0
	case 1:
		if((REG_DISPCNT & 7) == Display::MODE_0 || (REG_DISPCNT & 7) == Display::MODE_1){
			REG_BG1HOFS = x_scroll;
			REG_BG1VOFS = y_scroll;
			REG_BG1CNT &= ~((u16)3);
			REG_BG1CNT |= (priority & 3);
		}
		break;
	// Background 2 is present in every mode
	case 2:
		REG_BG2CNT &= ~((u16)3);
		REG_BG2CNT |= (priority & 3);
		// Check if it's a rotational background
		if((REG_DISPCNT & 7) == Display::MODE_1 || (REG_DISPCNT & 7) == Display::MODE_2){
			REG_BG2X = DX;
			REG_BG2Y = DY;

			REG_BG2PA = PA;
			REG_BG2PB = PB;
			REG_BG2PC = PC;
			REG_BG2PD = PD;
		}
		// Else is a text background
		else{
			REG_BG2HOFS = x_scroll;
			REG_BG2VOFS = y_scroll;
		}
		break;
	// Samething as background 2
	case 3:
		REG_BG3CNT &= ~((u16)3);
		REG_BG3CNT |= (priority & 3);
		
		if((REG_DISPCNT & 7) == Display::MODE_2){
			REG_BG3X = DX;
			REG_BG3Y = DY;

			REG_BG3PA = PA;
			REG_BG3PB = PB;
			REG_BG3PC = PC;
			REG_BG3PD = PD;
		}
		else if((REG_DISPCNT & 7) == Display::MODE_0){
			REG_BG3HOFS = x_scroll;
			REG_BG3VOFS = y_scroll;
		}
		break;
	}
}

void Background::loadTiles(const u16 tiles[], int size){
	dmaCopy(tiles, tileData, size, DMA_ENABLE);
}

void Background::loadMap(const u16 map[], int size){
	dmaCopy(map, mapData, size, DMA_ENABLE);
}

//Applica modifiche al bg per poi essere updatato
void Background::rotate(int angle, s32 x_scale, s32 y_scale){
	DX = 0;
	DY = 0;

	PA = (((1<<8)/x_scale) * COS[angle])>>8;
	PB = (((1<<8)/y_scale) * SIN[angle])>>8;
	PC = (((1<<8)/x_scale) * -SIN[angle])>>8;
	PD = (((1<<8)/y_scale) * COS[angle])>>8;
}