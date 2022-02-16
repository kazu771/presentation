//==================================================================================================
//�G�̎�����{����.h[ENEMYSITE.h]
//date:2021/10/01   name:Kazuki Wada
//==================================================================================================
#ifndef ENEMYSITE_H_
#define ENEMYSITE_H_


#include "GameObject.h"


//------------------------
//�N���X��`
//------------------------

class Enemysite : public GameObject
{
private:
	static	class Model* m_Model;  //���f����ǂݍ��ނ��ߗp
	class BoxCollision* m_Collision; //�R���W�����p
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	D3DXVECTOR3 m_Enemypos; //�G�̈ʒu���W������悤
	D3DXVECTOR3 m_Enemyrot; //�G�̂̊p�x
	D3DXVECTOR3 m_Playerpos;//�v���C���[�̍��W���Ƃ�悤
	float  angle;     //�p�x
	float Speed;      //����
	D3DXVECTOR3 cross;
	//MODE mode; //�G�̃��f����ς���悤
	int HPs;
	bool m_isAttack;
	void Collision(); //�v���C���[�Ƃ̓����蔻��p

public:
	static void Load();
	static void UnLoad();
	void Init();
	void UnInit();
	void Update();
	void Draw();
};

#endif // !ENEMYSITE_H_
