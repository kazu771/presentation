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
#include "KeyEffect.h"
#include "PoisonEffect.h"
#include "ChargeBullet.h"
#include "input.h"

Model* ChargeBullet::m_Model;//�X�^�e�B�b�N�ϐ�������cpp���ł��錾���K�v

void ChargeBullet::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\Arrows.obj");
}

void ChargeBullet::UnLoad()
{
	m_Model->Unload();
	delete m_Model;
}

void ChargeBullet::Init()
{

	m_Position = D3DXVECTOR3(3.0f, 1.0f, 2.0f);
	m_Rotation = D3DXVECTOR3(90.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	m_Attack = 0;
	m_Cnt = 0.0f;
	m_Speed = 0.0f;
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	//�v���C���[�̏����󂯎��
	Player* player = Manager::GetScene()->GetGameObject<Player>(1);
	m_Direction = player->GetForward();
}

//�I��
void ChargeBullet::UnInit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//�X�V
void ChargeBullet::Update()
{
	//�G�Ƃ̓����蔻��
	{
		Scene* scene = Manager::GetScene();
		//�ʏ�̓G�Ƃ̓����蔻��
		{
			std::vector<Enemy*> enemyList = scene->GetGameObjects<Enemy>(1); //�G���������邽��gameobjects
			for (Enemy* enemy : enemyList)
			{
				D3DXVECTOR3 enemyPosition = enemy->GetPosition();   //�G�̍��W���󂯎��
				D3DXVECTOR3 direction = m_Position - enemyPosition;

				D3DXVECTOR3 obbx, obbz;
				float obblenX, obblenZ;

				obbx = enemy->GetObbX();
				obblenX = D3DXVec3Length(&obbx);//�x�N�g���̒��������߂Ă���
				obbx /= obblenX;//�����������̒������P�ɂ��Ă���

				obbz = enemy->GetObbZ();
				obblenZ = D3DXVec3Length(&obbz);
				obbz /= obblenZ;

				float lenX, lenZ;
				lenX = D3DXVec3Dot(&obbx, &direction);//����
				lenZ = D3DXVec3Dot(&obbz, &direction);

				//fabs�Ő�Βl�����߂Ă���
				if (fabs(lenX) < obblenX && fabs(lenZ) < obblenZ)
				{
					//�����G�t�F�N�g�̐���
					scene->AddGameObject<PoisonEffect>(1)->SetPosition(m_Position);
					//enemy->SetDestroy(); //�G�̔j��
					SetDestroy();        //�e�̔j��

					return;
				}

			}

		}
		
		m_Position.x -= m_Direction.x * 0.5;
		m_Position.y -= m_Direction.y * 0.5;
		m_Position.z -= m_Direction.z * 0.5;
		//�t�B�[���h�O�ɏo��������\��
		if (m_Position.z > 100.0f || m_Position.z < -80.0f || m_Position.x > 70.0f || m_Position.x < -70.0f)
		{
			//�����G�t�F�N�g�̐���
			scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);
			SetDestroy();
			return;
		}
	}
	//�`���[�W
	if (Input::GetKeyPress('T'))
	{
		m_Cnt += 0.1f;
	}
	//�`���[�W�̗ʂɂ���čU���͂̕ω�
	if (m_Cnt > 0.4f)
	{
		m_Attack += 2;
		
	}
	//�ő�1.0f
	else if (m_Cnt > 1.0f)
	{
		m_Attack += 5;
	}
}
//�`��
void ChargeBullet::Draw()
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