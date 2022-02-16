//==================================================================================================
//��I�u�W�F�N�g��{����.h[Rock.h]
//date:2021/12/11    namek:Kazuki Wada
//==================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "Rock.h"

void Rock::Init()
{
	m_Rock = new Model();
	m_Rock->Load("asset\\model\\rock.obj");
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}

void Rock::UnInit()
{
	m_Rock->Unload();
	delete m_Rock;


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Rock::Update()
{
}

void Rock::Draw()
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
	m_Rock->Draw();
}
