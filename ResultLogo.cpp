//
//	���U���g��{����.cpp[Titlelogo.cpp]
//date:2021/07/01    nane:Kazuki Wada
//

#include "main.h"
#include "renderer.h"
#include "ResultLogo.h"

void Resultlogo::Init()
{

	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//����
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�@��
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f); //���_�̐F,�O����RGBA
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);//�e�N�X�`���[�̂͂�ʒu

	vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);//�E��
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�@��
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //�e�N�X�`���[�̐F
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);//�e�N�X�`���[�̂͂�ʒu

	vertex[2].Position = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);//����
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�@��
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //�e�N�X�`���[�̐F
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);//�e�N�X�`���[�̂͂�ʒu

	vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);//�E��
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //�@��
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //�e�N�X�`���[�̐F
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);//�e�N�X�`���[�̂͂�ʒu


	//���_�o�b�t�@�[�̐���
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	//���_�o�b�t�@�[�̃T�C�Y
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
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
		"asset/texture/result.png",
		NULL,
		NULL,
		&m_Texture,
		NULL
	);
	//��O�����p
	assert(m_Texture);

	//2D�|���S���p�V�F�[�_�[
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");
}

void Resultlogo::UnInit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Resultlogo::Update()
{

}

void Resultlogo::Draw()
{
	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�}�g���N�X�̐ݒ�
	Renderer::SetWorldViewProjection2D();

	//���_�o�b�t�@�[�̐ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

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