//=============================================
//�G��{����.h[Enemy.h]
//date;2021/05/24
//============================================
#ifndef SPIDER_H_
#define SPIDER_H_

#include "GameObject.h"

//------------------------
//�萔��`
//------------------------


//------------------------
//�N���X��`
//------------------------

class Spider : public GameObject
{
public:
	enum ENEMYSTATE
	{
		STATE_WALK = 0,
		STATE_ATTACK,
		STATE_MAX,
	};
	void Init();
	void UnInit();
	void Update();
	void Draw();
	int  SetHp();

private:
	#define SPEED_MAX (1.0f)
	class AnimetionModel* m_Model;  //���f����ǂݍ��ނ��ߗp
	class BoxCollision*   m_Collision; //�R���W�����p
	ID3D11VertexShader*   m_VertexShader = NULL;
	ID3D11PixelShader*    m_PixelShader = NULL;
	ID3D11InputLayout*    m_VertexLayout = NULL;
	D3DXVECTOR3			  m_TargetPos; //�v���C���[�̈ʒu���W������悤
	D3DXVECTOR3			  m_Direction; //�v���C���[�̊p�x�����锠
	D3DXVECTOR3			  m_Site;      //�v���C���[�̌��Ă�������擾
	D3DXVECTOR3			  m_Cross;
	ENEMYSTATE			  m_State;     //�G�̃X�e�[�g�����锠
	float				  m_Angle;     //�p�x
	float				  m_Speed;     //����
	float				  m_playerposx;
	float				  m_playerposz;
	float				  HPs;
	bool			      m_IsAngle;
	bool				  m_IsEscape;   //������悤�̏���
	bool				  m_IsAttack;
	int					  m_Cnt;		//Idle�ł��鎞��
	int					  m_AttckCnt;
	int					  m_frame;      //�A�j���[�V�����p
	int					  m_EsCnt;
	void State();			            //�G�̍s������
	void Walk();
	void Attack();
	void CollisionCharge();             //�`���[�W�o���b�g�Ƃ̓����蔻��
	void CollisionBullet();
	void CollisionTwoWay();
};

#endif // !ENEMY_H_

