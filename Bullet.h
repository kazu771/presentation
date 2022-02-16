//==============================================================================================
//プレイヤーの弾基本処理.h[Bullet.h]
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

	static class Model* m_Model;  //モデルを読み込むため用,cpp側でもう一回宣言を行う(staticのため)
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3         m_Direction;
	int                 m_SpCnt;	  //蜘蛛が弾にあったときのカウント用
	int					m_BulletsCnt;  //残段数
};
#endif // !BULLET_H_
