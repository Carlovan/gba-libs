#ifndef BG_H
#define BG_H

//BGCNT defines
namespace Backgrounds{
	enum BackgroundControl{
		ENABLE_MOSAIC         = 0x40,
	  	COLOR256              = 0x80,
	  	COLOR16               = 0x0,

		CHAR_SHIFT            = 0x2,
		SCREEN_SHIFT          = 0x8,

		TEXTBG_SIZE_256x256   = 0x0,
		TEXTBG_SIZE_256x512   = 0x8000,
		TEXTBG_SIZE_512x256   = 0x4000,
		TEXTBG_SIZE_512x512   = 0xC000,
		ROTBG_SIZE_128x128    = 0x0,
		ROTBG_SIZE_256x256    = 0x4000,
		ROTBG_SIZE_512x512    = 0x8000,
		ROTBG_SIZE_1024x1024  = 0xC000,

		WRAP                  = 0x200
	};
}

#define CharBaseBlock(n)      (((n)*0x4000)+0x6000000)
#define ScreenBaseBlock(n)    (((n)*0x800)+0x6000000)

typedef struct Background
{
	Background(){
		mosaic = colorMode = number = size = charBaseBlock = screenBaseBlock = 0;
		wraparound = x_scroll = y_scroll = DX = DY = PB = PD = 0;
		PA = PC = 1;
		priority = 3;
	}
	u16* tileData;
	u16* mapData;
	u8 mosaic;
	u8 colorMode;
	u16 number;
	u16 size;
	u16 charBaseBlock;
	u16 screenBaseBlock;
	u8 wraparound;
	s16 x_scroll,y_scroll;
	s32 DX,DY;
	s16 PA,PB,PC,PD;
	u16 priority;

	void update();
	void enable();
	void loadTiles(const u16 tiles[], int size);
	void loadMap(const u16 map[], int size);
	void rotate(int angle, s32 x_scale, s32 y_scale);
}Background;

#endif
