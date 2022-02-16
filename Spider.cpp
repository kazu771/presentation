//=============================================
//�G��{����.cpp[Enemy.Cpp]
//date:2021/05/24   name;Kazuki Wada
//=============================================
#include <time.h>   // time()�֐��p
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "Spider.h"
#include "player.h"
#include "EnemyBullet.h"
#include "BoxCollision.h"
#include "input.h"
#include "MeshField.h"
#include "animationModel.h"
#include "Camera.h"
#include "Bullet.h"
#include "Explosion.h"
#include "TwoWayBullet.h"
#include "TwoWayBulletRight.h"
#include "PoisonBullet.h"
#include "ChargeBullet.h"
#include "StateBullet.h"
//������
void Spider::Init()
{
	m_Cnt = 10;
	m_AttckCnt = 0;
	m_Model = new AnimetionModel();
	
	m_Model->Load("asset\\model\\SpiderWalks.fbx"); //�{�[���Ȃǂ�ǂݍ��ނ��߂ɏ����Ă���
	m_Model->LoadAnimation("asset\\model\\SpiderWalks.fbx", "Walk");
	m_Model->LoadAnimation("asset\\model\\SpiderAttacks.fbx", "Attacks");
	m_State = ENEMYSTATE::STATE_WALK;
	m_Position = D3DXVECTOR3(0.0f, 0.5f, 5.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
	m_Site = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TargetPos = { 0.0f, 0.0f, 0.0f };

	m_Direction = { 0.0f, 0.0f, 0.0f };
	m_Angle = 0.0f;
	m_Speed = SPEED_MAX + 0.5f;
	m_IsAngle = false;
	m_IsAttack = false;
	HPs = 10.0f;
	m_EsCnt = 0;
	Scene* scene = Manager::GetScene();


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}

//�I��
void Spider::UnInit()
{
	m_Model->Unload();
	delete m_Model;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//�X�V
void Spider::Update()
{

	m_frame++;

	Player* p_player = Manager::GetScene()->GetGameObject<Player>(1);
	m_TargetPos = p_player->GetPosition();//�v���C���[�̍��W�̎擾
	m_Site = p_player->GetForward();
	


	//�G�ƃv���C���[�̋����̍������Z�o
	m_Direction.x = m_TargetPos.x - m_Position.x;
	m_Direction.z = m_TargetPos.z - m_Position.z;
	
	//���K��
	D3DXVec3Normalize(&m_Direction, &m_Direction);
	//�v���C���[�ƓG�̍��W�̍������Z�o
	m_Angle = atan2(fabsf(m_Position.z - m_TargetPos.z), fabsf(m_Position.x - m_TargetPos.x));
	
	Scene* scene = Manager::GetScene();  //�e�p

	double probabilyty = 0.01; //0.1%�̊m���Ō����Ă���,0.1%�ɕύX

	if (m_State == ENEMYSTATE::STATE_ATTACK)
	{
		if ((double)rand() / RAND_MAX < probabilyty)
		{
			//�U������
			if (!m_IsAttack)
			{
				scene->AddGameObject<StateBullet>(1)->SetPosition(D3DXVECTOR3(m_Position.x + 1.0f, m_Position.y, m_Position.z));
				m_IsAttack = true;
			}
		}
	}

	if (m_IsAttack)
	{
		m_AttckCnt += 1;
	}
	else if (!m_IsAttack)
	{
		m_AttckCnt = 0;
	}
	if (m_AttckCnt > 1)
	{
		m_IsAttack = false;
	}
	State();
	//���b�V���t�B�[���h�����̎擾
	MeshField* meshField = Manager::GetScene()->GetGameObject<MeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

	CollisionCharge();
	CollisionBullet();
	//�e�Ƃ̓����蔻��
	{
		
		//twoway�̒e�Ƃ̓����蔻��
		{
			std::vector<TwoWay*> TwoBulletList = scene->GetGameObjects<TwoWay>(1); //�G���������邽��gameobjects
			for (TwoWay* bullet : TwoBulletList)
			{
				D3DXVECTOR3 BulletPosition = bullet->GetPosition();   //�G�̍��W���󂯎��
				D3DXVECTOR3 direction = m_Position - BulletPosition;
				float length = D3DXVec3Length(&direction);

				if (length < 1.5f)
				{
					//�����G�t�F�N�g�̐���
					scene->AddGameObject<Explosion>(1)->SetPosition(BulletPosition);
					bullet->SetDestroy();
					HPs -= 1.0f;

					if (HPs <= 3.0f)
					{
						m_IsEscape = true;
					}

					if (HPs <= 0.0f)
					{
						SetDestroy();
					}
					return;
				}
			}
			std::vector<TwowayRIght*> TwowayRightBulletList = scene->GetGameObjects<TwowayRIght>(1); //�G���������邽��gameobjects
			for (TwowayRIght* Rightbullet : TwowayRightBulletList)
			{
				D3DXVECTOR3 BulletPosition = Rightbullet->GetPosition();   //�G�̍��W���󂯎��
				D3DXVECTOR3 direction = m_Position - BulletPosition;
				float length = D3DXVec3Length(&direction);

				if (length < 1.5f)
				{
					//�����G�t�F�N�g�̐���
					scene->AddGameObject<Explosion>(1)->SetPosition(BulletPosition);
					Rightbullet->SetDestroy();
					HPs -= 1.0f;

					if (HPs <= 5.0f)
					{
						m_IsEscape = true;
					}

					if (HPs <= 0.0f)
					{
						SetDestroy();
					}
					return;
				}
			}
		}
		
	}
}

//�`��
void Spider::Draw()
{
	//�����������J�����O
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(0);
	//�����ĂȂ���Ε`�悵�Ȃ�
	if (!camera->CheckView(m_Position))
	{
		return;
	}

	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	//-atan2f(g_enemy[i].direction.z, g_enemy[i].direction.x) - D3DXToRadian(90)
	//�}�g���N�X�̐ݒ�
	D3DXMATRIX wold, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//�O����y, x, z�̏��Őݒ肵�Ă���
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	wold = scale * rot * trans;

	Renderer::SetWorldMatrix(&wold);

	//�`�悷�邾��
	m_Model->Draw();
}

//�G�̍s���p�^�[��
void Spider::State()
{
	switch (m_State)
	{
	case ENEMYSTATE::STATE_WALK:
		Walk();
		break;
	case ENEMYSTATE::STATE_ATTACK:
		Attack();
		break;
	}
}

//�U���֐�
void Spider::Attack()
{
	//�U�����f���̍Đ�
	m_Model->Update("Attacks", m_frame);
	m_Cnt+=1;
	if (m_Cnt >= 150)
	{
		m_State = ENEMYSTATE::STATE_WALK;
	}
}

void Spider::CollisionCharge()
{
	Scene* scene = Manager::GetScene(); 
	std::vector<ChargeBullet*> ChargeList = scene->GetGameObjects<ChargeBullet>(1); //�G���������邽��gameobjects
	for (ChargeBullet* Chargebullet : ChargeList)
	{
		D3DXVECTOR3 BulletPosition = Chargebullet->GetPosition();   //�G�̍��W���󂯎��
		D3DXVECTOR3 direction = m_Position - BulletPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 1.5f)
		{
			//�����G�t�F�N�g�̐���
			scene->AddGameObject<Explosion>(1)->SetPosition(BulletPosition);
			Chargebullet->SetDestroy();
			HPs -= 1.0f;

			if (HPs <= 5.0f)
			{
				m_IsEscape = true;
			}

			if (HPs <= 0.0f)
			{
				SetDestroy();
			}
			return;
		}
	}
}

void Spider::CollisionBullet()
{
	Scene* scenes = Manager::GetScene();
	//�ʏ�̒e�Ƃ̓����蔻��
	std::vector<Bullet*> BulletList = scenes->GetGameObjects<Bullet>(1); //�G���������邽��gameobjects
	for (Bullet* bullet : BulletList)
	{
		D3DXVECTOR3 BulletPosition = bullet->GetPosition();   //�G�̍��W���󂯎��
		D3DXVECTOR3 direction = m_Position - BulletPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 1.5f)
		{
			//�����G�t�F�N�g�̐���
			scenes->AddGameObject<Explosion>(1)->SetPosition(BulletPosition);
			bullet->SetDestroy();
			HPs -= 0.5f;
				if (HPs <= 3.0f)
				{
					m_IsEscape = true;
				}

				if (HPs <= 0.0f)
				{
					SetDestroy();
				}
				return;
			}
		}
}

