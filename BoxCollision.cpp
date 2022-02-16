//======================================================================================
//�v���C���[�p���^�R���W������{����.cpp[BoxCollision.cpp]
//date:2021/08/18  name:Kazuki Wada
//======================================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Scene.h"
#include "BoxCollision.h"
#include "Enemy.h"
#include "input.h"
#include "player.h"

//���_�f�[�^
//���W, �@��, �F, �e�N�X�`���[���W
BoxCollision::VERTEX3D g_VertexList[]
{
	//��ԉE
	//�O��
	{{ 0.0f, 3.0f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, //0,����
	{{ 2.0f, 3.0f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, //1,�E��
	{{ 0.0f, 0.0f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, //2,����
	{{ 2.0f, 0.0f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, //3,�E��

	//�E��
	{{ 2.0f, 3.0f,   1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, //4
	{{ 2.0f, 0.0f,   1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, //5

	//����
	{{ 0.0f, 3.0f,   1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, //6
	{{ 0.0f, 0.0f,   1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, //7

	//����
	//�������W��p���邽�ߏȗ�
};


//�C���f�b�N�X�f�[�^
WORD g_IndexList[]
{

	//------
	//����
	//------
	 0, 1, //��
	 2, 3, //��
	 2, 0, //��
	 3, 1, //�E

	//-----
	//�E
	//-----
	 1, 4, //��
	 3, 5, //��
	 3, 1, //�E
	 5, 4, //��

	//-----
	//���
	//-----
	 6, 4, //��
	 7, 5, //��
	 7, 6, //��
	 5, 4, //�E

	 //-----
	 //��
	 //-----
	 0, 6, //��
	 2, 7, //��
	 7, 6, //��
	 2, 0, //�E
};

//������
void BoxCollision::Init()
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
	bd.ByteWidth = sizeof(VERTEX3D) * 16;
	//���_�o�b�t�@�[�Ƃ������Ƃ��������ߗp
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	//�ŏ��ɓ���Ă������_�o�b�t�@�[��ۑ�������
	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = g_VertexList;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//�C���f�b�N�X�o�b�t�@�[�̐���
	D3D11_BUFFER_DESC ibDesc{};
	ibDesc.Usage = D3D11_USAGE_DEFAULT;
	ibDesc.ByteWidth = sizeof(WORD) * 28;
	//�C���f�b�N�X�o�b�t�@�[�Ƃ������Ƃ��ؖ�
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA irDate{};
	irDate.pSysMem = g_IndexList;

	Renderer::GetDevice()->CreateBuffer(&ibDesc, &irDate, &m_IndexBuffer);

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
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
//�I��
void BoxCollision::UnInit()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_IndexShader->Release();
	m_IndexPixcelShader->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//�X�V
void BoxCollision::Update()
{
	Scene* scene = Manager::GetScene();
	//�v���C���[�̏����󂯎��
	std::vector<Player*> PlayerList = scene->GetGameObjects<Player>(1);
	for (Player* player : PlayerList)
	{
		D3DXVECTOR3 l_PlayerPosition = player->GetPosition();
		D3DXVECTOR3 l_PlayerRotation = player->GetRotation();
		//m_Position.x = enemyPosition.x - 0.8f;
		m_Position.x = l_PlayerPosition.x;
		m_Position.y = l_PlayerPosition.y;
		m_Position.z = l_PlayerPosition.z;
		Player* p_player = Manager::GetScene()->GetGameObject<Player>(1);
		m_TargetPos = l_PlayerPosition;

		//�G�ƃv���C���[�̋����̍������Z�o
		m_Direction.x = m_TargetPos.x - m_Position.x;
		m_Direction.z = m_TargetPos.z - m_Position.z;

		//���K��
		D3DXVec3Normalize(&m_Direction, &m_Direction);

		m_Angle = atan2(fabsf(m_TargetPos.z - m_Position.z), fabsf(m_TargetPos.x - m_Position.x));

		//�p�x�̍X�V
		m_Rotation.x = l_PlayerRotation.x;
		m_Rotation.y = l_PlayerRotation.y + 1.6f;
		m_Rotation.z = l_PlayerRotation.z;
	}
}

//�`��
void BoxCollision::Draw()
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
	Renderer::GetDeviceContext()->DrawIndexed(28, 0, 0);

}

