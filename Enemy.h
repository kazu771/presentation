//=============================================
//�G��{����.h[Enemy.h]
//date;2021/05/24
//============================================
#ifndef ENEMY_H_
#define ENEMY_H_

#include "GameObject.h"

//------------------------
//�萔��`
//------------------------
#define ENEMY_MODELS (3)
#define SPEED_MAX (1.0f)

//------------------------
//�N���X��`
//------------------------

class Enemy : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:
	enum STATACE
	{
		STATACE_WALK = 0,
		STATACE_ATTACK,
		STATACE_MAX,
	};
	class AnimetionModel* m_Models;    //���f����ǂݍ��ނ��ߗp
	class BoxCollision*   m_Collision; //�R���W�����p
	ID3D11VertexShader*   m_VertexShader = NULL;
	ID3D11PixelShader*    m_PixelShader  = NULL;
	ID3D11InputLayout*    m_VertexLayout = NULL;
	D3DXVECTOR3           m_TargetPos; //�v���C���[�̈ʒu���W������悤
	D3DXVECTOR3           m_Direction; //�v���C���[�̊p�x�����锠
	D3DXVECTOR3           m_Cross;
	STATACE               m_State;	   //�G�̃X�e�[�g�����锠
	float                 m_Angle;	   //�p�x
	float                 m_Speed;	   //����
	float                 m_PlayerPosx;
	float                 m_PlayerPosz;
	float                 m_Hpss;
	bool                  m_IsAngle;
	bool                  m_IsAttack;
	bool                  m_IsEscape;  //������悤�̏���
	int                   HPs;
	int                   m_frame;	   //�A�j���[�V�����p
	int	                  m_Cnt;	   //Idle�ł��鎞��
	int	                  m_AttackCnt;
	void State();						//�G�̍s������
	void Walk();
	void Attack();
	

};

#endif // !ENEMY_H_

