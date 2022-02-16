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
#include "Spider.h"
#include "player.h"
#include "EnemyBullet.h"
#include "BoxCollision.h"
#include "input.h"
#include "MeshField.h"
#include "animationModel.h"
#include "Camera.h"
#include "Bullet.h"
#include "Explosion.h"
#include "TwoWayBullet.h"
#include "TwoWayBulletRight.h"
#include "PoisonBullet.h"
#include "ChargeBullet.h"
#include "StateBullet.h"
//初期化
void Spider::Init()
{
	m_Cnt = 10;
	m_AttckCnt = 0;
	m_Model = new AnimetionModel();
	
	m_Model->Load("asset\\model\\SpiderWalks.fbx"); //ボーンなどを読み込むために書いている
	m_Model->LoadAnimation("asset\\model\\SpiderWalks.fbx", "Walk");
	m_Model->LoadAnimation("asset\\model\\SpiderAttacks.fbx", "Attacks");
	m_State = ENEMYSTATE::STATE_WALK;
	m_Position = D3DXVECTOR3(0.0f, 0.5f, 5.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
	m_Site = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TargetPos = { 0.0f, 0.0f, 0.0f };

	m_Direction = { 0.0f, 0.0f, 0.0f };
	m_Angle = 0.0f;
	m_Speed = SPEED_MAX + 0.5f;
	m_IsAngle = false;
	m_IsAttack = false;
	HPs = 10.0f;
	m_EsCnt = 0;
	Scene* scene = Manager::GetScene();


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}

//終了
void Spider::UnInit()
{
	m_Model->Unload();
	delete m_Model;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//更新
void Spider::Update()
{

	m_frame++;

	Player* p_player = Manager::GetScene()->GetGameObject<Player>(1);
	m_TargetPos = p_player->GetPosition();//プレイヤーの座標の取得
	m_Site = p_player->GetForward();
	


	//敵とプレイヤーの距離の差分を算出
	m_Direction.x = m_TargetPos.x - m_Position.x;
	m_Direction.z = m_TargetPos.z - m_Position.z;
	
	//正規化
	D3DXVec3Normalize(&m_Direction, &m_Direction);
	//プレイヤーと敵の座標の差分を算出
	m_Angle = atan2(fabsf(m_Position.z - m_TargetPos.z), fabsf(m_Position.x - m_TargetPos.x));
	
	Scene* scene = Manager::GetScene();  //弾用

	double probabilyty = 0.01; //0.1%の確立で撃ってくる,0.1%に変更

	if (m_State == ENEMYSTATE::STATE_ATTACK)
	{
		if ((double)rand() / RAND_MAX < probabilyty)
		{
			//攻撃処理
			if (!m_IsAttack)
			{
				scene->AddGameObject<StateBullet>(1)->SetPosition(D3DXVECTOR3(m_Position.x + 1.0f, m_Position.y, m_Position.z));
				m_IsAttack = true;
			}
		}
	}

	if (m_IsAttack)
	{
		m_AttckCnt += 1;
	}
	else if (!m_IsAttack)
	{
		m_AttckCnt = 0;
	}
	if (m_AttckCnt > 1)
	{
		m_IsAttack = false;
	}
	State();
	//メッシュフィールド高さの取得
	MeshField* meshField = Manager::GetScene()->GetGameObject<MeshField>(1);
	m_Position.y = meshField->GetHeight(m_Position);

	CollisionCharge();
	CollisionBullet();
	//弾との当たり判定
	{
		
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
					HPs -= 1.0f;

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
					HPs -= 1.0f;

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
}

//描画
void Spider::Draw()
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


	//-atan2f(g_enemy[i].direction.z, g_enemy[i].direction.x) - D3DXToRadian(90)
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

//敵の行動パターン
void Spider::State()
{
	switch (m_State)
	{
	case ENEMYSTATE::STATE_WALK:
		Walk();
		break;
	case ENEMYSTATE::STATE_ATTACK:
		Attack();
		break;
	}
}

//攻撃関数
void Spider::Attack()
{
	//攻撃モデルの再生
	m_Model->Update("Attacks", m_frame);
	m_Cnt+=1;
	if (m_Cnt >= 150)
	{
		m_State = ENEMYSTATE::STATE_WALK;
	}
}

void Spider::CollisionCharge()
{
	Scene* scene = Manager::GetScene(); 
	std::vector<ChargeBullet*> ChargeList = scene->GetGameObjects<ChargeBullet>(1); //敵が複数いるためgameobjects
	for (ChargeBullet* Chargebullet : ChargeList)
	{
		D3DXVECTOR3 BulletPosition = Chargebullet->GetPosition();   //敵の座標を受け取る
		D3DXVECTOR3 direction = m_Position - BulletPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 1.5f)
		{
			//爆発エフェクトの生成
			scene->AddGameObject<Explosion>(1)->SetPosition(BulletPosition);
			Chargebullet->SetDestroy();
			HPs -= 1.0f;

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

void Spider::CollisionBullet()
{
	Scene* scenes = Manager::GetScene();
	//通常の弾との当たり判定
	std::vector<Bullet*> BulletList = scenes->GetGameObjects<Bullet>(1); //敵が複数いるためgameobjects
	for (Bullet* bullet : BulletList)
	{
		D3DXVECTOR3 BulletPosition = bullet->GetPosition();   //敵の座標を受け取る
		D3DXVECTOR3 direction = m_Position - BulletPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 1.5f)
		{
			//爆発エフェクトの生成
			scenes->AddGameObject<Explosion>(1)->SetPosition(BulletPosition);
			bullet->SetDestroy();
			HPs -= 0.5f;
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
}

void Spider::CollisionTwoWay()
{
}

//歩いているときの関数
void Spider::Walk()
{
	m_Cnt = 0;
	if (!m_IsEscape)
	{
		//座標の更新
		m_Position.x += m_Direction.x * (m_Speed * cosf(m_Angle) * 0.01f + 0.02f);
		m_Position.z += m_Direction.z * (m_Speed * sinf(m_Angle) * 0.01f + 0.02f);

		m_Rotation.y = -atan2f(m_Direction.z, m_Direction.x) - D3DXToRadian(90);
		if (m_Speed >= 0.2f)
		{
			m_Speed = 0.5f;
		}
	}

	else if (m_IsEscape)
	{
		m_Speed = 0.5f;	
		m_Rotation.y = -atan2f(m_Direction.z, m_Direction.x) + D3DXToRadian(90);
		//座標の更新
		m_Position.x -= m_Direction.x * (m_Speed * cosf(m_Angle) * 0.03f);
		m_Position.z -= m_Direction.z * (m_Speed * sinf(m_Angle) * 0.03f);
	}
	m_Model->Update("Walk", m_frame);
	Scene* scene = Manager::GetScene();
	std::vector<BoxCollision*> BoxList = scene->GetGameObjects<BoxCollision>(1);
	for (BoxCollision* BoxColli : BoxList)
	{
		D3DXVECTOR3 BoxCollisionPosition = BoxColli->GetPosition();   //敵の座標を受け取る
		D3DXVECTOR3 direction = m_Position - BoxCollisionPosition;
		float length = D3DXVec3Length(&direction);
			
		if (length < 1.5f)
		{
				m_State = ENEMYSTATE::STATE_ATTACK;
				return;
		}
	}
}

int Spider::SetHp()
{
	return HPs;
}