//====================================================================================================================
//��Ԉُ�i�Łj��{����.h[Poison.h]
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
	void ChangePoison();    //�ł̏�Ԃ�ς���
private:
	class Player* m_player; //�v���C���[�̏����󂯎��悤
	float         m_tcx;    //�؂���x���W
	float         m_tcy;    //�؂���y���W
	float		  m_Alfa;
	bool		  m_isUse;
	int			  m_Cnt;    //�ł̃J�E���g
	int			  m_Damage;
	int			  m_Hps;
	void PoisonChange();    //�t���O��ύX����֐�

};
#endif // !POSION_H_

#pragma once
