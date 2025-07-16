#define NOMINMAX 
#include "MapChip.h"
#include "Source/screen.h"
#include "Input.h"
#include "ImGui/imgui.h"
#include <algorithm>
//namespace
//{
//	const int IMAGE_SIZE = { 32 }; //画像全体のサイズ
//	const int MAP_CHIP_WIDTH = { 16 }; //画像の横並び数
//	const int MAP_CHIP_HEIGHT = { 12 };//画像の縦並び数
//	const int MAP_CHIP_NUM_X = { 8 }; //マップチップウィンドウの横
//	const int MAP_CHIP_NUM_Y = { 24 };//マップチップウィンドウの縦
//	const int MAP_CHIP_WIN_WIDTH = { IMAGE_SIZE * MAP_CHIP_NUM_X }; //ウィンドウの横幅
//	const int MAP_CHIP_WIN_HEIGHT = { IMAGE_SIZE * MAP_CHIP_NUM_Y }; //ウィンドウの縦幅
//	
//	ドラッグ開始と判定する移動量の数値
//	const int DRAG_THRESHOLD = 5;
//}
//MapChip::MapChip()
//	: GameObject(),isUpdate_(false), isInMapChipArea_(false), selectedIndex_(-1)
//	, bgHandle(MAP_CHIP_WIDTH* MAP_CHIP_HEIGHT, -1), selected_({0,0}){
//
//	LoadDivGraph("./bg.png", MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT,
//		MAP_CHIP_WIDTH, MAP_CHIP_HEIGHT,
//		IMAGE_SIZE, IMAGE_SIZE, bgHandle.data());
//	for (int i = 0; i < MAP_CHIP_NUM_X; i++)
//	{
//	   for (int j = 0; j < MAP_CHIP_NUM_Y; j++)
//	   {
//         Rect tmp{
//			   i *IMAGE_SIZE, j * IMAGE_SIZE,
//			   IMAGE_SIZE,IMAGE_SIZE
//		 };
//
//		 bgRects_.push_back(tmp);
//		
//	   }
//	}
//	for (int i = 0; i < bgHandle.size(); i++)
//	{
//		HandleToIndex[ハンドル番号] = i;
//		bgHandle[i]-> i
//		 HandleToIndex[bgHandleToIndex[bgHandle[i]] = i;
//		HandleToIndex[bgHandle[i]] = i;
//	}
//}
//
//MapChip::~MapChip()
//{
//	for (int i = 0; i < MAP_CHIP_WIDTH * MAP_CHIP_HEIGHT; i++)
//	{
//		if (bgHandle[i] != -1)
//		{
//			DeleteGraph(bgHandle[i]);
//			bgHandle[i] = -1;
//		}
//	}
//}
//
//void MapChip::Update()
//{
//	Point mousePos;
//	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1)
//	{
//		return;
//	}
//	isInMapChipArea_ = (mousePos.x > Screen::WIDTH - MAP_CHIP_WIN_WIDTH &&
//		mousePos.x < Screen::WIDTH && mousePos.y > 0 && mousePos.y < MAP_CHIP_WIN_HEIGHT);
//
//	if (isInMapChipArea_)
//	{
//		
//		selected_.x = (mousePos.x - (Screen::WIDTH - MAP_CHIP_WIN_WIDTH)) / IMAGE_SIZE;
//		selected_.y = mousePos.y / IMAGE_SIZE;
//		 if(Input::IsButtonDown(MOUSE_INPUT_LEFT))
//		 {
//		
//		   isHold_ = true;
//		   selectedIndex_ = bgHandle[selected_.y *  MAP_CHIP_NUM_X + selected_.x];
//		 }
//		
//	}
//	else
//	{
//		isInMapChipArea_ = false;
//	}
//	
// 
//}
//
//void MapChip::Draw()
//{
//	int TOPLEFT_X = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
//	int TOPLEFT_Y = 0;
//	int RIGHTBOTTOM_X = Screen::WIDTH;
//	int RIGHTBOTTOM_Y = MAP_CHIP_WIN_HEIGHT;
//	for (int i = 0; i < MAP_CHIP_NUM_X; i++) //たて
//	{
//		for (int j = 0; j < MAP_CHIP_NUM_Y; j++) //よこ
//		{
//			//mapを作る画像の描画
//			DrawGraph(TOPLEFT_X + i * IMAGE_SIZE, TOPLEFT_Y + j * IMAGE_SIZE,
//				bgHandle[ i  + j * MAP_CHIP_NUM_X], TRUE);
//		}
//		
//	}
//	
//	if (isInMapChipArea_)
//	{
//		/*SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
//		DrawBox(TOPLEFT_X, TOPLEFT_Y, RIGHTBOTTOM_X, RIGHTBOTTOM_Y, GetColor(132,255,193), TRUE);
//		
//		DrawBox(TOPLEFT_X + selected_.x * IMAGE_SIZE,selected_.y * IMAGE_SIZE,
//			   TOPLEFT_X+ selected_.x* IMAGE_SIZE + IMAGE_SIZE,selected_.y * IMAGE_SIZE + IMAGE_SIZE,(132,255,193), TRUE);
//		
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
//		
//		DrawBox(TOPLEFT_X + selected_.x * IMAGE_SIZE, selected_.y * IMAGE_SIZE,
//			    TOPLEFT_X + selected_.x * IMAGE_SIZE + IMAGE_SIZE,selected_.y * IMAGE_SIZE + IMAGE_SIZE,GetColor(255, 0, 0), FALSE,2);*/
//		
//
//		int xM = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
//
//
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
//		DrawBox(xM + selected_.x * IMAGE_SIZE + 1, selected_.y * IMAGE_SIZE - 1,
//			xM + (selected_.x + 1) * IMAGE_SIZE - 1,
//			(selected_.y + 1) * IMAGE_SIZE + 1,
//			GetColor(255, 255, 0), TRUE);
//		
//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//		
//		DrawBox(xM + selected_.x * IMAGE_SIZE, selected_.y * IMAGE_SIZE,
//			xM + (selected_.x + 1) * IMAGE_SIZE, (selected_.y + 1) * IMAGE_SIZE,
//			GetColor(255, 0, 0), FALSE, 2);
//	}
//	if (isHold_)
//	{
//		Point mousePos;
//		if (GetMousePoint(&mousePos.x, &mousePos.y) != -1)
//		{
//			DrawExtendGraph(mousePos.x, mousePos.y, 
//				mousePos.x + IMAGE_SIZE, mousePos.y + IMAGE_SIZE, selectedIndex_, TRUE);
//		}
//		if (Input::IsButtonUP(MOUSE_INPUT_RIGHT))
//		{
//			isHold_ = false;
//			selectedIndex_ = -1;
//		}
//	}
//	
//	//mapEditの赤い枠
//	DrawBox(TOPLEFT_X, TOPLEFT_Y, RIGHTBOTTOM_X, RIGHTBOTTOM_Y, GetColor(255, 0, 0), FALSE,3);
//	
//	int TOPLEFT_X = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
//	int TOPLEFT_Y = 0;
//	int RIGHTBOTTOM_X = Screen::WIDTH;
//	int RIGHTBOTTOM_Y = MAP_CHIP_WIN_HEIGHT;
//
//	for (int i = 0; i < MAP_CHIP_NUM_X; i++) {
//		for (int j = 0; j < MAP_CHIP_NUM_Y; j++) {
//			DrawGraph(TOPLEFT_X + i * IMAGE_SIZE, TOPLEFT_Y + j * IMAGE_SIZE,
//				bgHandle[i + j * MAP_CHIP_NUM_X], TRUE);
//
//		}
//	}
//
//	if (isInMapChipArea_)
//	{
//		int xM = Screen::WIDTH - MAP_CHIP_WIN_WIDTH;
//		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
//
//		DrawBox(xM + selected_.x * IMAGE_SIZE + 1, selected_.y * IMAGE_SIZE - 1,
//			xM + (selected_.x + 1) * IMAGE_SIZE - 1, (selected_.y + 1) * IMAGE_SIZE + 1,
//			GetColor(255, 255, 0), TRUE);
//
//		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//		
//		DrawBox(xM + selected_.x * IMAGE_SIZE, selected_.y * IMAGE_SIZE,
//			xM + (selected_.x + 1) * IMAGE_SIZE, (selected_.y + 1) * IMAGE_SIZE,
//			GetColor(255, 0, 0), FALSE, 2);
//	}
//	if (isHold_)
//	{
//		Point mousePos;
//		if (GetMousePoint(&mousePos.x, &mousePos.y) != -1)
//		{
//			DrawExtendGraph(mousePos.x, mousePos.y,
//				mousePos.x + IMAGE_SIZE, mousePos.y + IMAGE_SIZE, selectedIndex_, TRUE);
//		}
//		if (Input::IsButtonUP(MOUSE_INPUT_RIGHT))
//		{
//			isHold_ = false; //マウスのボタンが離されたら持っている状態を解除
//			selectedIndex_ = -1; //選択したインデックスをリセット
//		}
//	}
//
//}
//
//bool MapChip::IsHold()
//{
//	return isHold_;
//}
//
//bool MapChip::GetHoldImage()
//{
//	if (isHold_)
//	{
//		return selectedIndex_;
//	}
//	else
//	{
//		return -1;
//	}
//}
namespace
{
	////同じ名前の変数はあとでまとめましょう
	//const int IMAGE_SIZE = { 32 }; // 画像のサイズ
	//const int MAP_CHIP_WIDTH = { 16 };//チップの横並び数
	//const int MAP_CHIP_HEIGHT = { 12 };//チップの縦並び数
	//const int MAP_CHIP_NUM_X = { 8 };//マップチップウィンドウの横並び数
	//const int MAP_CHIP_NUM_Y = { 24 };//マップチップウィンドウの縦並び数
	//const int MAP_CHIP_WIN_WIDTH = { IMAGE_SIZE * MAP_CHIP_NUM_X };//ウィンドウの横幅
	//const int MAP_CHIP_WIN_HEIGHT = { IMAGE_SIZE * MAP_CHIP_NUM_Y };//ウィンドウの縦幅

