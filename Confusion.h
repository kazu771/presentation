//=========================================================================================================
//������{����.h[Confusion.h]
//date:2021/11/30   name:Kauzki Wada
//=========================================================================================================

#ifndef CONFUSION_H_
#define CONFUSION_H_

class Confusion
{
public:
	void Change();
	bool State();//���݂̏�Ԃ𑗂�֐�
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:
	bool          m_isConfusion;//�����p�ϐ�
	class Player* m_player;//�v���C���[�̑�Ck���󂯎��悤
	float		  m_Alfa;
};


#endif // !CONFUSION_H_

