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
#include "KeyEffect.h"
#include "PoisonEffect.h"
#include "ChargeBullet.h"
#include "input.h"

Model* ChargeBullet::m_Model;//スタティック変数だからcpp側でも宣言が必要

void ChargeBullet::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\Arrows.obj");
}

void ChargeBullet::UnLoad()
{
	m_Model->Unload();
	delete m_Model;
}

void ChargeBullet::Init()
{

	m_Position = D3DXVECTOR3(3.0f, 1.0f, 2.0f);
	m_Rotation = D3DXVECTOR3(90.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	m_Attack = 0;
	m_Cnt = 0.0f;
	m_Speed = 0.0f;
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	//プレイヤーの情報を受け取る
	Player* player = Manager::GetScene()->GetGameObject<Player>(1);
	m_Direction = player->GetForward();
}

//終了
void ChargeBullet::UnInit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//更新
void ChargeBullet::Update()
{
	//敵との当たり判定
	{
		Scene* scene = Manager::GetScene();
		//通常の敵との当たり判定
		{
			std::vector<Enemy*> enemyList = scene->GetGameObjects<Enemy>(1); //敵が複数いるためgameobjects
			for (Enemy* enemy : enemyList)
			{
				D3DXVECTOR3 enemyPosition = enemy->GetPosition();   //敵の座標を受け取る
				D3DXVECTOR3 direction = m_Position - enemyPosition;

				D3DXVECTOR3 obbx, obbz;
				float obblenX, obblenZ;

				obbx = enemy->GetObbX();
				obblenX = D3DXVec3Length(&obbx);//ベクトルの長さを求めている
				obbx /= obblenX;//分離軸方向の長さを１にしている

				obbz = enemy->GetObbZ();
				obblenZ = D3DXVec3Length(&obbz);
				obbz /= obblenZ;

				float lenX, lenZ;
				lenX = D3DXVec3Dot(&obbx, &direction);//内積
				lenZ = D3DXVec3Dot(&obbz, &direction);

				//fabsで絶対値を求めている
				if (fabs(lenX) < obblenX && fabs(lenZ) < obblenZ)
				{
					//爆発エフェクトの生成
					scene->AddGameObject<PoisonEffect>(1)->SetPosition(m_Position);
					//enemy->SetDestroy(); //敵の破壊
					SetDestroy();        //弾の破壊

					return;
				}

			}

		}
		
		m_Position.x -= m_Direction.x * 0.5;
		m_Position.y -= m_Direction.y * 0.5;
		m_Position.z -= m_Direction.z * 0.5;
		//フィールド外に出たら消す予約
		if (m_Position.z > 100.0f || m_Position.z < -80.0f || m_Position.x > 70.0f || m_Position.x < -70.0f)
		{
			//爆発エフェクトの生成
			scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);
			SetDestroy();
			return;
		}
	}
	//チャージ
	if (Input::GetKeyPress('T'))
	{
		m_Cnt += 0.1f;
	}
	//チャージの量によって攻撃力の変化
	if (m_Cnt > 0.4f)
	{
		m_Attack += 2;
		
	}
	//最大1.0f
	else if (m_Cnt > 1.0f)
	{
		m_Attack += 5;
	}
}
//描画
void ChargeBullet::Draw()
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