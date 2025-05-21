#include "MapChip.h"
#include "Source/screen.h"
namespace
{
	const int IMAGE_SIZE = { 32 }; //画像全体のサイズ
	const int MAP_CHIP_WIDTH = { 16 }; //画像の横並び数
	const int MAP_CHIP_HEIGHT = { 12 };//画像の縦並び数
	const int MAP_CHIP_NUM_X = { 8 }; //マップチップウィンドウの横
	const int MAP_CHIP_NUM_Y = { 24 };//マップチップウィンドウの縦
	const int MAP_CHIP_WIN_WIDTH = { IMAGE_SIZE * MAP_CHIP_NUM_X }; //ウィンドウの横幅
	const int MAP_CHIP_WIN_HEIGHT = { IMAGE_SIZE * MAP_CHIP_NUM_Y }; //ウィンドウの縦幅

}
MapChip::MapChip()
	: GameObject()
	, BgHandle(MAP_CHIP_WIDTH* MAP_CHIP_HEIGHT, -1)
{
	LoadDivGraph("./bg.png", MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT,
		MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT,
		IMAGE_SIZE, IMAGE_SIZE, BgHandle.data());
}

MapChip::~MapChip()
{// MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT
	for (int i = 0; i < MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT; i++)
	{
		if (BgHandle[i] != -1)
		{
			DeleteGraph(BgHandle[i]);
			BgHandle[i] = -1;
		}
	}
}

void MapChip::Update()
{
}

void MapChip::Draw()
{
	int TOPLEFT_X = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
	int TOPLEFT_Y = 0;
	int RIGHTBOTTOM_X = Screen::WIDTH;
	int RIGHTBOTTOM_Y = MAP_CHIP_WIN_HEIGHT;
	for (int i = 0; i < MAP_CHIP_NUM_X; i++) //たて
	{
		for (int j = 0; j < MAP_CHIP_NUM_Y; j++) //よこ
		{
			//mapを作る画像の描画
			DrawGraph(TOPLEFT_X + i * IMAGE_SIZE, TOPLEFT_Y + j * IMAGE_SIZE,
				BgHandle[ i  + j * MAP_CHIP_NUM_X], TRUE);
		}
		
	}
	
	
	//mapEditの赤い枠
	DrawBox(TOPLEFT_X, TOPLEFT_Y, RIGHTBOTTOM_X, RIGHTBOTTOM_Y, GetColor(255, 0, 0), FALSE,3);
	

}
