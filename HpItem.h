//==============================================================================================================
//�̗̓A�C�e����{����.h[HpItem.h]
//date:2021/12/14    name:Kazuki Wada
//==============================================================================================================
#ifndef HPITEM_H_
#define HPITEM_H_

#include "GameObject.h"

class HpItem : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	bool GetHpItem() { return m_isHp; } //Hp�A�C�e���擾�ϐ��𑗂�֐�
private:
	class Model*		m_MHp;          //�X�s�[�h�A�C�e���p
	class Player*		m_Player;
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	float				m_rotations;    //��]�p�ϐ�
	float				m_Cnt;
	bool				m_isHp;         //�擾�������ǂ���
	void ChangeFlag();                  //�t���O��ύX����悤
};


#endif // !HPITEM_H_
