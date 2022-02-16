//==============================================================================================================
//�̗̓A�C�e����{����.cpp[HpItem.cpp]
//date:2021/12/14    name:Kazuki Wada
//==============================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "player.h"
#include "HpItem.h"

void HpItem::Init()
{
	m_MHp = new Model();
	m_MHp->Load("asset\\model\\heart.obj");
	m_rotations = 0.0f;
	m_Position = D3DXVECTOR3(100.0f, 1.0f, -1.0f);
	m_Rotation = D3DXVECTOR3(0.0f, m_rotations, 0.0f);
	m_Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	m_Cnt = 5.0f;
	Scene* scene = Manager::GetScene();
	m_Player = scene->AddGameObject<Player>(1);
	m_isHp = m_Player->GetHpItem();//�A�C�e�����v���C���[���擾�������ǂ���
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}

void HpItem::UnInit()
{
	m_MHp->Unload();
	delete m_MHp;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void HpItem::Update()
{
	m_isHp = m_Player->GetHpItem();//�A�C�e�����v���C���[���擾�������ǂ���
	if (!m_isHp)
	{
		m_rotations += 0.1f;
	}

	//�v���C���[���擾���������
	else if (m_isHp)
	{
		SetDestroy();
		//ChangeFlag();
	}
	m_Rotation = D3DXVECTOR3(0.0f, m_rotations, 0.0f);
}

void HpItem::Draw()
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
	m_MHp->Draw();
}

void HpItem::ChangeFlag()
{
	if (m_isHp && m_Cnt >= 0)
	{
		m_Cnt -= 1.0f;

		if (m_Cnt < 0)
		{
			m_isHp = false;
			m_Cnt = 5.0f;
		}
	}
}
