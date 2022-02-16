//======================================================================================
//���j���[���S��{����.h[MenuLogo.h]
//date:2021/07/12  name:Kazuki Wada
//======================================================================================
#ifndef MENULOGO_H_
#define MENULOGO_H_

#include "GameObject.h"


//
//�N���X��`
//
class Menulogo : public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;	//���_�������邽�߂̗̈�
	ID3D11ShaderResourceView*	m_Texture = NULL;		//�|���S���ɂ͂���̂�ۑ�����̈�

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	float arufa;
public:

	void Init();
	void UnInit();
	void Update();
	void Draw();

};


#endif // !MENULOGO_H_

