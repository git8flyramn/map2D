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
	:GameObject(),Ecfg_(GetMapEditConfig()), myMap_(Ecfg_.MAP_WIDTH* Ecfg_.MAP_HEIGHT, -1), //�����l��-1��20*20�̔z�������������
	isInMapEditArea_(false) //�}�b�v�G�f�B�^�̈���ɂ��邩�ǂ���
{
	mapEditRect_ = { Ecfg_.LEFT_MARGIN, Ecfg_.TOP_MARGIN,
		 Ecfg_.MAP_WIDTH * Ecfg_.MAP_IMAGE_SIZE, Ecfg_.MAP_HEIGHT * Ecfg_.MAP_IMAGE_SIZE };
}

MapEdit::~MapEdit()
{
}

void MapEdit::SetMap(Point p, int value)
{
	//�}�b�v�̍��Wp��value���Z�b�g����
	//p���A�z��͈̔͊O�̎���assert�ɂЂ�������
	assert(p.x >= 0 && p.x < Ecfg_.MAP_WIDTH);
	assert(p.y >= 0 && p.y < Ecfg_.MAP_HEIGHT);
	myMap_[p.y * Ecfg_.MAP_WIDTH + p.x] = value; //y�sx���value���Z�b�g����

}

int MapEdit::GetMap(Point p) const
{
	//�}�b�v�̍��Wp�̒l���擾����
	//p���A�z��͈̔͊O�̎���assert�ɂЂ�������
	assert(p.x >= 0 && p.x < Ecfg_.MAP_WIDTH);
	assert(p.y >= 0 && p.y < Ecfg_.MAP_HEIGHT);
	return myMap_[p.y * Ecfg_.MAP_WIDTH + p.x]; //y�sx��̒l���擾����

}

