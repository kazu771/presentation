//======================================================================================
//�G�̒e��{����.h[EnemyEnemyBullet.h]
//date:2021/07/14   name:Kazuki Wada
//======================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "GameObject.h"
#include "model.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "player.h"
#include "Explosion.h"
#include "Title.h"
#include "Spider.h"
#include "PoisonEffect.h"

Model* EnemyBullet::m_Model;//�X�^�e�B�b�N�ϐ�������cpp���ł��錾���K�v

void EnemyBullet::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\nife.obj");
}

void EnemyBullet::UnLoad()
{
	m_Model->Unload();
	delete m_Model;
}

void EnemyBullet::Init()
{

	m_Position = D3DXVECTOR3(3.0f, 1.0f, 2.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 1.6f, 0.0f);
	m_Scale = D3DXVECTOR3(0.35f, 0.35f, 0.35f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	m_Spider = Manager::GetScene()->GetGameObject<Spider>(1);
	Spider* enemy = Manager::GetScene()->GetGameObject<Spider>(1);
	m_Direction = enemy->GetForward();
}

//�I��
void EnemyBullet::UnInit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//�X�V
void EnemyBullet::Update()
{
	m_Direction = m_Spider->GetForward();
	//�v���C���[�Ƃ̓����蔻��
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
			scene->AddGameObject<PoisonEffect>(1)->SetPosition(D3DXVECTOR3(PlayerPosition.x, PlayerPosition.y + 1.0f, PlayerPosition.z));
			player->ChangePoison();
			SetDestroy();        //�e�̔j��
			
			return;
		}
	}

	//�Ō�̊|���Z�ŃX�s�[�h�𒲐�
	m_Position -= m_Direction * 0.5;

	//���ɍs���Ăق�������z���������{����
	//m_Position.z -= 0.01f;
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
void EnemyBullet::Draw()
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