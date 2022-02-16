//=========================================================================================================
//二方向の弾基本処理.h[TwoWayBullet.h]
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
	static class Model* m_Model;  //モデルを読み込むため用,cpp側でもう一回宣言を行う(staticのため)
	Two                 m_LeftSide;//左用
	Two                 m_RightSide;//右用
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3         m_Direction;
	int                 m_BulletsCnt;  //残段数
	int                 m_SpCnt;

};


#endif // !TWOWAYBULLET_H_
