//===================================================================================================================
//�h�A�p�R���W������{����.h[DoorCollision.h]
//date:2022/01/11     name:Kauzki Wada
//===================================================================================================================
#ifndef DOORCOLLISION_H_
#define DOORCOLLISION_H_

#include "GameObject.h"

class DoorCollision : public GameObject
{
public:
	struct VERTEX3D
	{
		D3DXVECTOR3 Pos; //���_���W
		D3DXVECTOR3 Nolmal; //�@��
		D3DXVECTOR4 Col; //�F
		D3DXVECTOR2 TexCode;
	};
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:
	ID3D11Buffer*				m_VertexBuffer = NULL;	//���_�������邽�߂̗̈�
	ID3D11Buffer*				m_IndexBuffer = NULL;   //�C���f�b�N�X�������邽�߂̗̈�
	ID3D11ShaderResourceView*	m_Texture = NULL;		//�|���S���ɂ͂���̂�ۑ�����̈�
	ID3D11VertexShader*			m_VertexShader = NULL;
	ID3D11PixelShader*			m_PixelShader = NULL;
	ID3D11InputLayout*			m_VertexLayout = NULL;
	ID3D11VertexShader*			m_IndexShader = NULL;
	ID3D11PixelShader*			m_IndexPixcelShader = NULL;
	D3DXVECTOR3					m_TargetPos; //�v���C���[�̈ʒu���W������悤
	D3DXVECTOR3					m_TargetRot; //�v���C���[�̉�]��]�p�x
	D3DXVECTOR3					m_Direction; //�v���C���[�̊p�x�����锠
	D3DXVECTOR3					m_Cross;
	float						m_Angle;     //�p�x
	bool						m_IsVisible;  //�R���W������L�������邩�ǂ���

};
#endif // !DOORCOLLISION_H_