	//// ドラッグ開始と判定する移動量の閾値
	//const int DRAG_THRESHOLD = 5;

	/*
	int TILE_PIX_SIZE;//1タイルのピクセルサイズ
	int TILE_X;       //マップチップシートのマップチップの横並び数
	int TILE_Y;       //縦並び数
	int MAPCHIP_VIEW_X;
	int MAPCHIP_VIEW_Y;
	int MAPCHIP_WIN_WIDTH;
	int MAPCHIP_WIN_HEIGHT;
	*/
}

MapChip::MapChip()
	: GameObject(),cfg_(GetMapChipConfig()), isUpdate_(false), isInMapChipArea_(false), selectedIndex_(-1)
	, bgHandle(cfg_.TILE_X* cfg_.TILE_Y, -1), selected_({ 0,0 }), isHold_(false), ScrollOffset_({0,0}) //初期値を-1で16*12の配列を初期化する
{    
	

	    LoadDivGraph("./bg.png", cfg_.TILE_X * cfg_.TILE_Y,
			          cfg_.TILE_X, cfg_.TILE_Y,
			          cfg_.TILE_PIX_SIZE, cfg_.TILE_PIX_SIZE, bgHandle.data());
	//for (int i = 0; i < MAP_CHIP_NUM_X; i++) {
	//	for (int j = 0; j < MAP_CHIP_NUM_Y; j++) {
	//		Rect tmp{
	//			i * IMAGE_SIZE, j * IMAGE_SIZE,
	//			IMAGE_SIZE, IMAGE_SIZE
	//		};
	//		//bgRects_.push_back(tmp);
	//	}
	//}

	//LUT(Look Up Table) 作成
	for (int i = 0; i < bgHandle.size(); i++)
	{
		HandleToIndex[bgHandle[i]] = i;
	}
}


