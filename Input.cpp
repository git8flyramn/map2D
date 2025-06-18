#include "Input.h"
#include "DxLib.h"

namespace Input {
	//�L�[�{�[�h�擾�֘A
	const int KEY_MAX = 255;
	char keyBuff[KEY_MAX];		//�L�[�o�b�t�@ (���t���[��)
	char keyBuffOld[KEY_MAX];	//1�O�̃L�[�o�b�t�@(�O�t���[��) 
	char key_down[KEY_MAX];		//�����ꂽ�u�� 
	char key_up[KEY_MAX];		//�����ꂽ�u�� 
	char Key_Keep[KEY_MAX];		//�������ςȂ�
	int mousePre = false;//�}�E�X�̑O�̃t���[�� previous
	int mouseNow = false;//���t���[���̃}�E�X���

}

void Input::KeyStateUpdate()
{
	memcpy_s(keyBuffOld, sizeof(char) * KEY_MAX, keyBuff, sizeof(char) * KEY_MAX);

	GetHitKeyStateAll(keyBuff);//�S�ẴL�[�̏�Ԃ��擾 

	for (int i = 0; i < KEY_MAX; i++)
	{
		if (keyBuff[i] && keyBuffOld[i]) Key_Keep[i]++;
		int key_xor = keyBuff[i] ^ keyBuffOld[i];	//�O�t���[���ƌ��t���[����xor
		if (key_xor) Key_Keep[i] = 0;
		key_down[i] = key_xor & keyBuff[i];		//�����ꂽ�u�� = (���t���[����key_xor��AND) 
		key_up[i] = key_xor & keyBuffOld[i];	//�����ꂽ�u�� = (�O�t���[����key_xor��AND) 
	}
	mousePre = mouseNow;  //�O�t���[���̏�Ԃ�ۑ�
	mouseNow = GetMouseInput(); //�}�E�X�̏�Ԃ��擾
}

// 0xAB8D 1010 1011 1000 1101     
//�e�r�b�g��true false�̃t���O�Ƃ��Ďg�� -> �r�b�g�t���O   
bool Input::IsKeyUP(int keyCode)
{
	return(key_up[keyCode]);
}

bool Input::IsKeyDown(int keyCode)
{
	return(key_down[keyCode]);
}

int Input::IsKeepKeyDown(int keyCode)
{
	return(Key_Keep[keyCode]);
}

//�}�E�X�̏�Ԃ��擾����֐��Q
//mouseNow,mousePre ==0 ������Ă��� != 0�͉�����Ă��Ȃ�

bool Input::IsMouseDown()
{
	
	return(mouseNow == 1 && mousePre == 0);
}

bool Input::IsMouseUP()
{
	return (mouseNow == 0 && mousePre == 1);
}

bool Input::IsMouseKeep()
{
	return (mouseNow == 1 && mousePre == 1);
}

bool Input::IsButtonDown(int button)
{

   return(((mousePre & button) == 0) && ((mouseNow & button) != 0));
}

bool Input::IsButtonUP(int button)
{
	return(((mousePre & button) != 0) && ((mouseNow & button) == 0));
}

bool Input::IsButtonKeep(int button)
{
	return((mousePre & button) != 0) && ((mouseNow & button) != 0);
}
