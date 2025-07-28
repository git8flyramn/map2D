#include <windows.h>
#include "MapEdit.h"
#include <cassert>
#include "Input.h"
#include "DxLib.h"
#include "MapChip.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "ImGui/imgui.h"

MapEdit::MapEdit()
	:GameObject(),Ecfg_(GetMapEditConfig()), myMap_(Ecfg_.MAP_WIDTH* Ecfg_.MAP_HEIGHT, -1), //初期値を-1で20*20の配列を初期化する
	isInMapEditArea_(false) //マップエディタ領域内にいるかどうか
{
	mapEditRect_ = { Ecfg_.LEFT_MARGIN, Ecfg_.TOP_MARGIN,
		 Ecfg_.MAP_WIDTH * Ecfg_.MAP_IMAGE_SIZE, Ecfg_.MAP_HEIGHT * Ecfg_.MAP_IMAGE_SIZE };
}

MapEdit::~MapEdit()
{
}

void MapEdit::SetMap(Point p, int value)
{
	//マップの座標pにvalueをセットする
	//pが、配列の範囲外の時はassertにひっかかる
	assert(p.x >= 0 && p.x < Ecfg_.MAP_WIDTH);
	assert(p.y >= 0 && p.y < Ecfg_.MAP_HEIGHT);
	myMap_[p.y * Ecfg_.MAP_WIDTH + p.x] = value; //y行x列にvalueをセットする

}

int MapEdit::GetMap(Point p) const
{
	//マップの座標pの値を取得する
	//pが、配列の範囲外の時はassertにひっかかる
	assert(p.x >= 0 && p.x < Ecfg_.MAP_WIDTH);
	assert(p.y >= 0 && p.y < Ecfg_.MAP_HEIGHT);
	return myMap_[p.y * Ecfg_.MAP_WIDTH + p.x]; //y行x列の値を取得する

}

void MapEdit::Update()
{
	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1) {
		return;
	}
	// マウスの座標がマップエディタ領域内にいるかどうかを判定する
	isInMapEditArea_ = mousePos.x >= mapEditRect_.x && mousePos.x <= mapEditRect_.x + mapEditRect_.w &&
		               mousePos.y >= mapEditRect_.y && mousePos.y <= mapEditRect_.y + mapEditRect_.h;

	
	if (!isInMapEditArea_) {
		return; //マップエディタ領域外なら何もしない
	}

	int gridX = (mousePos.x - Ecfg_.LEFT_MARGIN) / Ecfg_.MAP_IMAGE_SIZE;
	int gridY = (mousePos.y - Ecfg_.TOP_MARGIN) / Ecfg_.MAP_IMAGE_SIZE;

	drawAreaRect_ = { Ecfg_.LEFT_MARGIN + gridX * Ecfg_.MAP_IMAGE_SIZE,  Ecfg_.TOP_MARGIN + gridY * Ecfg_.MAP_IMAGE_SIZE,
		 Ecfg_.MAP_IMAGE_SIZE,  Ecfg_.MAP_IMAGE_SIZE };

	//マウスのボタンが押されたら、持ってる画像をその座標に貼る
	//if (Input::IsButtonDown(MOUSE_INPUT_LEFT)) //左クリックでマップに値をセット
	//{
	//	MapChip* mapChip = FindGameObject<MapChip>();

	//	if (CheckHitKey(KEY_INPUT_LSHIFT)) //Rキーを押しているなら
	//	{
	//		SetMap({ gridX, gridY }, -1); //マップに値をセット（-1は何もない状態）
	//		return; //マップチップを削除したらここで終了
	//	}
	//	else if (mapChip && mapChip->IsHold()) //マップチップを持っているなら
	//	{
	//		SetMap({ gridX, gridY }, mapChip->GetHoldImage()); //マップに値をセット
	//	}
	//}

	if (Input::IsButtonKeep(MOUSE_INPUT_LEFT)) //左クリックでマップに値をセット
	{
		MapChip* mapChip = FindGameObject<MapChip>();

		if (CheckHitKey(KEY_INPUT_LSHIFT)) //Rキーを押しているなら
		{
			SetMap({ gridX, gridY }, -1); 
			return; 
		}
		else if (mapChip && mapChip->IsHold()) //マップチップを持っているなら
		{
			SetMap({ gridX, gridY }, mapChip->GetHoldImage()); //マップに値をセット
		}
	}
	if (Input::IsKeyDown(KEY_INPUT_S))
	{
		SaveMapData();
	}
	if (Input::IsKeyDown(KEY_INPUT_L))
	{
		LoadMapData();
	}
	//マップエディットの拡大
	if (Input::IsKeyDown(KEY_INPUT_A))
	{
		Down_Scale_Resize -= 10;
		UP_Scale_Resize += 10;
	}
	//マップエディットの縮小
	if (Input::IsKeyDown(KEY_INPUT_D))
	{
		UP_Scale_Resize -= 10;
		Down_Scale_Resize += 10;
	}
}

