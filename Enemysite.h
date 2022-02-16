//==================================================================================================
//敵の視線基本処理.h[ENEMYSITE.h]
//date:2021/10/01   name:Kazuki Wada
//==================================================================================================
#ifndef ENEMYSITE_H_
#define ENEMYSITE_H_


#include "GameObject.h"


//------------------------
//クラス定義
//------------------------

class Enemysite : public GameObject
{
private:
	static	class Model* m_Model;  //モデルを読み込むため用
	class BoxCollision* m_Collision; //コリジョン用
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3 m_Enemypos; //敵の位置座標を入れるよう
	D3DXVECTOR3 m_Enemyrot; //敵のの角度
	D3DXVECTOR3 m_Playerpos;//プレイヤーの座標をとるよう
	float  angle;     //角度
	float Speed;      //速さ
	D3DXVECTOR3 cross;
	//MODE mode; //敵のモデルを変えるよう
	int HPs;
	bool m_isAttack;
	void Collision(); //プレイヤーとの当たり判定用

public:
	static void Load();
	static void UnLoad();
	void Init();
	void UnInit();
	void Update();
	void Draw();
};

#endif // !ENEMYSITE_H_
