//
//ポリゴン基本処理.h[polygon.h]
//date:2021/4/26     name:Kazuki Wada
//
#pragma once
#include "GameObject.h"
class Polygon2D : public GameObject
{
public:

	void Init();
	void UnInit();
	void Update();
	void Draw();
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;	//頂点情報を入れるための領域
	ID3D11ShaderResourceView*	m_Texture      = NULL;  //ポリゴンにはるものを保存する領域

	ID3D11VertexShader*			m_VertexShader = NULL;
	ID3D11PixelShader*			m_PixelShader  = NULL;
	ID3D11InputLayout*			m_VertexLayout = NULL;
};