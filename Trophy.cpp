//====================================================================================================================
//��{����.cpp[Door.cpp]
//date:2021/11/16   name:Kazuki Wada
//====================================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "player.h"
#include "Trophy.h"
#include "input.h"

void Trophy::Init()
{
	m_Trophy = new Model();
	m_Trophy->Load("asset\\model\\Trohpys.obj");
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);

	Scene* scene = Manager::GetScene();

	
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}

void Trophy::UnInit()
{
	m_Trophy->Unload();
	delete m_Trophy;


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Trophy::Update()
{
	
	Scene* scene = Manager::GetScene();
	std::vector<Player*> PlayerList = scene->GetGameObjects<Player>(1); //�G���������邽��gameobjects

	for (Player* player : PlayerList)
	{
		D3DXVECTOR3 PlayerPosition = player->GetPosition();   //�G�̍��W���󂯎��
		D3DXVECTOR3 direction = m_Position - PlayerPosition;
		float length = D3DXVec3Length(&direction);
		if (length < 1.5f)
		{
			SetDestroy();
		}
			
	}
	
}

void Trophy::Draw()
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
	wold = scale * trans * rot;

	Renderer::SetWorldMatrix(&wold);

	//�`�悷�邾��
	m_Trophy->Draw();
}


