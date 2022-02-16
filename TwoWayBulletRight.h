//=========================================================================================================
//������̒e��{����(�E).h[TwoWayBulletRight.h]
//date:2021/11/30     name:Kazuki Wada
//=========================================================================================================

#include "GameObject.h"

#ifndef TWOWAYBULLETRIGHT_H_
#define TWOWAYBULLETRIGHT_H_


class TwowayRIght: public GameObject
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
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3         m_Direction;
	int                 m_BulletsCnt;  //�c�i��
	int                 m_SpCnt;
};


#endif // !TWOWAYBULLETRIGHT_H_

