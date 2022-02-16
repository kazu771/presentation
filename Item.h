//==============================================================================================
//�A�C�e����{����.h[Item.h]
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
	ITEMTYPE GetItemMode() { return Type; } //�A�C�e���̃Q�b�^�[
private:
	Model*				m_Heart;  //�̗̓A�C�e���p
	Model*				m_Speed;  //�X�s�[�h�A�C�e���p
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	float rotation;				  //��]�p�ϐ�
	ITEMTYPE Type;				  //�^�C�v�����锠
	void TypeItem(ITEMTYPE type); //�A�C�e���̃^�C�v��ς���悤	

};

#endif // !ITEM_H_