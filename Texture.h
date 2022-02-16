#pragma once
//=============================================================================
//
//  �e�N�X�`���[�Ǘ� [texture.cpp]
//  Author : ����E�l
//  Date   : 2021 / 07 / 25
//
//=============================================================================
#pragma once
#ifndef TEXTURE_H_
#define TEXTURE_H_


#define TEXTURE_MAX				(1024)		// �e�N�X�`���[���[�h�ő吔
#define TEXTURE_FILENAME_MAX	(256)		// �e�N�X�`���[�t�@�C�����ő啶����
#define INVALID_TEXTURE_ID		(-1)		// �����ȃe�N�X�`���Ǘ��ԍ�

//******************************************************************************
// �N���X��`
//******************************************************************************
class Texture
{
private:
	static ID3D11ShaderResourceView* m_Texture[TEXTURE_MAX];

public:
	//static�ɂ����new�ɂ��Ȃ��Ă��g����
	static void Init();
	static void Uninit();
	static int Load(const char* pFileName);
	static ID3D11ShaderResourceView* GetNum(int TextureNum);
};

#endif // !TEXTURE_H_