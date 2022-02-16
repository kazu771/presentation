//=================================================================================================
//リザルト基本処理.h[Result.h]
//date:2021/07/08   name:Kazuki Wada
//=================================================================================================
#ifndef RESULT_H_
#define RESULT_H_

#include "Scene.h"

class Result : public Scene
{

public:
	void Init();   //初期化
	void UnInit(); //終了
	void Update(); //更新
	void Draw();
	int Count;

private:
	float alfa;
	float a;
	float fadein;
	bool isUse;
	bool isFade;

};

#endif // !RESULT_H_

