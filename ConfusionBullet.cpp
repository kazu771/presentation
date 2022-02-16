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
#include "Enemy.h"
#include "player.h"
#include "Explosion.h"
#include "Item.h"
#include "Spider.h"
#include "PoisonBullet.h"
#include "Poison.h"
#include "DamageUi.h"
#include "ConfusionBullet.h"
#include "ConfuseEffect.h"
Model* ConfusionBullet::m_Model;//スタティック変数だからcpp側でも宣言が必要

void ConfusionBullet::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\Confusions.obj");
}

void ConfusionBullet::UnLoad()
{
	m_Model->Unload();
	delete m_Model;
}

void ConfusionBullet::Init()
{

	m_Position = D3DXVECTOR3(3.0f, 1.0f, 2.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 1.6f, 0.0f);
	m_Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	m_isAttack = false;
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	Scene* scene = Manager::GetScene();
	//敵の情報を取得
	std::vector<Enemy*> EnemyList = scene->GetGameObjects<Enemy>(1);
	for (Enemy* enemys : EnemyList)
	{
		m_Direction = enemys->GetForward();
	}
}

//終了
void ConfusionBullet::UnInit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//更新
void ConfusionBullet::Update()
{
	//プレイヤーとの当たり判定(
	Scene* scene = Manager::GetScene();
	std::vector<Player*> PlayerList = scene->GetGameObjects<Player>(1); //敵が複数いるためgameobjects
	for (Player* player : PlayerList)
	{
		D3DXVECTOR3 PlayerPosition = player->GetPosition();   //プレイヤーの座標を受け取る
		D3DXVECTOR3 direction = m_Position - PlayerPosition;
		float length = D3DXVec3Length(&direction);
		if (length < 1.5f)
		{
			//爆発エフェクトの生成
			scene->AddGameObject<ConfuseEffect>(1)->SetPosition(D3DXVECTOR3(PlayerPosition.x, PlayerPosition.y + 0.5f, PlayerPosition.z));
			player->ChangeConfusion();
			SetDestroy();        //弾の破壊

			return;
		}
	}

	//最後の掛け算でスピードを調整
	m_Position -= m_Direction * 0.5;

	//フィールド外に出たら消す予約
	if (m_Position.z > 70.0f || m_Position.z < -70.0f || m_Position.x > 70.0f || m_Position.x < -70.0f)
	{
		//爆発エフェクトの生成
		scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);

		SetDestroy();
		return;
	}
}

//描画
void ConfusionBullet::Draw()
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