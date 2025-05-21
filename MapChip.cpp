#include "MapChip.h"
#include "Source/screen.h"
namespace
{
	const int IMAGE_SIZE = { 32 }; //�摜�S�̂̃T�C�Y
	const int MAP_CHIP_WIDTH = { 16 }; //�摜�̉����ѐ�
	const int MAP_CHIP_HEIGHT = { 12 };//�摜�̏c���ѐ�
	const int MAP_CHIP_NUM_X = { 8 }; //�}�b�v�`�b�v�E�B���h�E�̉�
	const int MAP_CHIP_NUM_Y = { 24 };//�}�b�v�`�b�v�E�B���h�E�̏c
	const int MAP_CHIP_WIN_WIDTH = { IMAGE_SIZE * MAP_CHIP_NUM_X }; //�E�B���h�E�̉���
	const int MAP_CHIP_WIN_HEIGHT = { IMAGE_SIZE * MAP_CHIP_NUM_Y }; //�E�B���h�E�̏c��

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
	for (int i = 0; i < MAP_CHIP_NUM_X; i++) //����
	{
		for (int j = 0; j < MAP_CHIP_NUM_Y; j++) //�悱
		{
			//map�����摜�̕`��
			DrawGraph(TOPLEFT_X + i * IMAGE_SIZE, TOPLEFT_Y + j * IMAGE_SIZE,
				BgHandle[ i  + j * MAP_CHIP_NUM_X], TRUE);
		}
		
	}
	
	
	//mapEdit�̐Ԃ��g
	DrawBox(TOPLEFT_X, TOPLEFT_Y, RIGHTBOTTOM_X, RIGHTBOTTOM_Y, GetColor(255, 0, 0), FALSE,3);
	

}
