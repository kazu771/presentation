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
#include "Poison.h"
#include "DamageUi.h"
#include "PoisonEffect.h"
#include "StateBullet.h"

Model* StateBullet::m_Model;//�X�^�e�B�b�N�ϐ�������cpp���ł��錾���K�v

void StateBullet::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\Confusions.obj");
}

void StateBullet::UnLoad()
{
	m_Model->Unload();
	delete m_Model;
}

void StateBullet::Init()
{

	m_Position = D3DXVECTOR3(3.0f, 1.0f, 2.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 1.6f, 0.0f);
	m_Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	m_IsAttack = false;
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	Scene* scene = Manager::GetScene();
	//�G�̏����擾
	std::vector<Spider*> EnemyList = scene->GetGameObjects<Spider>(1);
	for (Spider* enemys : EnemyList)
	{
		m_Direction = enemys->GetForward();
	}
}

//�I��
void StateBullet::UnInit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//�X�V
void StateBullet::Update()
{
	//�v���C���[�Ƃ̓����蔻��(
	Scene* scene = Manager::GetScene();
	std::vector<Player*> PlayerList = scene->GetGameObjects<Player>(1); //�G���������邽��gameobjects
	for (Player* player : PlayerList)
	{
		D3DXVECTOR3 PlayerPosition = player->GetPosition();   //�v���C���[�̍��W���󂯎��
		D3DXVECTOR3 direction = m_Position - PlayerPosition;
		float length = D3DXVec3Length(&direction);
		if (length < 1.5f)
		{
			//�����G�t�F�N�g�̐���
			scene->AddGameObject<PoisonEffect>(1)->SetPosition(D3DXVECTOR3(PlayerPosition.x, PlayerPosition.y + 0.5f, PlayerPosition.z));
			player->ChangePoison();
			SetDestroy();        //�e�̔j��

			return;
		}
	}

	//�Ō�̊|���Z�ŃX�s�[�h�𒲐�
	m_Position -= m_Direction * 0.5;

	//���ɍs���Ăق�������z���������{����
	//m_Position.z += 0.01f;
	//�t�B�[���h�O�ɏo��������\��
	if (m_Position.z > 70.0f || m_Position.z < -70.0f || m_Position.x > 70.0f || m_Position.x < -70.0f)
	{
		//�����G�t�F�N�g�̐���
		scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);

		SetDestroy();
		return;
	}
}

//�`��
void StateBullet::Draw()
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