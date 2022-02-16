//======================================================================================
//ルールロゴ基本処理.h[RulrLogo.h]
//ate:2021/07/13  name:Kazuki Wada
//======================================================================================
#ifndef RULELOGO_H_
#define RULELOGO_H_

#include "GameObject.h"

//---------------
//クラス定義
//---------------

class RuleLogo : public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;	//頂点情報を入れるための領域
	ID3D11ShaderResourceView*	m_Texture = NULL;		//ポリゴンにはるものを保存する領域

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
public:

	void Init();
	void UnInit();
	void Update();
	void Draw();

};
#endif // !RURLELOGO_H_
