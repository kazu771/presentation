//================================================================================================================
//�Q�[���I�[�o�[��{����.h[GameOver.h]
//date:2022/02/01         name:Kazuki Wada
//================================================================================================================

#ifndef GAMEOVER_H_
#define GAMEOVER_H_

#include "Scene.h"

class  GameOver : public Scene
{
private:
	bool  m_isChange;//�`�F���W�t���O
	bool  m_isUse;	 //
	float m_alfa;    //�A���t�@�l
	float m_Var;  //���ϊ��l�p
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
};

#endif // !GAMEOVER_H_
