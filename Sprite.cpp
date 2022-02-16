//=============================================================================
//  �X�v���C�g�`�� [Sprite.h]
//  Date:2021/08/18   name:Kazuki Wada
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "sprite.h"

ID3D11Buffer* Sprite::m_VertexBuffer = NULL;
ID3D11VertexShader* Sprite::m_VertexShader = NULL;
ID3D11PixelShader* Sprite::m_PixelShader = NULL;
ID3D11InputLayout* Sprite::m_VertexLayout = NULL;

void Sprite::Init()
{
	Load();
}

void Sprite::Uninit()
{
	if (m_VertexShader)
	{
		m_VertexShader->Release();
	}
	if (m_PixelShader)
	{
		m_PixelShader->Release();
	}
	if (m_VertexLayout)
	{
		m_VertexLayout->Release();
	}
}

void Sprite::Update()
{

}

void Sprite::Load()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");
}


//1:ID, 2:X���W, 3:y���W, 4:����, 5:����,6:�؂���x,7:�؂���y
//8:�؂��艡��, 9:�؂���c��, 10:��, 11:��, 12:��, 13:�A���t�@�l
void Sprite::Draw(ID3D11ShaderResourceView* textureId, float x, float y, float width, float height,
	float tx, float ty, 
	float tw, float th,
	float RED, float GREEN, float BLUE, float ALPHA)
{
	x += SCREEN_WIDTH * 0.5f;
	y += SCREEN_HEIGHT * 0.5f;

	float w, h;
	w = width * 0.5f;
	h = height * 0.5f;

	// ���_�̐ݒ�
	VERTEX_3D vertex[4];

	//Z�����ɏ����Ă���
	vertex[0].Position = D3DXVECTOR3(x - w, y - h, 0.0f); 
	vertex[1].Position = D3DXVECTOR3(x + w, y - h, 0.0f); 
	vertex[2].Position = D3DXVECTOR3(x - w, y + h, 0.0f); 
	vertex[3].Position = D3DXVECTOR3(x + w, y + h, 0.0f); 

	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	vertex[0].Diffuse = D3DXVECTOR4(RED, GREEN, BLUE, ALPHA);
	vertex[1].Diffuse = D3DXVECTOR4(RED, GREEN, BLUE, ALPHA);
	vertex[2].Diffuse = D3DXVECTOR4(RED, GREEN, BLUE, ALPHA);
	vertex[3].Diffuse = D3DXVECTOR4(RED, GREEN, BLUE, ALPHA);


	//�؂�����W
	vertex[0].TexCoord = D3DXVECTOR2(tx, ty);
	vertex[1].TexCoord = D3DXVECTOR2(tx + tw, ty);
	vertex[2].TexCoord = D3DXVECTOR2(tx, ty + th);
	vertex[3].TexCoord = D3DXVECTOR2(tx + tw, ty + th);

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	Renderer::SetMaterial(material);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &textureId);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);

	m_VertexBuffer->Release();

}


//1:ID, 2:X���W, 3:y���W, 4:����, 5:����,6:�؂���x,7:�؂���y
//8:�؂��艡��, 9:�؂���c��, 10:��, 11:��, 12:��, 13:�A���t�@�l
void Sprite::Draws(ID3D11ShaderResourceView* textureId, float x, float y, float width, float height,
	float tx, float ty,
	float tw, float th,
	float RED, float GREEN, float BLUE, float ALPHA)
{
	x += SCREEN_WIDTH * 0.5f;
	y += SCREEN_HEIGHT * 0.5f;

	float w, h;
	w = width;
	h = height;

	// ���_�̐ݒ�
	VERTEX_3D vertex[4];

	//Z�����ɏ����Ă���
	vertex[0].Position = D3DXVECTOR3(x, y - h, 0.0f);
	vertex[1].Position = D3DXVECTOR3(x + w, y - h, 0.0f);
	vertex[2].Position = D3DXVECTOR3(x, y + h, 0.0f);
	vertex[3].Position = D3DXVECTOR3(x + w, y + h, 0.0f);

	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	vertex[0].Diffuse = D3DXVECTOR4(RED, GREEN, BLUE, ALPHA);
	vertex[1].Diffuse = D3DXVECTOR4(RED, GREEN, BLUE, ALPHA);
	vertex[2].Diffuse = D3DXVECTOR4(RED, GREEN, BLUE, ALPHA);
	vertex[3].Diffuse = D3DXVECTOR4(RED, GREEN, BLUE, ALPHA);


	//�؂�����W
	vertex[0].TexCoord = D3DXVECTOR2(tx, ty);
	vertex[1].TexCoord = D3DXVECTOR2(tx + tw, ty);
	vertex[2].TexCoord = D3DXVECTOR2(tx, ty + th);
	vertex[3].TexCoord = D3DXVECTOR2(tx + tw, ty + th);

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	Renderer::SetMaterial(material);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &textureId);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);

	m_VertexBuffer->Release();

}

