//=======================================================================================
//Explaine��{����.h[Explain.h]
//date:2021/08/28   name:Kazuki Wada
//=======================================================================================
#ifndef EXPLAINE_H_
#define EXPLAINE_H_

#include "Scene.h"
class Explaine : public Scene
{
private:
	float fadein;
	bool isUse;
	bool isVisible;
	float a;
	float alfa;
public:
	void Init();   //������
	void UnInit(); //�I��
	void Update(); //�X�V
	void Draw();   //�`��
};
#endif // !EXPLAINE_H_
