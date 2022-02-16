//====================================================================================================================
//状態異常（毒）基本処理.h[Poison.h]
//date:2021/11/18   name:Kazuki Wada
//====================================================================================================================
#include "State.h"

#ifndef POSION_H_
#define POISON_H_

class Poison
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	void Damege(int Dmage);
	void ChangePoison();    //毒の状態を変える
private:
	class Player* m_player; //プレイヤーの情報を受け取るよう
	float         m_tcx;    //切り取りx座標
	float         m_tcy;    //切り取りy座標
	float		  m_Alfa;
	bool		  m_isUse;
	int			  m_Cnt;    //毒のカウント
	int			  m_Damage;
	int			  m_Hps;
	void PoisonChange();    //フラグを変更する関数

};
#endif // !POSION_H_

#pragma once
