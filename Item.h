//==============================================================================================
//アイテム基本処理.h[Item.h]
//date:2021/05/31      name:Kazuki Wada
//==============================================================================================
#ifndef ITEM_H_
#define ITEM_H_



#include "GameObject.h"


class Item: public GameObject
{

public:
	typedef enum
	{
		TYPE_NORMAL,
		ITEM_RIPEA,
		ITEM_ATTACK,
		ITEM_MAX
	}ITEMTYPE;
	void Init();
	void UnInit();
	void Update();
	void Draw();
	ITEMTYPE GetItemMode() { return Type; } //アイテムのゲッター
private:
	Model*				m_Heart;  //体力アイテム用
	Model*				m_Speed;  //スピードアイテム用
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	float rotation;				  //回転用変数
	ITEMTYPE Type;				  //タイプを入れる箱
	void TypeItem(ITEMTYPE type); //アイテムのタイプを変えるよう	

};

#endif // !ITEM_H_