MapChip::~MapChip()
{
	for (int i = 0; i < cfg_.TILE_X * cfg_.TILE_Y; i++) {
		if (bgHandle[i] != -1) {
			DeleteGraph(bgHandle[i]);
			bgHandle[i] = -1;
		}
	}
}

Point MapChip::GetViewOrigin() const
{
	return {Screen::WIDTH - cfg_.MAPCHIP_WIN_WIDTH,0};
}

bool MapChip::IsInMapChipArea(const Point& mouse) const
{
	/*return (mouse.x > GetViewOrigin().x && mouse.x < Screen::WIDTH 
		&&  mouse.y > GetViewOrigin().y && mouse.y < Screen::HEIGHT);*/

	
	   return (mouse.x >= GetViewOrigin().x &&
		mouse.x < Screen::WIDTH &&
		mouse.y >= 0 &&
		mouse.y < cfg_.MAPCHIP_WIN_HEIGHT);
	
}

Point MapChip::ScreenToChip(const Point& mouse) const
{
	int localX = (mouse.x - GetViewOrigin().x) / cfg_.TILE_PIX_SIZE;
	int localY = mouse.y / cfg_.TILE_PIX_SIZE;
	return { localX,localY };
}


void MapChip::Update()
{



	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1) {
		return;
	}

	isInMapChipArea_ = IsInMapChipArea(mousePos);


	//mapChipをとってくる
	if (isInMapChipArea_) {
		if (Input::IsKeyDown(KEY_INPUT_LEFT))
		{
			
			ScrollOffset_.x = std::min(std::max(cfg_.MAPCHIP_VIEW_X, cfg_.TILE_X - cfg_.MAPCHIP_VIEW_X), ScrollOffset_.x + 1);
			//ScrollOffset_.x = std::min(std::max(0, cfg_.TILE_X - cfg_.MAPCHIP_VIEW_X), ScrollOffset_.x + 1);
			//ScrollOffset_.x = ScrollOffset_.x + 1;
		}
		if (Input::IsKeyDown(KEY_INPUT_RIGHT))
		{
			ScrollOffset_.x  = std::max(0, ScrollOffset_.x - 1);
			//ScrollOffset_.x = ScrollOffset_.x - 1;
		}
		selected_ = ScreenToChip(mousePos);
		int index = selected_.y * cfg_.TILE_X + selected_.x;
		if (Input::IsButtonDown(MOUSE_INPUT_LEFT))
		{
			isHold_ = true;
			selectedIndex_ = bgHandle[index];
		}
	}
	else
	{
		isInMapChipArea_ = false;
	}


}

