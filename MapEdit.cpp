#include "MapEdit.h"

MapEdit::MapEdit()
	:GameObject(),myMap_(MAP_WIDTH * MAP_HEIGHT,-1) //èâä˙ílÇ-1Ç≈20*20
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
	DrawBox(0, 0, MAP_WIDTH * MAP_IMAGE_SIZE, MAP_HEIGHT * MAP_IMAGE_SIZE, GetColor(255, 255, 255), FALSE, 3);

	for (int i = 0; i < MAP_WIDTH; i++)
	{ 
		DrawLine(0, i * MAP_IMAGE_SIZE,
			MAP_WIDTH * MAP_IMAGE_SIZE, MAP_IMAGE_SIZE * i,
			GetColor(255, 255, 255), TRUE);
		for(int)
			DrawLine(MAP_IMAGE_SIZE, 0,
				     MAP_IMAGE_SIZE,MAP_HEIGHT * MAP_IMAGE_SIZE,
				GetColor(255, 255, 255), TRUE);
		
    }
   


}
