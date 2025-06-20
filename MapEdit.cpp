#include "MapEdit.h"
#include <cassert>
#include "Input.h"
#include "DxLib.h"
#include "MapChip.h"
//左のマス目のあるマップ


MapEdit::MapEdit()
	:GameObject(),myMap_(MAP_WIDTH * MAP_HEIGHT,-1),isInMapEditArea_(false) //初期値を-1で20*20
{
	mapEditRect_ = { LEFT_MARGIN ,TOP_MARGIN,
				MAP_WIDTH * MAP_IMAGE_SIZE, MAP_HEIGHT * MAP_IMAGE_SIZE };
}
 

MapEdit::~MapEdit()
{
}

void MapEdit::SetMap(Point p, int value)
{
	//pが配列の範囲外の時はassretに引っかかる
	assert(p.x >= 0 && p.x < MAP_WIDTH);
	assert(p.y >= 0 && p.y < MAP_HEIGHT);
	myMap_[p.y * MAP_WIDTH + p.x] = value;
}

int MapEdit::GetMap(Point p) const
{
	//マップの座標pの値を取得する
	//pが配列の範囲外の時はassretに引っかかる
	assert(p.x >= 0 && p.x < MAP_WIDTH);
	assert(p.y >= 0 && p.y < MAP_HEIGHT);
	return myMap_[p.y * MAP_WIDTH + p.x];
}

void MapEdit::Update()
{
	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1)
	{
		return;
	}
	//isInMapEditArea_ = (mousePos.x >= mapEditRect_.x
	//	&& mousePos.x <= mapEditRect_.x + mapEditRect_.w
	//	&& mousePos.y <= mapEditRect_.y && mousePos.y >= mapEditRect_.y + mapEditRect_.h);//エリアの判定

	isInMapEditArea_ = (mousePos.x >= mapEditRect_.x
		&& mousePos.x <= mapEditRect_.x + mapEditRect_.w
		&& mousePos.y >= mapEditRect_.y
		&& mousePos.y <= mapEditRect_.y + mapEditRect_.h);
	if (!isInMapEditArea_)
	{
		return;
	}
	int gridX = (mousePos.x - LEFT_MARGIN) / MAP_IMAGE_SIZE;
	int gridY = (mousePos.y - TOP_MARGIN) / MAP_IMAGE_SIZE;
	drawAreaRect_ = { LEFT_MARGIN + gridX * MAP_IMAGE_SIZE, TOP_MARGIN + gridY * MAP_IMAGE_SIZE,
		MAP_IMAGE_SIZE, MAP_IMAGE_SIZE };
	if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
	{
		MapChip* mapChip = FindGameObject<MapChip>();
		if (mapChip && mapChip->IsHold())
		{
			SetMap({ gridX,gridY }, mapChip->GetHoldImage());
		}
	}
}

void MapEdit::Draw()
{
	for (int j = 0; j < MAP_WIDTH; j++)
	{
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			int value = GetMap({ i,j });
			if (value != -1) //-1なら何も描画しない
			{
				DrawGraph(LEFT_MARGIN + i * MAP_IMAGE_SIZE, TOP_MARGIN + j * MAP_IMAGE_SIZE,
					value, TRUE);
			}
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(LEFT_MARGIN + 0, TOP_MARGIN + 0,
		LEFT_MARGIN + MAP_WIDTH * MAP_IMAGE_SIZE, TOP_MARGIN + MAP_HEIGHT * MAP_IMAGE_SIZE, GetColor(255, 255, 0), FALSE, 5);
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
				
	/*	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(LEFT_MARGIN + 0, TOP_MARGIN + 0,
			LEFT_MARGIN + MAP_WIDTH * MAP_IMAGE_SIZE,
			TOP_MARGIN + MAP_HEIGHT * MAP_IMAGE_SIZE, GetColor(255, 255, 0), FALSE, 5);*/

    }
	if (isInMapEditArea_)
	{
		DrawBox(drawAreaRect_.x, drawAreaRect_.y,
			drawAreaRect_.x + drawAreaRect_.w,
			drawAreaRect_.y + drawAreaRect_.h, GetColor(255, 255, 0), TRUE);
    }
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}
