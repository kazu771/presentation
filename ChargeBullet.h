//===============================================================================================================
//チャージ用弾基本処理[ChargeBullet.h]
//date:2022/01/18        name:Kazuki Wada
//===============================================================================================================
#ifndef CHARGEBULLET_H_
#define CHARGEBULLET_H_

#include "GameObject.h"
class ChargeBullet : public GameObject
{
public:

	static void Load();
	static void UnLoad();
	void Init();
	void UnInit();
	void Update();
	void Draw();
	int GetAttack() { return m_Attack; }//攻撃力を送る関数

private:
	static class Model* m_Model;       //モデルを読み込むため用,cpp側でもう一回宣言を行う(staticのため)
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3         m_Direction;  //方向ベクトル
	float               m_Cnt;		  //押してる時の時間取得用
	float				m_Speed;	  //弾のスピード
	int					m_BulletsCnt; //残段数
	int					m_SpCnt;	  //蜘蛛が弾にあったときのカウント用
	int					m_Attack;	  //攻撃力

	
};


#endif // !CHARGEBULLET_H_
