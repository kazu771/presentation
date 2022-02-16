//======================================================================================
//�G�̒e��{����.h[EnemyBullet.h]
//date:2021/07/14   name:Kazuki Wada
//======================================================================================
#ifndef ENEMYBULLET_H_
#define ENEMYBULLET_H_

#include "GameObject.h"


class EnemyBullet : public GameObject
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
	class Spider* m_Spider;
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3         m_Direction;   //�����x�N�g��
	int                 m_BulletsCnt;  //�c�i��

};
#endif // !ENEMYBULLET_H_
