//==========================================================
//�J������{����.h[Camera.h]
//date;2021/05/10   name;Kazuki Wada
//==========================================================
#ifndef CAMERA_H_
#define CAMERA_H_

#include "GameObject.h"

class Camera :public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }
	bool CheckView(D3DXVECTOR3 Position); //����:�����錩���Ȃ��̔�������������̍��W������

private:

	D3DXVECTOR3 m_Target;   //�����_�̍��W
	D3DXMATRIX  m_ViewMatrix;
	D3DXMATRIX  m_ProjectionMatrix;
	bool        m_IsDebug;
};

#endif // !CAMERA_H_