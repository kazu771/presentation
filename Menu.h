//======================================================================================
//menu��{����.h[Menu.h]
//date:2021/07/12  name:Kazuki Wada
//======================================================================================
#ifndef MENU_H_
#define MENU_H_

#include "Scene.h"

//
//�N���X��`
//
class Menu : public Scene
{
private:
	float x; //�|�C���^�[���W
	float fadein;
	bool isUse;
	bool isVisible;
public:

	void Init();   //������
	void UnInit(); //�I��
	void Update(); //�X�V
	void Draw();   //�`��	

};

#endif // !MENU_H_

