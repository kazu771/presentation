//====================================================================================================================
//鍵基本処理.h[Door.h]
//date:2021/11/16   name:Kazuki Wada
//====================================================================================================================

#include "GameObject.h"

#ifndef KEY_H_
#define KEY_H_

class Key : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	void Collision();
	bool isActive();//取得したかどうかを送るよう
	
private:
	Model*				m_Key;	    //スピードアイテム用
	class Door*			m_Door;
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3			m_playerPos; //プレイヤーの座標を入れるよう
	D3DXVECTOR3			m_Direction; //プレイヤーの角度を入れる箱
	D3DXVECTOR3			m_Cross;
	float				m_angle;
	float				m_Speed;
	float				m_Rotations;  //回転用変数
	bool				m_isUse;
	bool				m_IsProof;   //鍵を使用したかどうか
	int					m_Cnt;       //エフェクト表示するよう
};


#endif // !KEY_H_

