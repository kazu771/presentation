//=========================================================================================================
//二方向の弾基本処理(右).h[TwoWayBulletRight.h]
//date:2021/11/30     name:Kazuki Wada
//=========================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "GameObject.h"
#include "model.h"
#include "TwoWayBulletRight.h"
#include "player.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Spider.h"

//----------------
//変数定義
//----------------
Model* TwowayRIght::m_Model;//スタティック変数だからcpp側でも宣言が必要



void TwowayRIght::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\Arrows.obj");
}

void TwowayRIght::UnLoad()
{
	m_Model->Unload();
	delete m_Model;
}

void TwowayRIght::Init()
{
	m_Position = D3DXVECTOR3(3.0f, 1.0f, 2.0f);
	m_Rotation = D3DXVECTOR3(90.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	//プレイヤーの情報を受け取る
	Player* player = Manager::GetScene()->GetGameObject<Player>(1);
	m_Direction = player->GetForward();

}

void TwowayRIght::UnInit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void TwowayRIght::Update()
{
	m_Position.x -= (m_Direction.x - 1.0f) * 0.5f;
	m_Position.y  = m_Direction.y * 0.5f;
	m_Position.z -= m_Direction.z * 0.5f;
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
					//scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);
					scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);
					//enemy->SetDestroy(); //敵の破壊
					SetDestroy();        //弾の破壊

					return;
				}

			}

		}
		//位置座標にプレイヤーの向きを入れる、最後の掛け算でスピードを調整
		m_Position -= m_Direction * 0.5;
		//フィールド外に出たら消す予約
		if (m_Position.z > 100.0f || m_Position.z < -80.0f || m_Position.x > 70.0f || m_Position.x < -70.0f)
		{
			//爆発エフェクトの生成
			scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);
			//	m_Spider.DecreaseHp();
			SetDestroy();

			return;
		}
	}

}

void TwowayRIght::Draw()
{//入力レイアウト
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
