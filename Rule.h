//======================================================================================
//ルール基本処理.h[Rule.h]
//date:2021/07/13  name:Kazuki Wada
//======================================================================================
#ifndef RULE_H_
#define RULE_H_

#include "Scene.h"
class Rule : public Scene
{
private:
	float fadein;
	bool isUse;
	bool isVisible;
	float alfa;
	float a;
public:
	void Init();   //初期化
	void UnInit(); //終了
	void Update(); //更新
	void Draw();   //描画
};

#endif // !RULE_H_
