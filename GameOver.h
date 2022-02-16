//================================================================================================================
//ゲームオーバー基本処理.h[GameOver.h]
//date:2022/02/01         name:Kazuki Wada
//================================================================================================================

#ifndef GAMEOVER_H_
#define GAMEOVER_H_

#include "Scene.h"

class  GameOver : public Scene
{
private:
	bool  m_isChange;//チェンジフラグ
	bool  m_isUse;	 //
	float m_alfa;    //アルファ値
	float m_Var;  //α変換値用
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
};

#endif // !GAMEOVER_H_
