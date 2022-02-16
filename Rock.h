//==================================================================================================
//��I�u�W�F�N�g��{����.h[Rock.h]
//date:2021/12/11    namek:Kazuki Wada
//==================================================================================================
#ifndef ROCK_H_
#define ROCK_H_
#include "GameObject.h"

class Rock : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:
	class Model*        m_Rock;  //�X�s�[�h�A�C�e���p
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader  = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
};


#endif // !ROCK_H_


