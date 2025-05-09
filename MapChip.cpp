#include "MapChip.h"
#include "Source/screen.h"
namespace
{
	const int IMAGE_SIZE = { 32 }; //�摜�S�̂̃T�C�Y
	const int MAP_CHIP_WIDTH = { 16 }; //�摜�̉����ѐ�
	const int MAP_CHIP_HEIGHT = { 12 };
	const int MAP_CHIP_NUM_X = { 8 }; //�}�b�v�`�b�v�E�B���h�E�̉�
	const int MAP_CHIP_NUM_Y = { 24 };//�}�b�v�`�b�v�E�B���h�E�̏c
	const int MAP_CHIP_WIN_WIDTH = { IMAGE_SIZE * 8}; //�E�B���h�E�̉���
	const int MAP_CHIP_WIN_HEIGHT = { IMAGE_SIZE * 24}; //�E�B���h�E�̏c��
	int TOPLEFT_X = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
	int TOPLIGHT_Y = 0;
	int RIGHTBOTTOM_X = Screen::WIDTH;
	int RIGHTBOTTOM_Y = MAP_CHIP_WIN_HEIGHT;

}
MapChip::MapChip()
	: GameObject()
	,BgHandle(MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT,-1)
{
	LoadDivGraph("./bg.png", MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT,
		MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT,
		IMAGE_SIZE, IMAGE_SIZE, BgHandle.data());
}

MapChip::~MapChip()
{
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
	for (int j = 0; j < MAP_CHIP_WIN_HEIGHT; j++) //����
	{
		for (int i = 0; i < MAP_CHIP_WIN_WIDTH; i++) //�悱
		{
		//DrawGraph(i * IMAGE_SIZE, j * IMAGE_SIZE,BgHandle[i + j * MAP_CHIP_WIDTH], TRUE);
			//DrawGraph(i * IMAGE_SIZE + TOPLEFT_X, j * IMAGE_SIZE + TOPLIGHT_Y, BgHandle[i * MAP_CHIP_WIDTH], TRUE);
			
		}
		
	}
	
	DrawBox(TOPLEFT_X, TOPLIGHT_Y, RIGHTBOTTOM_X, RIGHTBOTTOM_Y, GetColor(255, 0, 0), FALSE,3);
	

}
