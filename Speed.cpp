//================================================================================================
//スピードアイテム基本処理.cpp[Speed.cpp]
//date:2021/07/08  name:Kazuki Wada
//================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "Speed.h"

//初期化
void Speed::Init()
{
	m_Speed = new Model();
	m_Speed->Load("asset\\model\\heart.obj");
	m_Rotations = 0.0f;
	m_Position = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, m_Rotations, 0.0f);
	m_Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	



	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}

//終了
void Speed::UnInit()
{
	m_Speed->Unload();
	delete m_Speed;


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//更新
void Speed::Update()
{
	m_Rotations += 0.1f;

	m_Rotation = D3DXVECTOR3(0.0f, m_Rotations, 0.0f);



}

//描画
void Speed::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクスの設定
	D3DXMATRIX wold, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//前からy, x, zの順で設定していく
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	wold = scale * rot * trans;

	Renderer::SetWorldMatrix(&wold);

	//描画するだけ
	m_Speed->Draw();
}


void Speed::Speedefect()
{
	move += 0.5f;
}
