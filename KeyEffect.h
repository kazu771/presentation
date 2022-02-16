//====================================================================================================================
//鍵のエフェクト基本処理.h[KeyEffect.h]
//date:2021/11/17   name:Kauzki Wada
//====================================================================================================================
#ifndef KEYEFFECT_H_
#define KEYEFFECT_H_

#include "GameObject.h"

class KeyEffect : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:

	ID3D11Buffer*				m_VertexBuffer = NULL;	//頂点情報を入れるための領域
	ID3D11ShaderResourceView*	m_Texture      = NULL;	//ポリゴンにはるものを保存する領域
	ID3D11VertexShader*         m_VertexShader = NULL;
	ID3D11PixelShader*			m_PixelShader  = NULL;
	ID3D11InputLayout*			m_VertexLayout = NULL;
	int							m_Count;

};


#endif // !KEYEFFECT_H_

#pragma once
