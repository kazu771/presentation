//
//�Q�[���V�[����{����.h
//date:2021/07/05
//

#ifndef GAME_H_
#define GAME_H_

#include "Scene.h"

//-------------
//�N���X��`
//-------------

class Game:public Scene
{
private:
	int m_Hp;
	class Player* m_player;
	bool isChange;
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
};


#endif // !GAME_H_

