//=============================================
//敵基本処理.h[Enemy.h]
//date;2021/05/24
//============================================
#ifndef SPIDER_H_
#define SPIDER_H_

#include "GameObject.h"

//------------------------
//定数定義
//------------------------


//------------------------
//クラス定義
//------------------------

class Spider : public GameObject
{
public:
	enum ENEMYSTATE
	{
		STATE_WALK = 0,
		STATE_ATTACK,
		STATE_MAX,
	};
	void Init();
	void UnInit();
	void Update();
	void Draw();
	int  SetHp();

private:
	#define SPEED_MAX (1.0f)
	class AnimetionModel* m_Model;  //モデルを読み込むため用
	class BoxCollision*   m_Collision; //コリジョン用
	ID3D11VertexShader*   m_VertexShader = NULL;
	ID3D11PixelShader*    m_PixelShader = NULL;
	ID3D11InputLayout*    m_VertexLayout = NULL;
	D3DXVECTOR3			  m_TargetPos; //プレイヤーの位置座標を入れるよう
	D3DXVECTOR3			  m_Direction; //プレイヤーの角度を入れる箱
	D3DXVECTOR3			  m_Site;      //プレイヤーの見てる方向を取得
	D3DXVECTOR3			  m_Cross;
	ENEMYSTATE			  m_State;     //敵のステートを入れる箱
	float				  m_Angle;     //角度
	float				  m_Speed;     //速さ
	float				  m_playerposx;
	float				  m_playerposz;
	float				  HPs;
	bool			      m_IsAngle;
	bool				  m_IsEscape;   //逃げるようの処理
	bool				  m_IsAttack;
	int					  m_Cnt;		//Idleでいる時間
	int					  m_AttckCnt;
	int					  m_frame;      //アニメーション用
	int					  m_EsCnt;
	void State();			            //敵の行動処理
	void Walk();
	void Attack();
	void CollisionCharge();             //チャージバレットとの当たり判定
	void CollisionBullet();
	void CollisionTwoWay();
};

#endif // !ENEMY_H_

