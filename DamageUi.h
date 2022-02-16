//================================================================================================
//�_���[�W�pUI��{����.h[DamageUi.h]
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
	void ChangePosion();//�v���C���[���ŌĂԓŗp�֐�
	void ChangeConfusion();//�v���C���[���ŌĂԍ����p�֐�
	void SetPosition(float x, float y);

private:
	float m_Tx;//�؂���X���W
	float m_Ty;//�؂���Y���W
	float m_PosX;
	float m_PosY;
	bool  m_Poison;//�ł̒e������������true
	bool  m_Confusion;//��������e������������true
	int	  m_Cnt;//�\�����鎞��
};


#endif // !DAMAGEUI_H_

