//==================================================================================================
//��������e��{����.h[ConfusionBullet.h]
//date:2021/12/14    name:Kazuki Wada
//==================================================================================================
#ifndef CONFUSIONBULLET_H_
#define CONFUSIONBULLET_H_

#include "GameObject.h"

class ConfusionBullet : public GameObject
{
public:
	static void Load();
	static void UnLoad();
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:
	static class Model* m_Model;      //���f����ǂݍ��ނ��ߗp,cpp���ł������錾���s��(static�̂���)
	class Enemy* m_Enemy;
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3			m_Direction;
	bool				m_isAttack;
	int					m_BulletsCnt; //�c�i��
	
};


#endif
