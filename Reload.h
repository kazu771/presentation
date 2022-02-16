//
//リロード表示基本処理[Reload.h]
//date:2021/06/28   name:Kazuki Wada
//
#ifndef RELOAD_H_
#define RELOAD_H_

//
//クラス定義
//
#include "GameObject.h"
class Reload : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	void Change(); //表示の切り替え

private:
	ID3D11Buffer*				m_VertexBuffer = NULL;	//頂点情報を入れるための領域
	ID3D11ShaderResourceView*	m_Texture      = NULL;	//ポリゴンにはるものを保存する領域
	ID3D11VertexShader*         m_VertexShader = NULL;
	ID3D11PixelShader*			m_PixelShader  = NULL;
	ID3D11InputLayout*			m_VertexLayout = NULL;
	bool						m_IsUse;				//表示、非表示の切り替え用

};
#endif // !RELOAD_H_

