//====================================================================================================================
//武器UI基本処理.h
//date:2021/11/15    name:Kazuki Wada
//====================================================================================================================
#ifndef WEAPONUI_H_
#define WEAPONUI_H_

class WeaponUi
{
public:

	enum WeaponMode
	{
		WEAPONMODE_NORMAL = 0,
		WEAPONMODE_DOUBLE,
		WEAPONMODE_TWOWAY,
		WEAPONMODE_MAX
	};

	void Init();  //初期化
	void UnInit(); //終了
	void Update(); //更新
	void Draw();   //描画
	void ChangeMode();//武器のタイプを変更
private:
	WeaponMode m_mode;

};
#endif // !WEAPONUI_H_

#pragma once
