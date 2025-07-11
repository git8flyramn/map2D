#pragma once
struct MapChipConfig
{
	int TILE_PIX_SIZE;//1タイルのピクセルサイズ
	int TILE_X;       //マップチップシートのマップチップの横並び数
	int TILE_Y;
	int MAPCHIP_VIEW_X;
	int MAPCHIP_VIEW_Y;
	int MAPCHIP_WIN_WIDTH;
	int MAPCHIP_WIN_HEIGHT;
}; 

const MapChipConfig& GetMapChipConfig();

