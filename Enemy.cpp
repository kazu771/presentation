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
#include "Enemy.h"
#include "player.h"
#include "EnemyBullet.h"
#include "BoxCollision.h"
#include "input.h"
#include "MeshField.h"
#include "animationModel.h"
#include "Camera.h"
#include "ConfusionBullet.h"
#include "Bullet.h"
#include "TwoWayBullet.h"
#include "TwoWayBulletRight.h"
#include "Explosion.h"

//������
void Enemy::Init()
{
	m_Cnt = 10;
	m_Models = new AnimetionModel();

	m_Models->Load("asset\\model\\EnemyWalks.fbx"); //�{�[���Ȃǂ�ǂݍ��ނ��߂ɏ����Ă���
	m_Models->LoadAnimation("asset\\model\\EnemyWalking.fbx", "WalkS");
	m_Models->LoadAnimation("asset\\model\\EnemyAttacks.fbx", "AttackS");

	m_State = STATACE::STATACE_ATTACK;
	m_Position = D3DXVECTOR3(0.0f, 0.5f, 5.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
	
	m_TargetPos = { 0.0f, 0.0f, 0.0f };

	m_Direction = { 0.0f, 0.0f, 0.0f };
	m_Angle = 0.0f;
	m_Speed = SPEED_MAX;
	m_IsAngle = false;
	m_IsEscape = false;
	HPs = 50;
	m_Hpss = 15.0f;
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}
//�I��
void Enemy::UnInit()
{
	m_Models->Unload();
	delete m_Models;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//�X�V
void Enemy::Update()
{
	
	m_frame++;
	
	Player* p_player = Manager::GetScene()->GetGameObject<Player>(1);
	m_TargetPos = p_player->GetPosition();

	float sgn = m_Cross.y < 0.0f ? -1.0f : 1.0f;

	//�G�ƃv���C���[�̋����̍������Z�o
	m_Direction.x = m_TargetPos.x - m_Position.x;
	m_Direction.z = m_TargetPos.z - m_Position.z;
	

	//���K��
	D3DXVec3Normalize(&m_Direction, &m_Direction);
	
	m_Angle = atan2(fabsf(m_TargetPos.z - m_Position.z), fabsf(m_TargetPos.x - m_Position.x));
	
	Scene* scene = Manager::GetScene();  //�e�p

	double probabilyty = 0.01; //0.1%�̊m���Ō����Ă���
	if (m_State == STATACE::STATACE_ATTACK)
	{

		if ((double)rand() / RAND_MAX < probabilyty)
		{
			scene->AddGameObject<ConfusionBullet>(1)->SetPosition(D3DXVECTOR3(m_Position.x, m_Position.y + 0.5f, m_Position.z));

		}
	}
	State();
	//���b�V���t�B�[���h�����̎擾
	MeshField* meshField = Manager::GetScene()->GetGameObject<MeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);


	//�e�Ƃ̓����蔻��
	{
		//�ʏ�̒e�Ƃ̓����蔻��
		{
			std::vector<Bullet*> BulletList = scene->GetGameObjects<Bullet>(1); //�G���������邽��gameobjects
			for (Bullet* bullet : BulletList)
			{
				D3DXVECTOR3 BulletPosition = bullet->GetPosition();   //�G�̍��W���󂯎��
				D3DXVECTOR3 direction = m_Position - BulletPosition;
				float length = D3DXVec3Length(&direction);

				if (length < 1.5f)
				{
					//�����G�t�F�N�g�̐���
					scene->AddGameObject<Explosion>(1)->SetPosition(BulletPosition);
					bullet->SetDestroy();
					m_Hpss -= 1.0f;

					if (m_Hpss <= 5.0f)
					{
						m_IsEscape = true;
					}

					if (m_Hpss <= 0.0f)
					{
						SetDestroy();
					}
					return;
				}
			}
		}

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
					m_Hpss -= 1.0f;

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
					m_Hpss -= 1.0f;

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

	if (m_IsEscape)
	{
		m_State = STATACE::STATACE_WALK;
	}
}

//�`��
void Enemy::Draw()
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

	//�}�g���N�X�̐ݒ�
	D3DXMATRIX wold, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//�O����y, x, z�̏��Őݒ肵�Ă���
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	wold = scale * rot * trans;

	Renderer::SetWorldMatrix(&wold);

	//�`�悷�邾��
	m_Models->Draw();
}

//�G�̍s���p�^�[��
void Enemy::State()
{
	switch (m_State)
	{
	case STATACE::STATACE_WALK:
		Walk();
		break;
	case STATACE::STATACE_ATTACK:
		Attack();
		break;
	}
}

//�U���֐�
void Enemy::Attack()
{
	//�U���̃��f���Đ�
	m_Models->Update("AttackS", m_frame);
}

//�����Ă���Ƃ��̊֐�
void Enemy::Walk()
{
	m_Cnt = 0;
	m_Rotation.y = -atan2f(m_Direction.z, m_Direction.x) + D3DXToRadian(90);
	//���W�̍X�V
	m_Position.x -= m_Direction.x * (m_Speed * cosf(m_Angle) * 0.03f);
	m_Position.z -= m_Direction.z * (m_Speed * sinf(m_Angle) * 0.03f);
	m_Models->Update("WalkS", m_frame);
	Scene* scene = Manager::GetScene();
	std::vector<BoxCollision*> BoxList = scene->GetGameObjects<BoxCollision>(1);
	for (BoxCollision* BoxColli : BoxList)
	{
		D3DXVECTOR3 BoxCollisionPosition = BoxColli->GetPosition();   //�G�̍��W���󂯎��
		D3DXVECTOR3 direction = m_Position - BoxCollisionPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 1.5f)
		{
			m_State = STATACE::STATACE_ATTACK;
			return;
		}
	}

}