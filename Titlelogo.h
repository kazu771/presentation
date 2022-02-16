//=======================================================================================
//�^�C�g�����S��{����.h[TitleLogo.h]
//date:2021/07/13   name:Kazuki Wada
//=======================================================================================

#ifndef TITLELOGO_H_
#define TITLELOGO_H_

#include "GameObject.h"

//--------------
//�N���X��`
//--------------
class Titlelogo: public GameObject
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
	void ChangeArufa();
};

#endif // !TITLELOGO_H_
