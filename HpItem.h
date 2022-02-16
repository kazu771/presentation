//==============================================================================================================
//体力アイテム基本処理.h[HpItem.h]
//date:2021/12/14    name:Kazuki Wada
//==============================================================================================================
#ifndef HPITEM_H_
#define HPITEM_H_

#include "GameObject.h"

class HpItem : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	bool GetHpItem() { return m_isHp; } //Hpアイテム取得変数を送る関数
private:
	class Model*		m_MHp;          //スピードアイテム用
	class Player*		m_Player;
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	float				m_rotations;    //回転用変数
	float				m_Cnt;
	bool				m_isHp;         //取得したかどうか
	void ChangeFlag();                  //フラグを変更するよう
};


#endif // !HPITEM_H_
