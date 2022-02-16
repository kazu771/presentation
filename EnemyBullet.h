//======================================================================================
//敵の弾基本処理.h[EnemyBullet.h]
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

	static class Model* m_Model;       //モデルを読み込むため用,cpp側でもう一回宣言を行う(staticのため)
	class Spider* m_Spider;
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3         m_Direction;   //方向ベクトル
	int                 m_BulletsCnt;  //残段数

};
#endif // !ENEMYBULLET_H_