void MapChip::Draw()
{
	//マップチップ領域表示
	for (int i = 0; i < cfg_.TILE_X; i++)
	{
		for (int j = 0; j < cfg_.TILE_Y; j++)
		{
			int index = i +  ScrollOffset_.x + j * cfg_.TILE_X;
			if (index < 0)
			{
				continue;
			}
			DrawGraph(GetViewOrigin().x + i * cfg_.TILE_PIX_SIZE,
				      GetViewOrigin().y + j * cfg_.TILE_PIX_SIZE,bgHandle[index], TRUE);

		}
	}
	//マップチップの選択範囲をハイライト表示
	if (isInMapChipArea_)
	{
		int px = GetViewOrigin().x + selected_.x * cfg_.TILE_PIX_SIZE;
		int py = selected_.y * cfg_.TILE_PIX_SIZE;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		
		DrawBox(px, py,
		     px +  cfg_.TILE_PIX_SIZE - 1, py + cfg_.TILE_PIX_SIZE + 1,
			GetColor(255, 255, 0), TRUE);
		
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		
		DrawBox(px,py,px +cfg_.TILE_PIX_SIZE - 1 ,py + cfg_.TILE_PIX_SIZE + 1,
			GetColor(255, 0, 0), FALSE, 2);
	}
	//ホールド中のマップチップの描画
	if (isHold_)
	{
		Point mousePos;
		if (GetMousePoint(&mousePos.x, &mousePos.y) != -1)
		{
			DrawExtendGraph(mousePos.x, mousePos.y,
				mousePos.x + cfg_.TILE_PIX_SIZE, mousePos.y + cfg_.TILE_PIX_SIZE, selectedIndex_, TRUE);
		}
		if (Input::IsButtonUP(MOUSE_INPUT_RIGHT))
		{
			isHold_ = false; //マウスのボタンが離されたら持っている状態を解除
			selectedIndex_ = -1; //選択したインデックスをリセット
		}
	}

}

bool MapChip::IsHold()
{
	return isHold_;
}

int MapChip::GetHoldImage()
{
	if (isHold_)
	{
		return selectedIndex_;
	}
	else
	{
		return -1; //持っていない場合は-1を返す
	}
}
int MapChip::GetChipIndex(int handle)
{
	return HandleToIndex[handle];
	
}

