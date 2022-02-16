//==========================================================
//カメラ基本処理.cpp[Camera.cpp]
//date;2021/05/10   name;Kazuki Wada
//==========================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "Camera.h"
#include "input.h"
#include "player.h"

void Camera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 5.0f, -7.0f); //カメラの位置
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    //注視点の位置
	m_IsDebug = false;
}

void Camera::UnInit()
{

}

void Camera::Update()
{
	//デバックモードの操作
	{
		if (m_IsDebug == false)
		{
			//デバックモードに変更
			if (Input::GetKeyTrigger('I'))
			{
				m_IsDebug = true;
			}
		}
		else
		{
			//デバックモード解除
			if (Input::GetKeyTrigger('I'))
			{
				m_IsDebug = false;
			}
		}

		if (m_IsDebug)
		{
			if (Input::GetKeyTrigger('L'))
			{
				m_Position.x += 1.0f;
			}

			else if (Input::GetKeyTrigger('J'))
			{
				m_Position.x -= 1.0f;
			}
			else if (Input::GetKeyTrigger('I'))
			{
				m_Position.z -= 1.0f;
			}
			else if (Input::GetKeyTrigger('K'))
			{
				m_Position.z -= 1.0f;
			}

		}
	}

	//トップビュー
	Player* player = Manager::GetScene()->GetGameObject<Player>(1);
	
	D3DXVECTOR3 forward = player->GetForward();
	m_Target = player->GetPosition();
	//forward.x += 1.0f;
	//サードパーソン
	if (m_IsDebug == true)
	{
		//後ろの方向のベクトルが欲しいから-をつけてあげる、さらに後ろにするために*5.0
		m_Position = m_Target - (-forward) * 5.0f + D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	}
	
	else if (m_IsDebug == false)
	{
		//注視点に自分で設定したいカメラの位置を足してあげる
		m_Position = m_Target + D3DXVECTOR3(0.0f, 5.0f, -8.0f);
	}
}

void Camera::Draw()
{
	//ビューマトリクスの設定,カメラの位置など
	
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	Renderer::SetViewMatrix(&m_ViewMatrix);

	//プロジェクションマトリクス,投影設定,画角の設定、二アーなどのせっていも行う
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);
}

bool Camera::CheckView(D3DXVECTOR3 Position)
{
	D3DXMATRIX vp, invvp;

	vp = m_ViewMatrix * m_ProjectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);//逆行列を求めている

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];
	//カメラから見たときの奥の４頂点
	{
		vpos[0] = D3DXVECTOR3( -1.0f,  1.0f, 1.0f);//左上, とりあえず課題用に0にしてる本当は-1.0
		vpos[1] = D3DXVECTOR3(  1.0f,  1.0f, 1.0f);//右上
		vpos[2] = D3DXVECTOR3( -1.0f, -1.0f, 1.0f);//左下
		vpos[3] = D3DXVECTOR3(  1.0f, -1.0f, 1.0f);//右下
	}

	//座標変換
	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);

	D3DXVECTOR3 v, v1, v2,v3, v4, n, o;

	v = Position - m_Position;//斜めの線を算出
	v1 = wpos[0] - m_Position;
	v2 = wpos[2] - m_Position;
	v3 = wpos[1] - m_Position;
	v4 = wpos[3] - m_Position;

	D3DXVec3Cross(&n, &v1, &v2);//左側の外積を求める,v1とv2に垂直な左側面の法線ベクトル
	D3DXVec3Cross(&o, &v3, &v4);//右側の外積
	
	//視すいだいの中にいるかどうかの判定,D3DXVec3Dotで内積を算出
	if (D3DXVec3Dot(&n, &v) < 0.0f)
	{
		//居なければfalseにする
		return false;
	}

	
	return true;
}

