//=================================================================================================
//�̗̓o�[�̊�{����.h
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
	bool HpFlug();//HP�t���O�𑗂�p
private:
	class Player* m_Player;
	class HpItem* m_Item;
	float m_Tx;			    //�؂���X���W
	float m_Ty;			    //�؂���Y���W
	float m_Minus;
	float m_Frame;			//�t���[��
	float m_isItem;			//�A�C�e���擾�p
	bool m_isShrink;		//�n�[�g�k���p
	bool m_isCon;			//�����t���O
	bool m_isDeath;			//Death�t���O
	int m_TexNumX;          //�e�N�X�`���[�̉������̐�
	int m_TexNumY;			//�e�N�X�`���[�̏c�����̐�
	int m_Cnt;
};

#endif // !HPBAR_H_

#pragma once
