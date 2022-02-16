//==============================================================================================
//プレイヤーの弾基本処理.cpp[Bullet.cpp]
//date;2021/05/31     name:Kazuki Wada
//==============================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "GameObject.h"
#include "model.h"
#include "Bullet.h"
#include "Enemy.h"
#include "player.h"
#include "Explosion.h"
#include "Item.h"
#include "Spider.h"
#include "KeyEffect.h"
#include "PoisonEffect.h"

//----------------
//変数宣言
//----------------
Model* Bullet::m_Model;//スタティック変数だからcpp側でも宣言が必要
Spider  m_Spider;

void Bullet::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\Arrows.obj");
}

void Bullet::UnLoad()
{
	m_Model->Unload();
	delete m_Model;
}

void Bullet::Init()
{
	
	m_Position = D3DXVECTOR3(3.0f, 1.0f, 2.0f);
	m_Rotation = D3DXVECTOR3(90.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	//プレイヤーの情報を受け取る
	Player* player = Manager::GetScene()->GetGameObject<Player>(1);
	m_Direction = player->GetForward();
}

//終了
void Bullet::UnInit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//更新
void Bullet::Update()
{
	Scene* scene = Manager::GetScene();

	//位置座標にプレイヤーの向きを入れる、最後の掛け算でスピードを調整
	m_Position -= m_Direction * 0.5;
	//フィールド外に出たら消す予約
	if (m_Position.z > 100.0f || m_Position.z < -80.0f || m_Position.x > 70.0f || m_Position.x < -70.0f)
	{
		//爆発エフェクトの生成
		scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);
		SetDestroy();
		return;
	}
		
}

//描画
void Bullet::Draw()
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
	m_Model->Draw();
}