void Spider::CollisionTwoWay()
{
}

//�����Ă���Ƃ��̊֐�
void Spider::Walk()
{
	m_Cnt = 0;
	if (!m_IsEscape)
	{
		//���W�̍X�V
		m_Position.x += m_Direction.x * (m_Speed * cosf(m_Angle) * 0.01f + 0.02f);
		m_Position.z += m_Direction.z * (m_Speed * sinf(m_Angle) * 0.01f + 0.02f);

		m_Rotation.y = -atan2f(m_Direction.z, m_Direction.x) - D3DXToRadian(90);
		if (m_Speed >= 0.2f)
		{
			m_Speed = 0.5f;
		}
	}

	else if (m_IsEscape)
	{
		m_Speed = 0.5f;	
		m_Rotation.y = -atan2f(m_Direction.z, m_Direction.x) + D3DXToRadian(90);
		//���W�̍X�V
		m_Position.x -= m_Direction.x * (m_Speed * cosf(m_Angle) * 0.03f);
		m_Position.z -= m_Direction.z * (m_Speed * sinf(m_Angle) * 0.03f);
	}
	m_Model->Update("Walk", m_frame);
	Scene* scene = Manager::GetScene();
	std::vector<BoxCollision*> BoxList = scene->GetGameObjects<BoxCollision>(1);
	for (BoxCollision* BoxColli : BoxList)
	{
		D3DXVECTOR3 BoxCollisionPosition = BoxColli->GetPosition();   //�G�̍��W���󂯎��
		D3DXVECTOR3 direction = m_Position - BoxCollisionPosition;
		float length = D3DXVec3Length(&direction);
			
		if (length < 1.5f)
		{
				m_State = ENEMYSTATE::STATE_ATTACK;
				return;
		}
	}
}

int Spider::SetHp()
{
	return HPs;
}