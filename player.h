//======================================================================
//プレイヤー基本処理.h[player.h]
//date:2021/05/17     name:Kazuki Wada
//======================================================================

#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"

class Player : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	void ChangePoison();		  //プレイヤーの状態を変更するよう
	void ChangeConfusion();		  //プレイヤーの混乱状態を変更するよう
	void CollisionEnemyBullet();  //敵とプレイヤーの当たり判定
	void CollisuinPoisonBullet(); //毒の弾との当たり判定
	void ColllisionEnemy();       //プレイヤーと敵の当たり判定
	int GetHp() { return m_Hps; } //体力を送るよう
	bool Change;
	bool GetPoison() { return m_isPoison; }      //毒にかかってるかどうかの判定を送る関数
	bool GetChange() { return Change; }          //sceneを切り替えるよう
	bool GetConfusion() { return m_isConfusion; }//混乱変数を送るよう
	bool GetHpItem() { return m_isHpItem; }		 //HPフラグ送るよう
	bool GetCharge() { return m_isCharge; }		 //チャージフラグを送る用
	enum ArrowMode
	{
		ARROWMODE_NORMAL = 0,
		ARROWMODE_DOUBLE,
		ARROWMODE_TWOWAY,
		ARROWMODE_MAX
	};
	void ArrowModeChange();//フラグを変更するよう
	
	ArrowMode m_Mode;//矢の状態
private:
	class AnimetionModel* m_Model;		 //モデルを読み込むため用
	class Shadow*         m_Shadow;		 //影を読み込むよう
	class Speed*          m_Speed;       //スピードアイテム用
	class Camera*         m_Camera;      //カメラ用
	class BoxCollision*   m_collisions;
	class Audio*          m_shotse;		 //撃った時の音
	class Key*            m_Key;
	ID3D11VertexShader*   m_VertexShader = NULL;
	ID3D11PixelShader*    m_PixelShader  = NULL;
	ID3D11InputLayout*    m_VertexLayout = NULL;
	D3DXVECTOR3           m_site;
	D3DXVECTOR3			  m_GTraget;	 //銃の方向を受け取る
	D3DXVECTOR3           m_Forward;
	float                 m_speed;		 //スピード
	bool                  m_isConfusion; //混乱しているかどうか
	bool                  m_isEmote;	 //エモートフラグ,false:歩くモード,true:エモート
	bool                  m_isPoison;	 //毒の状態に変更
	bool				  m_isHpItem;    //アイテムを取得したかどうか
	bool				  m_IsSp;        //スピードアイテム取得したかどうか
	bool				  m_isCharge;    //チャージしてるかどうか
	bool				  m_isKey;	     //鍵取得フラグ
	bool				  m_isCheck;  	 //カギを使用したかどうか
	bool				  m_isDeath;	 //死亡フラグ
	int				      m_PoisonCnt;   //毒用カウント
	int					  m_Frame;       //アニメーション再生用
	int					  m_Hps;         //体力
	int				      m_Cnt;	     //混乱カウント用
	int					  m_HItemCnt;    //体力アイテムカウント用
	int				      m_EmCnt;	     //エモート用カウント
	void CollisionSpeed();				 //スピードアイテムとのあり判定
	void GetItem();						 //プレイヤーと弾の当たり判定
	void Behavior();					 //プレイヤーの操作をまとめる関数
	void PoisonDamge(float Dameg);
	void Confusion(int Cnt);			 //混乱用関数
	void CollisionConfuse();
	void CollisionHpItem();			     //回復アイテムとの当たり判定
	void CollisionDoor();				 //扉との当たり判定
	void HpItemProcess();				 //回復する処理
	void CollisionStateBullet();
	bool SetPosion();					 //状態を送る→毒状態になったらテクスチャーアニメーションを表示するため
};

#endif // !PLAYER_H_