#pragma once
struct MapChipConfig
{
	int TILE_PIX_SIZE;//1�^�C���̃s�N�Z���T�C�Y
	int TILE_X;       //�}�b�v�`�b�v�V�[�g�̃}�b�v�`�b�v�̉����ѐ�
	int TILE_Y;
	int MAPCHIP_VIEW_X;
	int MAPCHIP_VIEW_Y;
	int MAPCHIP_WIN_WIDTH;
	int MAPCHIP_WIN_HEIGHT;
}; 

const MapChipConfig& GetMapChipConfig();

