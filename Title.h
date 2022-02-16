//===================================================================================================================================
//タイトル基本処理.h[Title.h]
//date:2021/04/27   name;Kazuki Wada
//===================================================================================================================================
#ifndef TITLE_H_
#define TITLE_H_


#include "Scene.h"
#include "Titlelogo.h"
class Title: public Scene
{
private:
	bool isVisible;
	float fadein;
	float fade;
public:
	void Init();   //初期化
	void UnInit(); //終了
	void Update(); //更新
	void Draw();
	float alfa;
	float a;
	bool isUse;
};

#endif // !TITLE_H_