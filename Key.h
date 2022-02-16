//====================================================================================================================
//����{����.h[Door.h]
//date:2021/11/16   name:Kazuki Wada
//====================================================================================================================

#include "GameObject.h"

#ifndef KEY_H_
#define KEY_H_

class Key : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	void Collision();
	bool isActive();//�擾�������ǂ����𑗂�悤
	
private:
	Model*				m_Key;	    //�X�s�[�h�A�C�e���p
	class Door*			m_Door;
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3			m_playerPos; //�v���C���[�̍��W������悤
	D3DXVECTOR3			m_Direction; //�v���C���[�̊p�x�����锠
	D3DXVECTOR3			m_Cross;
	float				m_angle;
	float				m_Speed;
	float				m_Rotations;  //��]�p�ϐ�
	bool				m_isUse;
	bool				m_IsProof;   //�����g�p�������ǂ���
	int					m_Cnt;       //�G�t�F�N�g�\������悤
};


#endif // !KEY_H_

