//================================================================================================================
//ゲームクリア基本処理.h[Clear.h]
//date:2022/01/25         name:Kazuki Wada
//================================================================================================================
#ifndef CLEAR_H_
#define CLEAR_H_

#include "Scene.h"

//-------------
//クラス定義
//-------------

class Clear :public Scene
{
private:
	bool  m_isChange;//チェンジフラグ
	bool  m_isUse;	 //
	float m_alfa;    //アルファ値
	float m_Var;
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
};

#endif // !CLEAR_H_
