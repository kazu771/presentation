//====================================================================================================================
//�����h�A��{����.cpp[Door.cpp]
//date:2021/11/16   name:Kazuki Wada
//====================================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "RightDoor.h"
#include "Key.h"
#include "player.h"
#include "input.h"

void RightDoor::Init()
{
	m_Door = new Model();
	m_Door->Load("asset\\model\\RightDoor.obj");
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Cnt = 0;

	Scene* scene = Manager::GetScene();

	//���̏����擾
	m_Key = scene->AddGameObject<Key>(1);
	m_Chack = m_Key->isActive();//�ŏ���false

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}

void RightDoor::UnInit()
{
	m_Door->Unload();
	delete m_Door;


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void RightDoor::Update()
{
	m_Chack = m_Key->isActive();//���̏�Ԃ��擾
	//�����擾���Ă�����
	if (m_Chack)
	{
		Scene* scene = Manager::GetScene();
		std::vector<Player*> PlayerList = scene->GetGameObjects<Player>(1); //�G���������邽��gameobjects
		for (Player* player : PlayerList)
		{
			D3DXVECTOR3 PlayerPosition = player->GetPosition();   //�G�̍��W���󂯎��
			D3DXVECTOR3 direction = m_Position - PlayerPosition;
			float length = D3DXVec3Length(&direction);

			if (Input::GetKeyTrigger('E'))
			{
				if (PlayerPosition.z < m_Position.z + 2.0f)
				{

					m_isActive = true;
				}
				return;
			}
		}

	}

	if (m_isActive)
	{
		if (m_Cnt < 10)
		{
			m_Rotation.y += 0.1f;
			m_Cnt += 1;
		}
		else
		{
			m_isActive = false;
		}
	}
}

void RightDoor::Draw()
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
	m_Door->Draw();
}
