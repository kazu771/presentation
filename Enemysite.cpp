//==================================================================================================
//�G�̎�����{����.cpp[ENEMYSITE.cpp]
//date:2021/10/01   name:Kazuki Wada
//==================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "Enemysite.h"
#include "Enemy.h"
#include "player.h"
//
//�O���[�o���ϐ�
//
Model* Enemysite::m_Model;//�X�^�e�B�b�N�ϐ�������cpp���ł��錾���K�v

void Enemysite::Init()
{
		m_Model = new Model();
		m_Model->Load("asset\\model\\enemysite.obj");

		m_Position = D3DXVECTOR3(3.0f, 1.0f, 2.0f);
		m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_Enemypos = { 0.0f, 0.0f, 0.0f };
		m_Enemyrot = { 0.0f, 0.0f, 0.0f };
		m_Playerpos = { 0.0f, 0.0f, 0.0f };
		m_isAttack = false;
	/*Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "LineofsightVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "LineofsightPS.cso");
*/
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	
}

void Enemysite::UnInit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Enemysite::Update()
{
	Enemy* p_Enemy = Manager::GetScene()->GetGameObject<Enemy>(1);
	Player* p_Player = Manager::GetScene()->GetGameObject<Player>(1);
	m_Enemypos = p_Enemy->GetPosition();
	m_Enemyrot = p_Enemy->GetRotation();
	m_Playerpos = p_Player->GetPosition();
	m_Position.x = m_Enemypos.x;
	m_Position.y = 1.0f;

	if (m_Enemypos.z > m_Playerpos.z)
	{
		m_Position.z = m_Enemypos.z - 1.0f;
	}

	else if (m_Enemypos.z < m_Playerpos.z)
	{
		m_Position.z = m_Enemypos.z + 1.0f;
	}
	m_Rotation = m_Enemyrot;
}

void Enemysite::Draw()
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

//�v���C���[�Ƃ̓����蔻��
void Enemysite::Collision()
{
	//�G�Ƃ̓����蔻��(
	Scene* scene = Manager::GetScene();
	std::vector<Player*> PlayerList = scene->GetGameObjects<Player>(1); //�G���������邽��gameobjects
	for (Player* player : PlayerList)
	{
		D3DXVECTOR3 enemyPosition = player->GetPosition();   //�G�̍��W���󂯎��
		D3DXVECTOR3 direction = m_Position - enemyPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 1.5f)
		{

			return;
		}
	}
}



