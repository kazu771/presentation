//==============================================================================================
//�v���C���[�̒e��{����.cpp[Bullet.cpp]
//date;2021/05/31     name:Kazuki Wada
//==============================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "GameObject.h"
#include "model.h"
#include "Enemy.h"
#include "player.h"
#include "Explosion.h"
#include "Item.h"
#include "Spider.h"
#include "PoisonBullet.h"
#include "Poison.h"
#include "DamageUi.h"
#include "PoisonEffect.h"

Model* PoisonBullet::m_Model;//�X�^�e�B�b�N�ϐ�������cpp���ł��錾���K�v
Player* m_Player;

void PoisonBullet::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\Box.obj");
}

void PoisonBullet::UnLoad()
{
	m_Model->Unload();
	delete m_Model;
}

void PoisonBullet::Init()
{

	m_Position = D3DXVECTOR3(3.0f, 1.0f, 2.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	//�v���C���[�̏����󂯎��
	Player* player = Manager::GetScene()->GetGameObject<Player>(1);

	Scene* scene = Manager::GetScene();
	
	//�ł̏����擾
	m_Player = scene->AddGameObject<Player>(1);
	std::vector<Enemy*> EnemyList = scene->GetGameObjects<Enemy>(1);
	for (Enemy* enemys : EnemyList)
	{
		m_Direction = enemys->GetForward();
	}
}

//�I��
void PoisonBullet::UnInit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//�X�V
void PoisonBullet::Update()
{
	//�v���C���[�Ƃ̓����蔻��
	{
		Scene* scene = Manager::GetScene();
		{
			std::vector<Player*> PlayerList = scene->GetGameObjects<Player>(1); 
			for (Player* player : PlayerList)
			{
				D3DXVECTOR3 PlayerPosition = player->GetPosition();   //�G�̍��W���󂯎��
				D3DXVECTOR3 direction = m_Position - PlayerPosition;
				float length = D3DXVec3Length(&direction);

				if (length < 1.5f)
				{
					//�����G�t�F�N�g�̐���
					scene->AddGameObject<PoisonEffect>(1)->SetPosition(PlayerPosition);//�ŗp�̃G�t�F�N�g�ɕύX����
				
					player->ChangePoison();
					SetDestroy();        //�e�̔j��
					return;
				}
			}
			//�ʒu���W�Ƀv���C���[�̌���������A�Ō�̊|���Z�ŃX�s�[�h�𒲐�
			m_Position -= m_Direction * 0.5;

			//���ɍs���Ăق�������z���������{����
			/*m_Position.z += 0.01f;*/
			//�t�B�[���h�O�ɏo��������\��
			if (m_Position.z > 100.0f || m_Position.z < -80.0f || m_Position.x > 70.0f || m_Position.x < -70.0f)
			{
				//�����G�t�F�N�g�̐���
				scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);

				SetDestroy();
				return;
			}
		}
	}
}
//�`��
void PoisonBullet::Draw()
{
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
	m_Model->Draw();
}