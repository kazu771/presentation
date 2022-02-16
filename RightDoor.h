//====================================================================================================================
//ドア基本処理.h[RightDoor.h]
//date:2021/11/18  name:Kazuki Wada
//====================================================================================================================
#include "GameObject.h"

#ifndef RIGHTDOOR_H_
#define RIGHTDOOR_H_


class RightDoor : public GameObject
{
public:
	enum DoorType
	{
		DoorType_Right = 0,
		DoorType_Left,
		DoorType_Max,
	};
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:

	class Model*		m_Door;    //スピードアイテム用
	class Key*			m_Key;     //鍵用
	class Player*		m_Player;
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	bool				m_isActive; //true:横に移動,false:動かない
	bool				m_Chack;    //プレイヤーが鍵を取得したかどうか判定用
	int					m_Cnt;      //ドアを動かすときのカウント用
};


#endif // !RIGHTDOOR_H_

