//=========================================================================================================
//混乱基本処理.h[Confusion.h]
//date:2021/11/30   name:Kauzki Wada
//=========================================================================================================

#ifndef CONFUSION_H_
#define CONFUSION_H_

class Confusion
{
public:
	void Change();
	bool State();//現在の状態を送る関数
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:
	bool          m_isConfusion;//混乱用変数
	class Player* m_player;//プレイヤーの大呂kを受け取るよう
	float		  m_Alfa;
};


#endif // !CONFUSION_H_

