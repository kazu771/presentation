////================================================================================================================
////��R���W������{����.h[RockCollision.h]
////date:2022/02/01           name:Kauzki Wada
////================================================================================================================
//#ifndef ROCKCOLLISION_H_
//#define ROCKCOLLISION_H_
//
//#include "GameObject.h"
//
//class RockCollision : public GameObject
//{
//private:
//	ID3D11Buffer*				m_VertexBuffer = NULL;	//���_�������邽�߂̗̈�
//	ID3D11Buffer*				m_IndexBuffer = NULL;   //�C���f�b�N�X�������邽�߂̗̈�
//
//	ID3D11ShaderResourceView*	m_Texture = NULL;		//�|���S���ɂ͂���̂�ۑ�����̈�
//
//	ID3D11VertexShader* m_VertexShader = NULL;
//	ID3D11PixelShader*  m_PixelShader = NULL;
//	ID3D11InputLayout*  m_VertexLayout = NULL;
//
//	ID3D11VertexShader* m_IndexShader = NULL;
//	ID3D11PixelShader* m_IndexPixcelShader = NULL;
//	D3DXVECTOR3 targetpos; //�v���C���[�̈ʒu���W������悤
//	D3DXVECTOR3 targetrot; //�v���C���[�̉�]��]�p�x
//	D3DXVECTOR3 Direction; //�v���C���[�̊p�x�����锠
//	D3DXVECTOR3 cross;
//	float  angle;     //�p�x
//	bool isVisible;  //�R���W������L�������邩�ǂ���
//
//public:
//	struct VERTEX3D
//	{
//		D3DXVECTOR3 pos; //���_���W
//		D3DXVECTOR3 nolmal; //�@��
//		D3DXVECTOR4 col; //�F
//		D3DXVECTOR2 texcode;
//	};
//	void Init();
//	void UnInit();
//	void Update();
//	void Draw();
//};
//#endif // !ROCKCOLLISION_H_
