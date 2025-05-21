#pragma once
namespace Input {
	//�L�[�{�[�h�擾�֘A
	void KeyStateUpdate();
	bool IsKeyUP(int keyCode);
	bool IsKeyDown(int keyCode);
	int IsKeepKeyDown(int keyCode);

	bool IsMouseDown(); //�@�}�E�X�̃{�^���������ꂽ��
	bool IsMouseUP(); //
	bool IsMouseKeep();
	bool IsButtonDown(int button); //�{�^���������ꂽ�u��
	bool IsButtonUP(int button); //�{�^���������ꂽ�u��
	bool IsButtonKeep(int button);//�{�^���������ꑱ���Ă���
	//MOUSE_INPUT_LEFT = 0x0001
    //MOUSE_INPUT_MIDDLE = 0x0004
	//MOUSE_INPUT_RIGHT  = 0x0002

}
