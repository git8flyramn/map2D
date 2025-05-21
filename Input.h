#pragma once
namespace Input {
	//キーボード取得関連
	void KeyStateUpdate();
	bool IsKeyUP(int keyCode);
	bool IsKeyDown(int keyCode);
	int IsKeepKeyDown(int keyCode);

	bool IsMouseDown(); //　マウスのボタンが押された時
	bool IsMouseUP(); //
	bool IsMouseKeep();
	bool IsButtonDown(int button); //ボタンが押された瞬間
	bool IsButtonUP(int button); //ボタンが離された瞬間
	bool IsButtonKeep(int button);//ボタンが押され続いている
	//MOUSE_INPUT_LEFT = 0x0001
    //MOUSE_INPUT_MIDDLE = 0x0004
	//MOUSE_INPUT_RIGHT  = 0x0002

}
