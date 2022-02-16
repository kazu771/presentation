//=========================================================================================================
//������̒e��{����(��).cpp[TwoWayBullet.cpp]
//date:2021/11/30     name:Kazuki Wada
//=========================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "GameObject.h"
#include "model.h"
#include "TwoWayBullet.h"
#include "player.h"
#include "Spider.h"

Model* TwoWay::m_Model;//�X�^�e�B�b�N�ϐ�������cpp���ł��錾���K�v

void TwoWay::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\Arrows.obj");
}

void TwoWay::UnLoad()
{
	m_Model->Unload();
	delete m_Model;
}

void TwoWay::Init()
{
	m_Position = D3DXVECTOR3(3.0f, 1.0f, 2.0f);
	m_Rotation = D3DXVECTOR3(90.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	//�v���C���[�̏����󂯎��
	Player* player = Manager::GetScene()->GetGameObject<Player>(1);
	m_Direction = player->GetForward();
}

void TwoWay::UnInit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void TwoWay::Update()
{

	m_Position.x += (m_Direction.x - 1.0f) * 0.5f;
	m_Position.y  =  m_Direction.y * 0.5f;
	m_Position.z -=  m_Direction.z * 0.5f;


}

void TwoWay::Draw()
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


