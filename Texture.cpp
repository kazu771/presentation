// ===================================================================
// �e�N�X�`���[�Ǘ�[ texture.cpp ]
// date:2021/08/18     name:Kazuki Wada
// ===================================================================
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "assetnames.h"

ID3D11ShaderResourceView* Texture::m_Texture[TEXTURE_MAX]; //static�錾�������������x�錾

//������
void Texture::Init()
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		m_Texture[i] = NULL;
	}

	for (int i = 0; i < TX_MAX; i++)
	{
		Texture::Load(g_TextureFileName[i]);
	}
}

int Texture::Load(const char* pFileName)
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (m_Texture[i] == NULL)
		{
			// �e�N�X�`���̓ǂݍ���
			D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
				pFileName,
				NULL,
				NULL,
				&m_Texture[i],
				NULL);

			assert(m_Texture);

			return i;
		}
	}
	return INVALID_TEXTURE_ID;
}

//TX_�̂������
ID3D11ShaderResourceView* Texture::GetNum(int TextureNum)
{
	return m_Texture[TextureNum];
}

//���
void Texture::Uninit()
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (m_Texture[i])
		{
			m_Texture[i]->Release();
			m_Texture[i] = NULL;
		}
	}
}