//====================================================================================================================
//����UI��{����.h
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

	void Init();  //������
	void UnInit(); //�I��
	void Update(); //�X�V
	void Draw();   //�`��
	void ChangeMode();//����̃^�C�v��ύX
private:
	WeaponMode m_mode;

};
#endif // !WEAPONUI_H_

#pragma once
