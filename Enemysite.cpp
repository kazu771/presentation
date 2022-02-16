//==================================================================================================
//敵の視線基本処理.cpp[ENEMYSITE.cpp]
//date:2021/10/01   name:Kazuki Wada
//==================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "Enemysite.h"
#include "Enemy.h"
#include "player.h"
//
//グローバル変数
//
Model* Enemysite::m_Model;//スタティック変数だからcpp側でも宣言が必要

void Enemysite::Init()
{
		m_Model = new Model();
		m_Model->Load("asset\\model\\enemysite.obj");

		m_Position = D3DXVECTOR3(3.0f, 1.0f, 2.0f);
		m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		m_Enemypos = { 0.0f, 0.0f, 0.0f };
		m_Enemyrot = { 0.0f, 0.0f, 0.0f };
		m_Playerpos = { 0.0f, 0.0f, 0.0f };
		m_isAttack = false;
	/*Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "LineofsightVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "LineofsightPS.cso");
*/
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	
}

void Enemysite::UnInit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Enemysite::Update()
{
	Enemy* p_Enemy = Manager::GetScene()->GetGameObject<Enemy>(1);
	Player* p_Player = Manager::GetScene()->GetGameObject<Player>(1);
	m_Enemypos = p_Enemy->GetPosition();
	m_Enemyrot = p_Enemy->GetRotation();
	m_Playerpos = p_Player->GetPosition();
	m_Position.x = m_Enemypos.x;
	m_Position.y = 1.0f;

	if (m_Enemypos.z > m_Playerpos.z)
	{
		m_Position.z = m_Enemypos.z - 1.0f;
	}

	else if (m_Enemypos.z < m_Playerpos.z)
	{
		m_Position.z = m_Enemypos.z + 1.0f;
	}
	m_Rotation = m_Enemyrot;
}

void Enemysite::Draw()
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

//プレイヤーとの当たり判定
void Enemysite::Collision()
{
	//敵との当たり判定(
	Scene* scene = Manager::GetScene();
	std::vector<Player*> PlayerList = scene->GetGameObjects<Player>(1); //敵が複数いるためgameobjects
	for (Player* player : PlayerList)
	{
		D3DXVECTOR3 enemyPosition = player->GetPosition();   //敵の座標を受け取る
		D3DXVECTOR3 direction = m_Position - enemyPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 1.5f)
		{

			return;
		}
	}
}



