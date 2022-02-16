#pragma once
//=============================================================================
//
//  テクスチャー管理 [texture.cpp]
//  Author : 今井勇斗
//  Date   : 2021 / 07 / 25
//
//=============================================================================
#pragma once
#ifndef TEXTURE_H_
#define TEXTURE_H_


#define TEXTURE_MAX				(1024)		// テクスチャーロード最大数
#define TEXTURE_FILENAME_MAX	(256)		// テクスチャーファイル名最大文字数
#define INVALID_TEXTURE_ID		(-1)		// 無効なテクスチャ管理番号

//******************************************************************************
// クラス定義
//******************************************************************************
class Texture
{
private:
	static ID3D11ShaderResourceView* m_Texture[TEXTURE_MAX];

public:
	//staticにするとnewにしなくても使える
	static void Init();
	static void Uninit();
	static int Load(const char* pFileName);
	static ID3D11ShaderResourceView* GetNum(int TextureNum);
};

#endif // !TEXTURE_H_