//=======================================================================================
//タイトルロゴ基本処理.h[TitleLogo.h]
//date:2021/07/13   name:Kazuki Wada
//=======================================================================================

#ifndef TITLELOGO_H_
#define TITLELOGO_H_

#include "GameObject.h"

//--------------
//クラス定義
//--------------
class Titlelogo: public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;	//頂点情報を入れるための領域
	ID3D11ShaderResourceView*	m_Texture = NULL;		//ポリゴンにはるものを保存する領域

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;

	float arufa;
public:

	void Init();
	void UnInit();
	void Update();
	void Draw();
	void ChangeArufa();
};

#endif // !TITLELOGO_H_
