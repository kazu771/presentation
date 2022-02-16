//====================================================================================================================
//鍵の基本処理.cpp[Key.cpp]
//date:2021/11/16   name:Kauzki Wada
//====================================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "Key.h"
#include "player.h"
#include "MeshField.h"
#include "input.h"
#include "Door.h"
#include "KeyEffect.h"
void Key::Init()
{
	m_Key = new Model();
	m_Key->Load("asset\\model\\Key.obj");
	m_Rotations = 0.0f;
	m_Position = D3DXVECTOR3(5.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, m_Rotations, 0.0f);
	m_Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	m_isUse = false;
	
	m_Direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_playerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_angle = 0.0f;
	m_Speed = 5.0f;

	m_Cnt = 1;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}

void Key::UnInit()
{
	m_Key->Unload();
	delete m_Key;


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Key::Update()
{
	
		Collision();
		if (!m_isUse)
		{
			m_Rotations += 0.1f;

			m_Rotation = D3DXVECTOR3(0.0f, m_Rotations, 0.0f);
		}

		else if (m_isUse)
		{
			Player* p_player = Manager::GetScene()->GetGameObject<Player>(1);
			m_playerPos = p_player->GetPosition();//プレイヤーの座礁を取得
			float sgn = m_Cross.y < 0.0f ? -1.0f : 1.0f;

			//鍵とプレイヤーの距離の差分を算出
			m_Direction.x = m_playerPos.x - m_Position.x;
			m_Direction.z = m_playerPos.z - m_Position.z;

			//正規化
			D3DXVec3Normalize(&m_Direction, &m_Direction);

			m_angle = atan2(fabsf(m_playerPos.z - m_Position.z), fabsf(m_playerPos.x - m_Position.x));

			//角度の更新
			m_Rotation.y = -atan2f(m_Direction.z, m_Direction.x) - D3DXToRadian(90);

			//座標の更新
			m_Position.x += m_Direction.x * (m_Speed * cosf(m_angle) * 0.01f);
			m_Position.z += m_Direction.z * (m_Speed * sinf(m_angle) * 0.01f);

			//メッシュフィールド高さの取得
			MeshField* meshField = Manager::GetScene()->GetGameObject<MeshField>(1);
			m_Position.y = meshField->GetHeight(m_Position);
			
			if (Input::GetKeyPress('E'))
			{
				SetDestroy();
			}	
		}
	
}

void Key::Draw()
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
		m_Key->Draw();
	
}

//プレイヤーとの当たり判定
void Key::Collision()
{
	Scene* scene = Manager::GetScene();
	
	std::vector<Player*> PlayerList = scene->GetGameObjects<Player>(1); //敵が複数いるためgameobjects
	for (Player* player : PlayerList)
	{
		D3DXVECTOR3 PlayerPosition = player->GetPosition();   //敵の座標を受け取る
		D3DXVECTOR3 direction = m_Position - PlayerPosition;
		float length = D3DXVec3Length(&direction);
		
		if (length < 1.5f)
		{
			if (m_Cnt == 1)
			{
				m_Cnt -= 1;
			}
			m_isUse = true;
			return;
		}
	}
	
}
//鍵の取得をしたかどうかを送るよう
bool Key::isActive()
{
	return m_isUse;
}




