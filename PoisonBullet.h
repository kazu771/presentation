//==============================================================================================
//�v���C���[�̒e��{����.h[Bullet.h]
//date:2021/05/31   name:Kazuki Wada
//==============================================================================================

#include "GameObject.h"

#ifndef POISONBULLET_H_
#define POISONBULLET_H_

class PoisonBullet : public GameObject
{
public:
	static void Load();
	static void UnLoad();
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:
	static class Model* m_Model;       //���f����ǂݍ��ނ��ߗp,cpp���ł������錾���s��(static�̂���)
	class Dmage*        m_Damage;	   //�_���[�W�N���X�̊֐����g������
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3         m_Direction;   //�����x�N�g��
	bool				m_IsActive;
};
#endif // !BULLET_H_
