//=========================================================================================================
//������̒e��{����.h[TwoWayBullet.h]
//date:2021/11/30     name:Kazuki Wada
//=========================================================================================================

#include "GameObject.h"

#ifndef TWOWAYBULLET_H_
#define TWOWAYBULLET_H_

class TwoWay : public GameObject
{
public:
	enum Two
	{
		BULLET_LEFT = 0,
		BULLET_RIGHT,
		BULLET_MAX
	};
	static void Load();
	static void UnLoad();
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:
	static class Model* m_Model;  //���f����ǂݍ��ނ��ߗp,cpp���ł������錾���s��(static�̂���)
	Two                 m_LeftSide;//���p
	Two                 m_RightSide;//�E�p
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3         m_Direction;
	int                 m_BulletsCnt;  //�c�i��
	int                 m_SpCnt;

};


#endif // !TWOWAYBULLET_H_
