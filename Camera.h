//==========================================================
//カメラ基本処理.h[Camera.h]
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
	bool CheckView(D3DXVECTOR3 Position); //引数:見える見えないの判定をしたい物の座標を入れる

private:

	D3DXVECTOR3 m_Target;   //注視点の座標
	D3DXMATRIX  m_ViewMatrix;
	D3DXMATRIX  m_ProjectionMatrix;
	bool        m_IsDebug;
};

#endif // !CAMERA_H_