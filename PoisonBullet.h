//==============================================================================================
//プレイヤーの弾基本処理.h[Bullet.h]
//date:2021/05/31   name:Kazuki Wada
//==============================================================================================

#include "GameObject.h"

#ifndef POISONBULLET_H_
#define POISONBULLET_H_

class PoisonBullet : public GameObject
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
	class Dmage*        m_Damage;	   //ダメージクラスの関数を使うため
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3         m_Direction;   //方向ベクトル
	bool				m_IsActive;
};
#endif // !BULLET_H_
