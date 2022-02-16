//===============================================================================================================
//�`���[�W�p�e��{����[ChargeBullet.h]
//date:2022/01/18        name:Kazuki Wada
//===============================================================================================================
#ifndef CHARGEBULLET_H_
#define CHARGEBULLET_H_

#include "GameObject.h"
class ChargeBullet : public GameObject
{
public:

	static void Load();
	static void UnLoad();
	void Init();
	void UnInit();
	void Update();
	void Draw();
	int GetAttack() { return m_Attack; }//�U���͂𑗂�֐�

private:
	static class Model* m_Model;       //���f����ǂݍ��ނ��ߗp,cpp���ł������錾���s��(static�̂���)
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3         m_Direction;  //�����x�N�g��
	float               m_Cnt;		  //�����Ă鎞�̎��Ԏ擾�p
	float				m_Speed;	  //�e�̃X�s�[�h
	int					m_BulletsCnt; //�c�i��
	int					m_SpCnt;	  //�w偂��e�ɂ������Ƃ��̃J�E���g�p
	int					m_Attack;	  //�U����

	
};


#endif // !CHARGEBULLET_H_
