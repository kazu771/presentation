//=================================================================================================
//体力バーの基本処理.h
//date:2021/11/11   name:Kazuki Wada
//=================================================================================================

#ifndef HPBAR_H_
#define HPBAR_H_


class HpBar
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	bool HpFlug();//HPフラグを送る用
private:
	class Player* m_Player;
	class HpItem* m_Item;
	float m_Tx;			    //切り取りX座標
	float m_Ty;			    //切り取りY座標
	float m_Minus;
	float m_Frame;			//フレーム
	float m_isItem;			//アイテム取得用
	bool m_isShrink;		//ハート縮小用
	bool m_isCon;			//混乱フラグ
	bool m_isDeath;			//Deathフラグ
	int m_TexNumX;          //テクスチャーの横方向の数
	int m_TexNumY;			//テクスチャーの縦方向の数
	int m_Cnt;
};

#endif // !HPBAR_H_

#pragma once
