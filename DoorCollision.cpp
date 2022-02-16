//===================================================================================================================
//�h�A�p�R���W������{����.h[DoorCollision.h]
//date:2022/01/11     name:Kauzki Wada
//===================================================================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Scene.h"
#include "Enemy.h"
#include "DoorCollision.h"
#include "Door.h"

//���_�f�[�^
//���W, �@��, �F, �e�N�X�`���[���W
//�}�`����ʂ��猩���Ƃ��ɍ����E�A������̏��ɂȂ�悤�ɔz�u
DoorCollision::VERTEX3D g_vertexList[]
{
	
//����ad
{{ 0.0f, 0.0f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, //0
{{ 7.5f, 0.0f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, //1
{{ 0.0f, 7.0f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, //2
{{ 7.5f, 7.0f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, //3


//�E��
{{ 7.5f, 0.0f,   0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, //4
{{ 7.5f, 7.0f,   0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, //5


//����
{{ 0.0f, 0.0f,   0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, //6
{{ 0.0f, 7.0f,   0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, //7

//���ʂ͍��܂ł̒��_�f�[�^���g���΂����̂ŏȗ�

};

//�C���f�b�N�X�f�[�^
WORD g_DoorIndexList[]
{

	//------
	//����
	//------
	 0, 1, //��
	 2, 3, //��
	 0, 2, //��
	 1, 3, //�E

	//-----
	//�E
	//-----
	 1, 4, //��
	 3, 5, //��
	 1, 3, //��
	 4, 5, //�E

	//-----
	//���
	//-----
	 6, 4, //��
	7, 5, //��
	 6, 7, //��
	 4, 5, //�E

	 //-----
	 //��
	 //-----
	 6, 0, //��
	 7, 2, //��
	 6, 7, //��
	 0, 2, //�E
};

void DoorCollision::Init()
{
	m_IsVisible = false;


	m_TargetPos = { 0.0f, 0.0f, 0.0f };
	m_TargetRot = { 0.0f, 0.0f, 0.0f };
	m_Direction = { 0.0f, 0.0f, 0.0f };
	m_Angle = 0.0f;
	//���_�o�b�t�@�[�̐���
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	//���_�o�b�t�@�[�̃T�C�Y(���_��)
	bd.ByteWidth = sizeof(VERTEX3D) * 8;
	//���_�o�b�t�@�[�Ƃ������Ƃ��������ߗp
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	//�ŏ��ɓ���Ă������_�o�b�t�@�[��ۑ�������
	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = g_vertexList;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//�C���f�b�N�X�o�b�t�@�[�̐���
	D3D11_BUFFER_DESC ibDesc{};
	ibDesc.Usage = D3D11_USAGE_DEFAULT;
	ibDesc.ByteWidth = sizeof(WORD) * 32;
	//�C���f�b�N�X�o�b�t�@�[�Ƃ������Ƃ��ؖ�
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA irDate{};
	irDate.pSysMem = g_DoorIndexList;

	Renderer::GetDevice()->CreateBuffer(&ibDesc, &irDate, &m_IndexBuffer);

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	//�e�N�X�`���[�̓ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetDevice(),
		"asset/model/Treasure.png",
		NULL,
		NULL,
		&m_Texture,
		NULL
	);
	//��O�����p
	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	Renderer::CreateVertexShader(&m_IndexShader, &m_VertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_IndexPixcelShader, "vertexLightingPS.cso");
}

void DoorCollision::UnInit()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_IndexShader->Release();
	m_IndexPixcelShader->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void DoorCollision::Update()
{
	
}

void DoorCollision::Draw()
{
	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//���_�o�b�t�@�[�̐ݒ�
	UINT stride = sizeof(VERTEX3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	//�}�g���N�X�̐ݒ�
	D3DXMATRIX wold, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);

	//�O����y, x, z�̏��Őݒ肵�Ă���
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	wold = scale * rot * trans;
	Renderer::SetWorldMatrix(&wold);

	//�v���~�e�B�u�g�|���W�ݒ�
	//���_���ǂ�����Č��Ԃ̂�
	//�O�p�`�̏�����
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	//�|���S���`��
	Renderer::GetDeviceContext()->DrawIndexed(32, 0, 0);
}
