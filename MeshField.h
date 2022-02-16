//---------------------------
//3D�|���S���`�揈��
//---------------------------
#pragma once

#include "gameObject.h"

class MeshField : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	float GetHeight(D3DXVECTOR3 Position);

private:
	ID3D11Buffer*             m_VertexBuffer = NULL;
	ID3D11Buffer*             m_IndexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture     = NULL; //�e�N�X�`���Ǘ��p

	ID3D11VertexShader*       m_VertexShader = NULL;
	ID3D11PixelShader*        m_PixelShader  = NULL;
	ID3D11InputLayout*        m_VertexLayout = NULL;


	VERTEX_3D m_Vertex[21][21];//���_�z��

};