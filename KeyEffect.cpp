//====================================================================================================================
//���̃G�t�F�N�g��{����.cpp[KeyEffect.cpp]
//date:2021/06/21   name:Kazuki Wada
//====================================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "assetnames.h"
#include "input.h"
#include "Texture.h"
#include "Sprite.h"
#include "KeyEffect.h"
#include "Camera.h"

void KeyEffect::Init()
{
	VERTEX_3D vertex[4];
	//�����|���S��
	//���W��Z���ɂȂ�悤�ɔz�u
	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);      //����
	vertex[0].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //�@��
	vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //���_�̐F,�O����RGBA
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);             //�e�N�X�`���[�̂͂�ʒu

	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);       //�E��
	vertex[1].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //�@��
	vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //�e�N�X�`���[�̐F
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);			  //�e�N�X�`���[�̂͂�ʒu

	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);     //����
	vertex[2].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //�@��
	vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //�e�N�X�`���[�̐F
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);			  //�e�N�X�`���[�̂͂�ʒu

	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);      //�E��
	vertex[3].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //�@��
	vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //�e�N�X�`���[�̐F
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);             //�e�N�X�`���[�̂͂�ʒu

	//���_�o�b�t�@�[�̐���
	D3D11_BUFFER_DESC bd{};
	//ZeroMemory();
	bd.Usage = D3D11_USAGE_DYNAMIC;
	//���_�o�b�t�@�[�̃T�C�Y
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;  //�o�b�t�@�[�̃T�C�Y�����₳�Ȃ��ƎO�p�`�������Ȃ�4���ƈ�A8���Ɠ��
	//���_�o�b�t�@�[�Ƃ������Ƃ��������ߗp
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//�ŏ��ɓ���Ă������_�o�b�t�@�[��ۑ�������
	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//�e�N�X�`���[�̓ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetDevice(),
		"asset/texture/KeyEffects.png",
		NULL,
		NULL,
		&m_Texture,
		NULL
	);
	//��O�����p
	assert(m_Texture);

	//�����͉��݂����Ȃ��̂Ȃ̂�unlitTexture�̂ق����g��
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Count = 0;
}

void KeyEffect::UnInit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void KeyEffect::Update()
{
	m_Count++;
	if (m_Count >= 16)
	{
		SetDestroy();
		return;
	}
}

void KeyEffect::Draw()
{
	//�e�N�X�`���[���W�Z�o
	float x = m_Count % 5 * (1.0f / 8);
	float y = m_Count / 4 * (1.0f / 4);

	//���_�f�[�^��������
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);      //����
	vertex[0].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //�@��
	vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //���_�̐F,�O����RGBA
	vertex[0].TexCoord = D3DXVECTOR2(x, y);                   //�e�N�X�`���[�̂͂�ʒu

	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);       //�E��
	vertex[1].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //�@��
	vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //�e�N�X�`���[�̐F
	vertex[1].TexCoord = D3DXVECTOR2(x + 0.25f, y);			  //�e�N�X�`���[�̂͂�ʒu

	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);     //����
	vertex[2].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //�@��
	vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //�e�N�X�`���[�̐F
	vertex[2].TexCoord = D3DXVECTOR2(x, y + 0.25f);			  //�e�N�X�`���[�̂͂�ʒu

	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);      //�E��
	vertex[3].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //�@��
	vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //�e�N�X�`���[�̐F
	vertex[3].TexCoord = D3DXVECTOR2(x + 0.25f, y + 0.25f);   //�e�N�X�`���[�̂͂�ʒu7

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(0);
	D3DXMATRIX view = camera->GetViewMatrix();


	//�r���[�̋t�s��
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);
	//41,42,43�͈ړ������������Ă���Ƃ���ł����������Ă�����=�ړ��������Ȃ��Ȃ�A�J�����ɒ���t�����w�肵���ꏊ�ŕ`�悪�ł���
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;


	//�}�g���N�X�̐ݒ�
	D3DXMATRIX wold, scale, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);

	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	wold = scale * invView * trans;
	Renderer::SetWorldMatrix(&wold);


	//���_�o�b�t�@�[�̐ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//�}�e���A���̐ݒ�
	MATERIAL material;
	//�}�e���A���̑S����������
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	//�e�N�X�`���[�̐ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//�v���~�e�B�u�g�|���W�ݒ�
	//���_���ǂ�����Č��Ԃ̂�
	//�O�p�`�̏�����
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	//������:���_��
	//���_���������邱�ƂŎO�p�`�̐���ς�����
	//������:���Ԗڂ̒��_����n�߂邩
	Renderer::GetDeviceContext()->Draw(4, 0);
}
