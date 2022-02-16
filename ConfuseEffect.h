//===============================================================================================================
//�����G�t�F�N�g�e�N�X�`���[��{����.h[ConfuseEffect]
//date:2021/01/21            name:Kazuki Wada
//===============================================================================================================
#ifndef CONFUSEEFFECT_H_
#define CONFUSEEFFECT_H_
#include "GameObject.h"

class ConfuseEffect : public GameObject
{
public:

	void Init();
	void UnInit();
	void Update();
	void Draw();

private:
	ID3D11Buffer*				m_VertexBuffer = NULL;	//���_�������邽�߂̗̈�
	ID3D11ShaderResourceView*	m_Texture      = NULL;	//�|���S���ɂ͂���̂�ۑ�����̈�
	ID3D11VertexShader*         m_VertexShader = NULL;
	ID3D11PixelShader*			m_PixelShader  = NULL;
	ID3D11InputLayout*			m_VertexLayout = NULL;
	bool						m_isUse;
	int							m_Count;

};


#endif // !CONFUSEEFFECT_H_
