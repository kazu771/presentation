//=================================================================================================
//���U���g��{����.h[Result.h]
//date:2021/07/08   name:Kazuki Wada
//=================================================================================================
#ifndef RESULT_H_
#define RESULT_H_

#include "Scene.h"

class Result : public Scene
{

public:
	void Init();   //������
	void UnInit(); //�I��
	void Update(); //�X�V
	void Draw();
	int Count;

private:
	float alfa;
	float a;
	float fadein;
	bool isUse;
	bool isFade;

};

#endif // !RESULT_H_

