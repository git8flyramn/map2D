#include "MapEdit.h"

//左のマス目のあるマップ


MapEdit::MapEdit()
	:GameObject(),myMap_(MAP_WIDTH * MAP_HEIGHT,-1) //初期値を-1で20*20
{
	
}
 

MapEdit::~MapEdit()
{
}

void MapEdit::Update()
{
}

void MapEdit::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(LEFT_MARGIN + 0,TOP_MARGIN +0, LEFT_MARGIN + MAP_WIDTH * MAP_IMAGE_SIZE,
		   TOP_MARGIN +MAP_HEIGHT * MAP_IMAGE_SIZE, GetColor(255, 255, 0), FALSE, 3);
	

	for (int j = 0; j < MAP_WIDTH; j++)
	{ 
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
		DrawLine(LEFT_MARGIN + i * MAP_IMAGE_SIZE,TOP_MARGIN + j * MAP_IMAGE_SIZE,
			    LEFT_MARGIN + (i+1) * MAP_IMAGE_SIZE,TOP_MARGIN + j *MAP_IMAGE_SIZE,
			GetColor(255, 255, 255), 1);

		DrawLine(LEFT_MARGIN + i * MAP_IMAGE_SIZE, TOP_MARGIN + j * MAP_IMAGE_SIZE,
			LEFT_MARGIN + i * MAP_IMAGE_SIZE, TOP_MARGIN + (j + 1) * MAP_IMAGE_SIZE,
			GetColor(255, 255, 255), 1);
		}
				
		
    }
   


}
