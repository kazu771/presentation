//==============================================================================================
//�A�C�e����{����.cpp[Item.cpp]
//date:2021/05/31     name:Kazuki Wada
//==============================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "Item.h"

//������
void Item::Init()
{
	m_Heart = new Model();
	m_Heart->Load("asset\\model\\heart.obj");
	rotation = 0.0f;
	m_Position = D3DXVECTOR3(100.0f, 1.0f, -1.0f);
	m_Rotation = D3DXVECTOR3(0.0f, rotation, 0.0f);
	m_Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	Type = TYPE_NORMAL;
	
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}

//�I��
void Item::UnInit()
{
	m_Heart->Unload();
	delete m_Heart;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//�X�V
void Item::Update()
{
	rotation += 0.1f;
	
	m_Rotation = D3DXVECTOR3(0.0f, rotation, 0.0f);
	


}

//�`��
void Item::Draw()
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
	m_Heart->Draw();
}

//�A�C�e���̎�ނ�ς���悤
void Item::TypeItem(ITEMTYPE type)
{
	Type = type;
}