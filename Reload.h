//
//�����[�h�\����{����[Reload.h]
//date:2021/06/28   name:Kazuki Wada
//
#ifndef RELOAD_H_
#define RELOAD_H_

//
//�N���X��`
//
#include "GameObject.h"
class Reload : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	void Change(); //�\���̐؂�ւ�

private:
	ID3D11Buffer*				m_VertexBuffer = NULL;	//���_�������邽�߂̗̈�
	ID3D11ShaderResourceView*	m_Texture      = NULL;	//�|���S���ɂ͂���̂�ۑ�����̈�
	ID3D11VertexShader*         m_VertexShader = NULL;
	ID3D11PixelShader*			m_PixelShader  = NULL;
	ID3D11InputLayout*			m_VertexLayout = NULL;
	bool						m_IsUse;				//�\���A��\���̐؂�ւ��p

};
#endif // !RELOAD_H_

