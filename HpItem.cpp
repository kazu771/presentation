//==============================================================================================================
//体力アイテム基本処理.cpp[HpItem.cpp]
//date:2021/12/14    name:Kazuki Wada
//==============================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "player.h"
#include "HpItem.h"

void HpItem::Init()
{
	m_MHp = new Model();
	m_MHp->Load("asset\\model\\heart.obj");
	m_rotations = 0.0f;
	m_Position = D3DXVECTOR3(100.0f, 1.0f, -1.0f);
	m_Rotation = D3DXVECTOR3(0.0f, m_rotations, 0.0f);
	m_Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	m_Cnt = 5.0f;
	Scene* scene = Manager::GetScene();
	m_Player = scene->AddGameObject<Player>(1);
	m_isHp = m_Player->GetHpItem();//アイテムをプレイヤーが取得したかどうか
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}

void HpItem::UnInit()
{
	m_MHp->Unload();
	delete m_MHp;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void HpItem::Update()
{
	m_isHp = m_Player->GetHpItem();//アイテムをプレイヤーが取得したかどうか
	if (!m_isHp)
	{
		m_rotations += 0.1f;
	}

	//プレイヤーが取得したら消す
	else if (m_isHp)
	{
		SetDestroy();
		//ChangeFlag();
	}
	m_Rotation = D3DXVECTOR3(0.0f, m_rotations, 0.0f);
}

void HpItem::Draw()
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
	m_MHp->Draw();
}

void HpItem::ChangeFlag()
{
	if (m_isHp && m_Cnt >= 0)
	{
		m_Cnt -= 1.0f;

		if (m_Cnt < 0)
		{
			m_isHp = false;
			m_Cnt = 5.0f;
		}
	}
}
