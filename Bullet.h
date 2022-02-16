//==============================================================================================
//�v���C���[�̒e��{����.h[Bullet.h]
//date:2021/05/31   name:Kazuki Wada
//==============================================================================================

#include "GameObject.h"

#ifndef BULLET_H_
#define BULLET_H_

class Bullet: public GameObject
{
public:

	static void Load();
	static void UnLoad();
	void Init();
	void UnInit();
	void Update();
	void Draw();
	
private:

	static class Model* m_Model;  //���f����ǂݍ��ނ��ߗp,cpp���ł������錾���s��(static�̂���)
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3         m_Direction;
	int                 m_SpCnt;	  //�w偂��e�ɂ������Ƃ��̃J�E���g�p
	int					m_BulletsCnt;  //�c�i��
};
#endif // !BULLET_H_
