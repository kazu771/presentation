//
//==================================================================================================
//混乱する弾基本処理.h[ConfusionBullet.h]
//date:2021/12/14    name:Kazuki Wada
//==================================================================================================
#ifndef STATEBULLET_H_
#define STATEBULLET_H_

#include "GameObject.h"

class StateBullet : public GameObject
{
public:
	static void Load();
	static void UnLoad();
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:
	static class Model* m_Model;  //モデルを読み込むため用,cpp側でもう一回宣言を行う(staticのため)
	class Enemy*        m_Enemy;
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3         m_Direction;
	bool                m_IsAttack;
	int                 m_BulletsCnt;  //残段数
};

#endif