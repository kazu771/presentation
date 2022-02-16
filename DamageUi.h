//================================================================================================
//ダメージ用UI基本処理.h[DamageUi.h]
//date:2021/12/07      name:Kazuki Wada
//================================================================================================
#ifndef DAMAGEUI_H_
#define DAMAGEUI_H_


class DamageUi
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	void ChangePosion();//プレイヤー側で呼ぶ毒用関数
	void ChangeConfusion();//プレイヤー側で呼ぶ混乱用関数
	void SetPosition(float x, float y);

private:
	float m_Tx;//切り取りX座標
	float m_Ty;//切り取りY座標
	float m_PosX;
	float m_PosY;
	bool  m_Poison;//毒の弾があたったらtrue
	bool  m_Confusion;//混乱する弾が当たったらtrue
	int	  m_Cnt;//表示する時間
};


#endif // !DAMAGEUI_H_

