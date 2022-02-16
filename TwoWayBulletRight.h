//=========================================================================================================
//二方向の弾基本処理(右).h[TwoWayBulletRight.h]
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
	static class Model* m_Model;  //モデルを読み込むため用,cpp側でもう一回宣言を行う(staticのため)
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3         m_Direction;
	int                 m_BulletsCnt;  //残段数
	int                 m_SpCnt;
};


#endif // !TWOWAYBULLETRIGHT_H_

