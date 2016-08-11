#include "libs/gba.h"
#include "libs/dispcnt.h"
#include "libs/backgrounds.h"

#include "images/tiles.cpp"
#include "images/map.cpp"

int main(){
	initialize(Display::MODE_2 | Display::SPR_MAP_1D | Display::BG2_ENABLE);

	Background bg;
	bg.charBaseBlock = 0;
	bg.screenBaseBlock = 31;
	bg.colorMode = Backgrounds::COLOR256;
	bg.number = 2;
	bg.size = Backgrounds::ROTBG_SIZE_256x256;

	bg.enable();
	bg.update();

	dmaCopy(tiles_palette, BGPaletteMem, 256, DMA_ENABLE);

	bg.loadTiles(tiles, tiles_HEIGHT*tiles_WIDTH/2);
	bg.loadMap(map, 1024);

	bg.rotate(30, 1, 1);
	bg.update();

	int x = 0, y = 0, a = 0;
	while(1){
	}
}