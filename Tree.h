//
//
//
//
#ifndef TREE_H_
#define TREE_H_

//
//�N���X��`
//
#include "GameObject.h"

class Tree : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:

	ID3D11Buffer*				m_VertexBuffer = NULL;	//���_�������邽�߂̗̈�
	ID3D11ShaderResourceView*	m_Texture = NULL;		//�|���S���ɂ͂���̂�ۑ�����̈�

	ID3D11VertexShader*			m_VertexShader = NULL;
	ID3D11PixelShader*			m_PixelShader = NULL;
	ID3D11InputLayout*			m_VertexLayout = NULL;
	int							m_Count;
};
#endif // !TREE_H_
