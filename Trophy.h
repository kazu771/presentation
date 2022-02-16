//================================================================================================================
//トロフィー基本処理.h[Trophy.h]
//date:2022/01/24       name:Kazuki Wada
//================================================================================================================

#include "GameObject.h"

#ifndef TROPHY_H_
#define TROPYH_H_

class Trophy : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	bool SetActive();//鍵を使ったかどうか

private:

	class Model*        m_Trophy;  
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
	
};

#endif // !DOOR_H_

#pragma once
