
//==============================================================================================
//壁の基本処理.h[Wall.h]
//date;2021/05/11   name:Kazuki Wada
//==============================================================================================
#ifndef WALL_H_
#define WALL_H_


#include "GameObject.h"

class Wall : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
private:
	
	ID3D11Buffer*				m_VertexBuffer = NULL;	//頂点情報を入れるための領域
	ID3D11ShaderResourceView*	m_Texture      = NULL;	//ポリゴンにはるものを保存する領域

	ID3D11VertexShader*			m_VertexShader = NULL;
	ID3D11PixelShader*			m_PixcelShader = NULL;
	ID3D11InputLayout*			m_VertexLayout = NULL;
};

#endif // !WALL_H_