void MapEdit::Draw()
{//背景を描画する

	for (int j = 0; j < Ecfg_.MAP_HEIGHT; j++)
	{
		for (int i = 0; i < Ecfg_.MAP_WIDTH; i++)
		{
			int value = GetMap({ i,j });
			if (value != -1) //-1なら何も描画しない
			{
				DrawGraph(Ecfg_.LEFT_MARGIN + i * Ecfg_.MAP_IMAGE_SIZE + UP_Scale_Resize, Ecfg_.TOP_MARGIN + j * Ecfg_.MAP_IMAGE_SIZE + UP_Scale_Resize,
					value, TRUE);
			}
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	DrawBox(Ecfg_.LEFT_MARGIN + 0 + Down_Scale_Resize, Ecfg_.TOP_MARGIN + 0 + Down_Scale_Resize,
            Ecfg_.LEFT_MARGIN + Ecfg_.MAP_WIDTH * Ecfg_.MAP_IMAGE_SIZE + UP_Scale_Resize,
            Ecfg_.TOP_MARGIN + Ecfg_.MAP_HEIGHT * Ecfg_.MAP_IMAGE_SIZE + UP_Scale_Resize, GetColor(255, 255, 0), FALSE);

	for (int j = 0; j < Ecfg_.MAP_HEIGHT; j++) {
		for (int i = 0; i < Ecfg_.MAP_WIDTH; i++) {
			 //横線の描画
			DrawLine(Ecfg_.LEFT_MARGIN + i * Ecfg_.MAP_IMAGE_SIZE + Down_Scale_Resize,
				Ecfg_.TOP_MARGIN + j * Ecfg_.MAP_IMAGE_SIZE  ,
				Ecfg_.LEFT_MARGIN + (i + 1) * Ecfg_.MAP_IMAGE_SIZE + UP_Scale_Resize,
				Ecfg_.TOP_MARGIN + j * Ecfg_.MAP_IMAGE_SIZE,
				GetColor(255, 255, 255), 1);
			
			//縦線の描画
			DrawLine(Ecfg_.LEFT_MARGIN + i * Ecfg_.MAP_IMAGE_SIZE,
				Ecfg_.TOP_MARGIN + j * Ecfg_.MAP_IMAGE_SIZE + Down_Scale_Resize,
				Ecfg_.LEFT_MARGIN + i * Ecfg_.MAP_IMAGE_SIZE ,
				Ecfg_.TOP_MARGIN + (j + 1) * Ecfg_.MAP_IMAGE_SIZE + UP_Scale_Resize,
				GetColor(255, 255, 255), 1);
		}
	}
	if (isInMapEditArea_) {

		DrawBox(drawAreaRect_.x, drawAreaRect_.y,
			drawAreaRect_.x + drawAreaRect_.w, drawAreaRect_.y + drawAreaRect_.h,
			GetColor(255, 255, 0), TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);



}

void MapEdit::SaveMapData()
{
	////ファイル選択ダイアログを出す
	//TCHAR filename[255] = "";
	//OPENFILENAME ofn = { 0 };

	//ofn.lStructSize = sizeof(ofn);
	////ウィンドウのオーナー = 親ウィンドウのハンドル
	//ofn.hwndOwner = GetMainWindowHandle();
	//ofn.lpstrFilter = "全てのファイル (*.*)\0*.*\0";
	//ofn.lpstrFile = filename;
	//ofn.nMaxFile = 255;
	//ofn.Flags = OFN_OVERWRITEPROMPT;

	//if (GetSaveFileName(&ofn))
	//{
	//	printfDx("ファイルが選択された");
	//	//ファイルを開いてセーブ
	//	std::ofstream openfile(filename);
	//	openfile << "#TinyMapData\n";
	//	
	//	MapChip* mc = FindGameObject<MapChip>();
	//
	//	for (int j = 0; j < MAP_HEIGHT; j++)
	//	{
	//		for (int i = 0; i < MAP_WIDTH; i++)
	//		{

	//			int index;
	//			if (myMap_[j * MAP_WIDTH + i] != -1)
	//				index = mc->GetChipIndex(myMap_[j * MAP_WIDTH + i]);
	//			else
	//				index = -1;
	//			if (i == MAP_WIDTH - 1)
	//			{
	//				openfile << index;
	//			}
	//			else
	//			{
	//				openfile << index << ',';
	//			}
	//		}
	//		openfile << std::endl;
	//	}
	//	openfile.close();
	//	printfDx("file Saved\n");
	//}

	//頑張ってファイル選択ダイアログを出す回
	TCHAR filename[255] = "";
	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(ofn);
	//ウィンドウのオーナー＝親ウィンドウのハンドル
	ofn.hwndOwner = GetMainWindowHandle();
	ofn.lpstrFilter = "全てのファイル (*.*)\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = 255;
	ofn.Flags = OFN_OVERWRITEPROMPT;


	if (GetSaveFileName(&ofn))
	{
		printfDx("ファイルが選択された\n");
		//ファイルを開いて、セーブ
		//std::filesystem ファイル名だけ取り出す
		//ofstreamを開く
		std::ofstream openfile(filename);
		//ファイルの選択がキャンセル
		//printfDx("セーブがキャンセル\n");
		openfile << "#TinyMapData\n";

		MapChip* mc = FindGameObject<MapChip>();

		for (int j = 0; j < Ecfg_.MAP_HEIGHT; j++) {
			for (int i = 0; i < Ecfg_.MAP_WIDTH; i++) {

				int index;
				if (myMap_[j * Ecfg_.MAP_WIDTH + i] != -1)
					index = mc->GetChipIndex(myMap_[j * Ecfg_.MAP_WIDTH + i]);
				else
					index = -1;

				if (i == Ecfg_.MAP_WIDTH - 1) //最後の要素なら改行しない
				{
					openfile << index; //最後の要素はカンマをつけない
				}
				else
				{
					//最後の要素以外はカンマをつける
					openfile << index << ",";
				}
			}
			openfile << std::endl;
		}
		openfile.close();
		printfDx("File Saved!!!\n");
	}
		/*for (int j = 0; j < MAP_HEIGHT; j++)
		{
			for (int i = 0; i < MAP_WIDTH; i++)
			{

				int index;
				if (myMap_[j * MAP_WIDTH + i] != -1)
					index = mc->GetChipIndex(myMap_[i * MAP_WIDTH + j]);
				else
					index = -1;
				flie << index << "";
			}
			flie << std::endl;
		}
		flie.close();
		printfDx("file Saved\n");*/	/*printfDx("file Saved\n");
	std::ofstream flie("data.dat");
	flie << "#TinyMapData\n";
	MapChip* mc = FindGameObject<MapChip>();
	flie << " #header" << "\n" << "WIDTH 20" << "\n" << "HEIGHT 20" << "\n";
	flie << "#data" << std::endl;

	for (int j = 0; j < MAP_HEIGHT; j++)
	{
		for (int i = 0; i < MAP_WIDTH; i++)
		{

			int index;
			if (myMap_[j * MAP_WIDTH + i] != -1)
				index = mc->GetChipIndex(myMap_[i * MAP_WIDTH + j]);
			else
			index = -1;
			flie << index << ",";
		}
		flie << std::endl;
	}
	flie.close();
	printfDx("file Saved\n");*/
}
	


void MapEdit::LoadMapData()
{
	//ファイル選択ダイアログを出す
	TCHAR filename[255] = "";
	OPENFILENAME ifn = { 0 };

	ifn.lStructSize = sizeof(ifn);
	//ウィンドウのオーナー = 親ウィンドウのハンドル
	ifn.hwndOwner = GetMainWindowHandle();
	ifn.lpstrFilter = "全てのファイル (*.*)\0*.*\0";
	ifn.lpstrFile = filename;
	ifn.nMaxFile = 255;
	//ifn.Flags = OFN_OVERWRITEPROMPT;
	
	

	//printfDx("ファイルが読み込まれた");
	//GetOpenFileName()
	if (GetOpenFileName(&ifn))
	{
		printfDx("ファイルが選択された->%s",filename);
		//ファイルを開いてセーブ
		//std::filesystem ファイル名だけ取り出す
	    //ifstreamを開く input file name
		std::ifstream inputfile(filename);
		//ファイルがオープンしたかどうかはチェックが必要
		std::string line;

		//mapChipの情報
		MapChip* mc = FindGameObject<MapChip>();
		myMap_.clear();//マップを空に
		while (std::getline(inputfile,line))
		{
			if (line.empty()) continue;
			//読み込みの処理を書いていく
			if (line[0]!= '#')
			{
				std::istringstream iss(line);
				std::string tmp;//これに一個ずつ読み込む
				while (getline(iss, tmp, ',')) {
					/*if (tmp == -1)
						myMap_.push_back(-1);
					else
						myMap_.push_back(mc->GetHandle(tmp));*/

					printfDx("%s", tmp.c_str());
					if (tmp == "-1")
					{
						myMap_.push_back(-1);
					}
					else
					{
						int index = std::stoi(tmp);
						int handle = mc->GetHandle(index);
						myMap_.push_back(handle);
					}
				}
			}
			/*else
			{
				MessageBox(nullptr, "画像の読み込みに失敗しました", "読み込みエラー", MB_OK | MB_ICONWARNING);
			}*/
			printfDx("\n");
		}
	}
	else
	{
		//ファイルの選択がキャンセル
		printfDx("セーブがキャンセル\n");
	}
}
