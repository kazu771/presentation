#pragma once
//
//������{����.h[Explosion.h]
//dat:2021/06/21     name:Kazuki Wada
//


#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "GameObject.h"

class Explosion: public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:

	ID3D11Buffer*				m_VertexBuffer = NULL;	//���_�������邽�߂̗̈�
	ID3D11ShaderResourceView*	m_Texture      = NULL;	//�|���S���ɂ͂���̂�ۑ�����̈�
	ID3D11VertexShader*			m_VertexShader = NULL;
	ID3D11PixelShader*			m_PixelShader  = NULL;
	ID3D11InputLayout*			m_VertexLayout = NULL;
	bool						m_isUse;
	int							m_Count;

};



#endif // !EXPLOSION_H_
