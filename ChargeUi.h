//==================================================================================================================
//�`���[�WUI��{����.h[ChargeUi.h]
//date:2022/01/12   name:Kazuki Wada
//==================================================================================================================
#ifndef CHARGE_H_
#define CHARGE_H_

class ChargeUi
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:
	class Player* m_Player;
	bool		  m_IsCarges;//�v���C���[��c�^�[�W�ϐ����󂯎��悤
	float		  m_Extend;  //�L�΂�
	float		  m_PosX;
};


#endif // !CHARGE_H_
