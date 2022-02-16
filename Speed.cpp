//================================================================================================
//�X�s�[�h�A�C�e����{����.cpp[Speed.cpp]
//date:2021/07/08  name:Kazuki Wada
//================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "Speed.h"

//������
void Speed::Init()
{
	m_Speed = new Model();
	m_Speed->Load("asset\\model\\heart.obj");
	m_Rotations = 0.0f;
	m_Position = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, m_Rotations, 0.0f);
	m_Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	



	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}

//�I��
void Speed::UnInit()
{
	m_Speed->Unload();
	delete m_Speed;


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//�X�V
void Speed::Update()
{
	m_Rotations += 0.1f;

	m_Rotation = D3DXVECTOR3(0.0f, m_Rotations, 0.0f);



}

//�`��
void Speed::Draw()
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
	m_Speed->Draw();
}


void Speed::Speedefect()
{
	move += 0.5f;
}
