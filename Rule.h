//======================================================================================
//���[����{����.h[Rule.h]
//date:2021/07/13  name:Kazuki Wada
//======================================================================================
#ifndef RULE_H_
#define RULE_H_

#include "Scene.h"
class Rule : public Scene
{
private:
	float fadein;
	bool isUse;
	bool isVisible;
	float alfa;
	float a;
public:
	void Init();   //������
	void UnInit(); //�I��
	void Update(); //�X�V
	void Draw();   //�`��
};

#endif // !RULE_H_
