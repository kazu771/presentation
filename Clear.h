//================================================================================================================
//�Q�[���N���A��{����.h[Clear.h]
//date:2022/01/25         name:Kazuki Wada
//================================================================================================================
#ifndef CLEAR_H_
#define CLEAR_H_

#include "Scene.h"

//-------------
//�N���X��`
//-------------

class Clear :public Scene
{
private:
	bool  m_isChange;//�`�F���W�t���O
	bool  m_isUse;	 //
	float m_alfa;    //�A���t�@�l
	float m_Var;
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
};

#endif // !CLEAR_H_
