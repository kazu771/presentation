//=============================================
//敵基本処理.cpp[Enemy.Cpp]
//date:2021/05/24   name;Kazuki Wada
//=============================================
#include <time.h>   // time()関数用
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "Enemy.h"
#include "player.h"
#include "EnemyBullet.h"
#include "BoxCollision.h"
#include "input.h"
#include "MeshField.h"
#include "animationModel.h"
#include "Camera.h"
#include "ConfusionBullet.h"
#include "Bullet.h"
#include "TwoWayBullet.h"
#include "TwoWayBulletRight.h"
#include "Explosion.h"

//初期化
void Enemy::Init()
{
	m_Cnt = 10;
	m_Models = new AnimetionModel();

	m_Models->Load("asset\\model\\EnemyWalks.fbx"); //ボーンなどを読み込むために書いている
	m_Models->LoadAnimation("asset\\model\\EnemyWalking.fbx", "WalkS");
	m_Models->LoadAnimation("asset\\model\\EnemyAttacks.fbx", "AttackS");

	m_State = STATACE::STATACE_ATTACK;
	m_Position = D3DXVECTOR3(0.0f, 0.5f, 5.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
	
	m_TargetPos = { 0.0f, 0.0f, 0.0f };

	m_Direction = { 0.0f, 0.0f, 0.0f };
	m_Angle = 0.0f;
	m_Speed = SPEED_MAX;
	m_IsAngle = false;
	m_IsEscape = false;
	HPs = 50;
	m_Hpss = 15.0f;
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}
//終了
void Enemy::UnInit()
{
	m_Models->Unload();
	delete m_Models;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//更新
void Enemy::Update()
{
	
	m_frame++;
	
	Player* p_player = Manager::GetScene()->GetGameObject<Player>(1);
	m_TargetPos = p_player->GetPosition();

	float sgn = m_Cross.y < 0.0f ? -1.0f : 1.0f;

	//敵とプレイヤーの距離の差分を算出
	m_Direction.x = m_TargetPos.x - m_Position.x;
	m_Direction.z = m_TargetPos.z - m_Position.z;
	

	//正規化
	D3DXVec3Normalize(&m_Direction, &m_Direction);
	
	m_Angle = atan2(fabsf(m_TargetPos.z - m_Position.z), fabsf(m_TargetPos.x - m_Position.x));
	
	Scene* scene = Manager::GetScene();  //弾用

	double probabilyty = 0.01; //0.1%の確立で撃ってくる
	if (m_State == STATACE::STATACE_ATTACK)
	{

		if ((double)rand() / RAND_MAX < probabilyty)
		{
			scene->AddGameObject<ConfusionBullet>(1)->SetPosition(D3DXVECTOR3(m_Position.x, m_Position.y + 0.5f, m_Position.z));

		}
	}
	State();
	//メッシュフィールド高さの取得
	MeshField* meshField = Manager::GetScene()->GetGameObject<MeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);


	//弾との当たり判定
	{
		//通常の弾との当たり判定
		{
			std::vector<Bullet*> BulletList = scene->GetGameObjects<Bullet>(1); //敵が複数いるためgameobjects
			for (Bullet* bullet : BulletList)
			{
				D3DXVECTOR3 BulletPosition = bullet->GetPosition();   //敵の座標を受け取る
				D3DXVECTOR3 direction = m_Position - BulletPosition;
				float length = D3DXVec3Length(&direction);

				if (length < 1.5f)
				{
					//爆発エフェクトの生成
					scene->AddGameObject<Explosion>(1)->SetPosition(BulletPosition);
					bullet->SetDestroy();
					m_Hpss -= 1.0f;

					if (m_Hpss <= 5.0f)
					{
						m_IsEscape = true;
					}

					if (m_Hpss <= 0.0f)
					{
						SetDestroy();
					}
					return;
				}
			}
		}

		//twowayの弾との当たり判定
		{
			std::vector<TwoWay*> TwoBulletList = scene->GetGameObjects<TwoWay>(1); //敵が複数いるためgameobjects
			for (TwoWay* bullet : TwoBulletList)
			{
				D3DXVECTOR3 BulletPosition = bullet->GetPosition();   //敵の座標を受け取る
				D3DXVECTOR3 direction = m_Position - BulletPosition;
				float length = D3DXVec3Length(&direction);

				if (length < 1.5f)
				{
					//爆発エフェクトの生成
					scene->AddGameObject<Explosion>(1)->SetPosition(BulletPosition);
					bullet->SetDestroy();
					m_Hpss -= 1.0f;

					if (HPs <= 3.0f)
					{
						m_IsEscape = true;
					}

					if (HPs <= 0.0f)
					{
						SetDestroy();
					}
					return;
				}
			}
		
			std::vector<TwowayRIght*> TwowayRightBulletList = scene->GetGameObjects<TwowayRIght>(1); //敵が複数いるためgameobjects
			for (TwowayRIght* Rightbullet : TwowayRightBulletList)
			{
				D3DXVECTOR3 BulletPosition = Rightbullet->GetPosition();   //敵の座標を受け取る
				D3DXVECTOR3 direction = m_Position - BulletPosition;
				float length = D3DXVec3Length(&direction);

				if (length < 1.5f)
				{
					//爆発エフェクトの生成
					scene->AddGameObject<Explosion>(1)->SetPosition(BulletPosition);
					Rightbullet->SetDestroy();
					m_Hpss -= 1.0f;

					if (HPs <= 5.0f)
					{
						m_IsEscape = true;
					}

					if (HPs <= 0.0f)
					{
						SetDestroy();
					}
					return;
				}
			}
		}
	}

	if (m_IsEscape)
	{
		m_State = STATACE::STATACE_WALK;
	}
}

//描画
void Enemy::Draw()
{
	//しすいだいカリング
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(0);
	//見えてなければ描画しない
	if (!camera->CheckView(m_Position))
	{
		return;
	}

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
	m_Models->Draw();
}

//敵の行動パターン
void Enemy::State()
{
	switch (m_State)
	{
	case STATACE::STATACE_WALK:
		Walk();
		break;
	case STATACE::STATACE_ATTACK:
		Attack();
		break;
	}
}

//攻撃関数
void Enemy::Attack()
{
	//攻撃のモデル再生
	m_Models->Update("AttackS", m_frame);
}

//歩いているときの関数
void Enemy::Walk()
{
	m_Cnt = 0;
	m_Rotation.y = -atan2f(m_Direction.z, m_Direction.x) + D3DXToRadian(90);
	//座標の更新
	m_Position.x -= m_Direction.x * (m_Speed * cosf(m_Angle) * 0.03f);
	m_Position.z -= m_Direction.z * (m_Speed * sinf(m_Angle) * 0.03f);
	m_Models->Update("WalkS", m_frame);
	Scene* scene = Manager::GetScene();
	std::vector<BoxCollision*> BoxList = scene->GetGameObjects<BoxCollision>(1);
	for (BoxCollision* BoxColli : BoxList)
	{
		D3DXVECTOR3 BoxCollisionPosition = BoxColli->GetPosition();   //敵の座標を受け取る
		D3DXVECTOR3 direction = m_Position - BoxCollisionPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 1.5f)
		{
			m_State = STATACE::STATACE_ATTACK;
			return;
		}
	}

}