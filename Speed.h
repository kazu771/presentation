//================================================================================================
//�X�s�[�h�A�C�e����{����.h[Speed.h]
//date:2021/07/08  name:Kazuki Wada
//================================================================================================
#ifndef SPEED_H_
#define SPEED_H_


#include "GameObject.h"


class Speed : public GameObject
{

public:
	
	void Init();
	void UnInit();
	void Update();
	void Draw();
	void Speedefect();
private:
	
	Model*				m_Speed;  //�X�s�[�h�A�C�e���p
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	float				m_Rotations;  //��]�p�ϐ�
};

#endif // !SPEED_H_

