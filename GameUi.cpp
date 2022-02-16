//=================================================================================================
//ゲームのUIをまとめる.cpp
//date:2021/11/10   name:Kazuki Wada
//=================================================================================================

#include "GameUi.h"
#include "HpBar.h"
#include "EmptyHeart.h"
#include "WeaponUi.h"
#include "Poison.h"
#include "DamageUi.h"
#include "Confusion.h"
#include "ChargeUi.h"

//---------------
//グローバル変数
//---------------
HpBar     g_Hp;	      //体力バー
EmtyHeart g_Empty;    //空の体力バー
WeaponUi  g_Weapon;   //武器UI
Poison    g_Poison;   //毒用
DamageUi  g_Damage;	  //ダメージUI
Confusion g_Confusion;//混乱テクスチャー
ChargeUi  g_ChargeBar;//チャージバー用

void GameUi_Init()
{
	g_Hp.Init();
	g_Empty.Init();
	g_Weapon.Init();
	g_Poison.Init();
	g_Damage.Init();
	g_Confusion.Init();
	g_ChargeBar.Init();
}

void GameUi_UnInit()
{
	g_ChargeBar.UnInit();
	g_Confusion.UnInit();
	g_Damage.UnInit();
	g_Poison.UnInit();
	g_Weapon.UnInit();
	g_Empty.UnInit();
	g_Hp.UnInit();
}

void GameUi_Update()
{
	
	g_Empty.Update();
	g_Hp.Update();
	g_Weapon.Update();
	g_Poison.Update();
	g_Damage.Update();
	g_Confusion.Update();
	g_ChargeBar.Update();
}

void GameUi_Draw()
{
	
	g_Empty.Draw();
	g_Hp.Draw();
	g_Weapon.Draw();
	g_Poison.Draw();
	g_Damage.Draw();
	g_Confusion.Draw();
	g_ChargeBar.Draw();
}
