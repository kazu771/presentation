//=======================================================================================
//Explaine基本処理.h[Explain.h]
//date:2021/08/28   name:Kazuki Wada
//=======================================================================================
#ifndef EXPLAINE_H_
#define EXPLAINE_H_

#include "Scene.h"
class Explaine : public Scene
{
private:
	float fadein;
	bool isUse;
	bool isVisible;
	float a;
	float alfa;
public:
	void Init();   //初期化
	void UnInit(); //終了
	void Update(); //更新
	void Draw();   //描画
};
#endif // !EXPLAINE_H_
