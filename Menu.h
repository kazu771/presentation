//======================================================================================
//menu基本処理.h[Menu.h]
//date:2021/07/12  name:Kazuki Wada
//======================================================================================
#ifndef MENU_H_
#define MENU_H_

#include "Scene.h"

//
//クラス定義
//
class Menu : public Scene
{
private:
	float x; //ポインター座標
	float fadein;
	bool isUse;
	bool isVisible;
public:

	void Init();   //初期化
	void UnInit(); //終了
	void Update(); //更新
	void Draw();   //描画	

};

#endif // !MENU_H_

