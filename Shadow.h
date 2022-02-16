//================================================================================================
//‰eŠî–{ˆ—.h[Shadow.h]
//date:2021/07/05   name:Kazuki Wada
//================================================================================================
#ifndef SHADOW_H_
#define SHADOW_H_

#include "GameObject.h"

class Shadow : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:

	ID3D11Buffer*				m_VertexBuffer = NULL;	//’¸“_î•ñ‚ğ“ü‚ê‚é‚½‚ß‚Ì—Ìˆæ
	ID3D11ShaderResourceView*	m_Texture = NULL;		//ƒ|ƒŠƒSƒ“‚É‚Í‚é‚à‚Ì‚ğ•Û‘¶‚·‚é—Ìˆæ

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
};

#endif // !SHADOW_H_