void MapEdit::Update()
{
	Point mousePos;
	if (GetMousePoint(&mousePos.x, &mousePos.y) == -1) {
		return;
	}
	// �}�E�X�̍��W���}�b�v�G�f�B�^�̈���ɂ��邩�ǂ����𔻒肷��
	isInMapEditArea_ = mousePos.x >= mapEditRect_.x && mousePos.x <= mapEditRect_.x + mapEditRect_.w &&
		               mousePos.y >= mapEditRect_.y && mousePos.y <= mapEditRect_.y + mapEditRect_.h;

	
	if (!isInMapEditArea_) {
		return; //�}�b�v�G�f�B�^�̈�O�Ȃ牽�����Ȃ�
	}

	int gridX = (mousePos.x - Ecfg_.LEFT_MARGIN) / Ecfg_.MAP_IMAGE_SIZE;
	int gridY = (mousePos.y - Ecfg_.TOP_MARGIN) / Ecfg_.MAP_IMAGE_SIZE;

	drawAreaRect_ = { Ecfg_.LEFT_MARGIN + gridX * Ecfg_.MAP_IMAGE_SIZE,  Ecfg_.TOP_MARGIN + gridY * Ecfg_.MAP_IMAGE_SIZE,
		 Ecfg_.MAP_IMAGE_SIZE,  Ecfg_.MAP_IMAGE_SIZE };

	//�}�E�X�̃{�^���������ꂽ��A�����Ă�摜�����̍��W�ɓ\��
	//if (Input::IsButtonDown(MOUSE_INPUT_LEFT)) //���N���b�N�Ń}�b�v�ɒl���Z�b�g
	//{
	//	MapChip* mapChip = FindGameObject<MapChip>();

	//	if (CheckHitKey(KEY_INPUT_LSHIFT)) //R�L�[�������Ă���Ȃ�
	//	{
	//		SetMap({ gridX, gridY }, -1); //�}�b�v�ɒl���Z�b�g�i-1�͉����Ȃ���ԁj
	//		return; //�}�b�v�`�b�v���폜�����炱���ŏI��
	//	}
	//	else if (mapChip && mapChip->IsHold()) //�}�b�v�`�b�v�������Ă���Ȃ�
	//	{
	//		SetMap({ gridX, gridY }, mapChip->GetHoldImage()); //�}�b�v�ɒl���Z�b�g
	//	}
	//}

	if (Input::IsButtonKeep(MOUSE_INPUT_LEFT)) //���N���b�N�Ń}�b�v�ɒl���Z�b�g
	{
		MapChip* mapChip = FindGameObject<MapChip>();

		if (CheckHitKey(KEY_INPUT_LSHIFT)) //R�L�[�������Ă���Ȃ�
		{
			SetMap({ gridX, gridY }, -1); 
			return; 
		}
		else if (mapChip && mapChip->IsHold()) //�}�b�v�`�b�v�������Ă���Ȃ�
		{
			SetMap({ gridX, gridY }, mapChip->GetHoldImage()); //�}�b�v�ɒl���Z�b�g
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
	//�}�b�v�G�f�B�b�g�̊g��
	if (Input::IsKeyDown(KEY_INPUT_A))
	{
		Down_Scale_Resize -= 10;
		UP_Scale_Resize += 10;
	}
	//�}�b�v�G�f�B�b�g�̏k��
	if (Input::IsKeyDown(KEY_INPUT_D))
	{
		UP_Scale_Resize -= 10;
		Down_Scale_Resize += 10;
	}
}

void MapEdit::Draw()
{//�w�i��`�悷��

	for (int j = 0; j < Ecfg_.MAP_HEIGHT; j++)
	{
		for (int i = 0; i < Ecfg_.MAP_WIDTH; i++)
		{
			int value = GetMap({ i,j });
			if (value != -1) //-1�Ȃ牽���`�悵�Ȃ�
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
			 //�����̕`��
			DrawLine(Ecfg_.LEFT_MARGIN + i * Ecfg_.MAP_IMAGE_SIZE + Down_Scale_Resize,
				Ecfg_.TOP_MARGIN + j * Ecfg_.MAP_IMAGE_SIZE  ,
				Ecfg_.LEFT_MARGIN + (i + 1) * Ecfg_.MAP_IMAGE_SIZE + UP_Scale_Resize,
				Ecfg_.TOP_MARGIN + j * Ecfg_.MAP_IMAGE_SIZE,
				GetColor(255, 255, 255), 1);
			
			//�c���̕`��
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
	////�t�@�C���I���_�C�A���O���o��
	//TCHAR filename[255] = "";
	//OPENFILENAME ofn = { 0 };

	//ofn.lStructSize = sizeof(ofn);
	////�E�B���h�E�̃I�[�i�[ = �e�E�B���h�E�̃n���h��
	//ofn.hwndOwner = GetMainWindowHandle();
	//ofn.lpstrFilter = "�S�Ẵt�@�C�� (*.*)\0*.*\0";
	//ofn.lpstrFile = filename;
	//ofn.nMaxFile = 255;
	//ofn.Flags = OFN_OVERWRITEPROMPT;

	//if (GetSaveFileName(&ofn))
	//{
	//	printfDx("�t�@�C�����I�����ꂽ");
	//	//�t�@�C�����J���ăZ�[�u
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

	//�撣���ăt�@�C���I���_�C�A���O���o����
	TCHAR filename[255] = "";
	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(ofn);
	//�E�B���h�E�̃I�[�i�[���e�E�B���h�E�̃n���h��
	ofn.hwndOwner = GetMainWindowHandle();
	ofn.lpstrFilter = "�S�Ẵt�@�C�� (*.*)\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = 255;
	ofn.Flags = OFN_OVERWRITEPROMPT;


	if (GetSaveFileName(&ofn))
	{
		printfDx("�t�@�C�����I�����ꂽ\n");
		//�t�@�C�����J���āA�Z�[�u
		//std::filesystem �t�@�C�����������o��
		//ofstream���J��
		std::ofstream openfile(filename);
		//�t�@�C���̑I�����L�����Z��
		//printfDx("�Z�[�u���L�����Z��\n");
		openfile << "#TinyMapData\n";

		MapChip* mc = FindGameObject<MapChip>();

		for (int j = 0; j < Ecfg_.MAP_HEIGHT; j++) {
			for (int i = 0; i < Ecfg_.MAP_WIDTH; i++) {

				int index;
				if (myMap_[j * Ecfg_.MAP_WIDTH + i] != -1)
					index = mc->GetChipIndex(myMap_[j * Ecfg_.MAP_WIDTH + i]);
				else
					index = -1;

				if (i == Ecfg_.MAP_WIDTH - 1) //�Ō�̗v�f�Ȃ���s���Ȃ�
				{
					openfile << index; //�Ō�̗v�f�̓J���}�����Ȃ�
				}
				else
				{
					//�Ō�̗v�f�ȊO�̓J���}������
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
	//�t�@�C���I���_�C�A���O���o��
	TCHAR filename[255] = "";
	OPENFILENAME ifn = { 0 };

	ifn.lStructSize = sizeof(ifn);
	//�E�B���h�E�̃I�[�i�[ = �e�E�B���h�E�̃n���h��
	ifn.hwndOwner = GetMainWindowHandle();
	ifn.lpstrFilter = "�S�Ẵt�@�C�� (*.*)\0*.*\0";
	ifn.lpstrFile = filename;
	ifn.nMaxFile = 255;
	//ifn.Flags = OFN_OVERWRITEPROMPT;
	
	

	//printfDx("�t�@�C�����ǂݍ��܂ꂽ");
	//GetOpenFileName()
	if (GetOpenFileName(&ifn))
	{
		printfDx("�t�@�C�����I�����ꂽ->%s",filename);
		//�t�@�C�����J���ăZ�[�u
		//std::filesystem �t�@�C�����������o��
	    //ifstream���J�� input file name
		std::ifstream inputfile(filename);
		//�t�@�C�����I�[�v���������ǂ����̓`�F�b�N���K�v
		std::string line;

		//mapChip�̏��
		MapChip* mc = FindGameObject<MapChip>();
		myMap_.clear();//�}�b�v�����
		while (std::getline(inputfile,line))
		{
			if (line.empty()) continue;
			//�ǂݍ��݂̏����������Ă���
			if (line[0]!= '#')
			{
				std::istringstream iss(line);
				std::string tmp;//����Ɉ���ǂݍ���
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
				MessageBox(nullptr, "�摜�̓ǂݍ��݂Ɏ��s���܂���", "�ǂݍ��݃G���[", MB_OK | MB_ICONWARNING);
			}*/
			printfDx("\n");
		}
	}
	else
	{
		//�t�@�C���̑I�����L�����Z��
		printfDx("�Z�[�u���L�����Z��\n");
	}
}
