//
//�ǂ̊�{����.cpp[Wall]
//
//
#include "main.h"
#include "renderer.h"
#include "Wall.h"

void Wall::Init()
{
	VERTEX_3D vertex[8];
	//���̕�
	vertex[0].Position = D3DXVECTOR3(-10.0f, 10.0f, 10.0f);   //����
	vertex[0].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //�@��
	vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f); //���_�̐F,�O����RGBA
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);             //�e�N�X�`���[�̂͂�ʒu

	vertex[1].Position = D3DXVECTOR3(10.0f, 10.0f, 10.0f);    //�E��
	vertex[1].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //�@��
	vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f); //�e�N�X�`���[�̐F
	vertex[1].TexCoord = D3DXVECTOR2(10.0f, 0.0f);			  //�e�N�X�`���[�̂͂�ʒu

	vertex[2].Position = D3DXVECTOR3(-10.0f, 0.0f, 10.0f);    //����
	vertex[2].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //�@��
	vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f); //�e�N�X�`���[�̐F
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 10.0f);			  //�e�N�X�`���[�̂͂�ʒu

	vertex[3].Position = D3DXVECTOR3(10.0f, 0.0f, 10.0f);     //�E��
	vertex[3].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //�@��
	vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f); //�e�N�X�`���[�̐F
	vertex[3].TexCoord = D3DXVECTOR2(10.0f, 10.0f);           //�e�N�X�`���[�̂͂�ʒu

	//�E�̕�
	vertex[4].Position = D3DXVECTOR3(10.0f, 10.0f, 10.0f);    //����
	vertex[4].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //�@��
	vertex[4].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f); //���_�̐F,�O����RGBA
	vertex[4].TexCoord = D3DXVECTOR2(0.0f, 0.0f);             //�e�N�X�`���[�̂͂�ʒu

	vertex[5].Position = D3DXVECTOR3(10.0f, 10.0f, -10.0f);   //�E��
	vertex[5].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //�@��
	vertex[5].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f); //�e�N�X�`���[�̐F
	vertex[5].TexCoord = D3DXVECTOR2(10.0f, 0.0f);			  //�e�N�X�`���[�̂͂�ʒu

	vertex[6].Position = D3DXVECTOR3(10.0f, 0.0f, 10.0f);     //����
	vertex[6].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //�@��
	vertex[6].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f); //�e�N�X�`���[�̐F
	vertex[6].TexCoord = D3DXVECTOR2(0.0f, 10.0f);			  //�e�N�X�`���[�̂͂�ʒu

	vertex[7].Position = D3DXVECTOR3(10.0f, 0.0f, -10.0f);    //�E��
	vertex[7].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //�@��
	vertex[7].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f); //�e�N�X�`���[�̐F
	vertex[7].TexCoord = D3DXVECTOR2(10.0f, 10.0f);           //�e�N�X�`���[�̂͂�ʒu

	//���_�o�b�t�@�[�̐���
	D3D11_BUFFER_DESC bd{};
	//ZeroMemory();
	bd.Usage = D3D11_USAGE_DEFAULT;
	//���_�o�b�t�@�[�̃T�C�Y
	bd.ByteWidth = sizeof(VERTEX_3D) * 8;  //�o�b�t�@�[�̃T�C�Y�����₳�Ȃ��ƎO�p�`�������Ȃ�4���ƈ�A8���Ɠ��
	//���_�o�b�t�@�[�Ƃ������Ƃ��������ߗp
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	//�ŏ��ɓ���Ă������_�o�b�t�@�[��ۑ�������
	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//�e�N�X�`���[�̓ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetDevice(),
		"asset/texture/yuka.jpg",
		NULL,
		NULL,
		&m_Texture,
		NULL
	);
	//��O�����p
	assert(m_Texture);

	//3D�|���S���p�V�F�[�_�[
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixcelShader, "vertexLightingPS.cso");

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

void Wall::UnInit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixcelShader->Release();
}

void Wall::Draw()
{
	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixcelShader, NULL, 0);

	//�}�g���N�X�̐ݒ�
	D3DXMATRIX wold, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//�O����y, x, z�̏��Őݒ肵�Ă���
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	wold = scale * rot * trans;
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
	Renderer::GetDeviceContext()->Draw(8, 0);
}


void Wall::Update()
{

}