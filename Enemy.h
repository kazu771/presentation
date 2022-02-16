//=============================================
//敵基本処理.h[Enemy.h]
//date;2021/05/24
//============================================
#ifndef ENEMY_H_
#define ENEMY_H_

#include "GameObject.h"

//------------------------
//定数定義
//------------------------
#define ENEMY_MODELS (3)
#define SPEED_MAX (1.0f)

//------------------------
//クラス定義
//------------------------

class Enemy : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:
	enum STATACE
	{
		STATACE_WALK = 0,
		STATACE_ATTACK,
		STATACE_MAX,
	};
	class AnimetionModel* m_Models;    //モデルを読み込むため用
	class BoxCollision*   m_Collision; //コリジョン用
	ID3D11VertexShader*   m_VertexShader = NULL;
	ID3D11PixelShader*    m_PixelShader  = NULL;
	ID3D11InputLayout*    m_VertexLayout = NULL;
	D3DXVECTOR3           m_TargetPos; //プレイヤーの位置座標を入れるよう
	D3DXVECTOR3           m_Direction; //プレイヤーの角度を入れる箱
	D3DXVECTOR3           m_Cross;
	STATACE               m_State;	   //敵のステートを入れる箱
	float                 m_Angle;	   //角度
	float                 m_Speed;	   //速さ
	float                 m_PlayerPosx;
	float                 m_PlayerPosz;
	float                 m_Hpss;
	bool                  m_IsAngle;
	bool                  m_IsAttack;
	bool                  m_IsEscape;  //逃げるようの処理
	int                   HPs;
	int                   m_frame;	   //アニメーション用
	int	                  m_Cnt;	   //Idleでいる時間
	int	                  m_AttackCnt;
	void State();						//敵の行動処理
	void Walk();
	void Attack();
	

};

#endif // !ENEMY_H_

