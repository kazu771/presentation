//==================================================================
//プレイヤー基本処理.cpp[player.cpp]
//date:2021/05/17      name:Kazuki Wada
//==================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "GameObject.h"
#include "input.h"
#include "audio.h"
#include "model.h"
#include "player.h"
#include "Bullet.h"
#include "Item.h"
#include "Reload.h"
#include "player.h"
#include "Enemy.h"
#include "Shadow.h"
#include "Speed.h"
#include "BoxCollision.h"
#include "EnemyBullet.h"
#include "animationModel.h"
#include "MeshField.h"
#include "Camera.h"
#include "Camera.h"
#include "keyboard.h"
#include "TwoWayBullet.h"
#include "TwoWayBulletRight.h"
#include "Poison.h"
#include "Confusion.h"
#include "ConfusionBullet.h"
#include "HpItem.h"
#include "Door.h"
#include "RightDoor.h"
#include "ChargeBullet.h"
#include "PoisonEffect.h"
#include "PoisonBullet.h"
#include "DoorCollision.h"
#include "Key.h"
#include "StateBullet.h"
#include "HpBar.h"

void Player::Init()
{
	//g_Poison.Init();
	m_Model = new AnimetionModel();
	
	m_Model->Load("asset\\model\\PlayersIdle.fbx");					   //ボーン情報を読み込み
	m_Model->LoadAnimation("asset\\model\\PlayersIdle.fbx", "Idle");   //止まってる状態
	m_Model->LoadAnimation("asset\\model\\PlayersRun.fbx", "Run");     //歩いている状態
	m_Model->LoadAnimation("asset\\model\\PlayersDance.fbx", "Dance"); //エモート

	m_Position = D3DXVECTOR3(-10.0f, 0.0f, -5.0f);
	m_Mode = ArrowMode::ARROWMODE_NORMAL;        //弾の種類(最初はノーマル)
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
	move = 0.0f;
	m_isEmote     = false; //エモートフラグ
	m_isPoison    = false; //毒用フラグ
	m_isConfusion = false; //混乱フラグ
	m_isHpItem    = false; //HPアイテムフラグ
	m_HP = 5;
	m_Hps = 10;       //プレイヤーの体力
	m_Cnt = 50;       //混乱用カウント
	m_PoisonCnt = 50; //毒用カウント
	m_HItemCnt = 10;  //アイテム用カウント
	m_EmCnt = 0;
	
	Scene* scene = Manager::GetScene();
	//影
	m_Shadow = scene->AddGameObject<Shadow>(2);
	m_Shadow->SetPosition(m_Position);

	m_Camera = scene->AddGameObject<Camera>(0);
	m_site.x = m_Camera->GetForward().x;
	m_site.y = m_Camera->GetForward().y;
	m_site.z = m_Camera->GetForward().z;

	m_Forward = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Key = scene->AddGameObject<Key>(1);
	m_isKey = false;
	//スピードアイテム用
	m_Speed = scene->AddGameObject<Speed>(1);

	//打つときのSE
	m_shotse = scene->AddGameObject<Audio>(2);
	m_shotse->Load("asset\\bgm\\SE\\Shots.wav");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
}

//終了
void Player::UnInit()
{
	m_Model->Unload();
	delete m_Model;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//更新
void Player::Update()
{	
	m_Frame++;
	m_isKey = m_Key->isActive();//カギを取得しているかどうか
	if (m_IsSp == true)
	{
		m_Speed->Speedefect();
	}
	else
	{
		move = 0.1f;
	}
	Behavior();
	PoisonDamge(1.0f);
	HpItemProcess();
	Confusion(50);
		//メッシュフィールド高さの取得
		MeshField* meshField = Manager::GetScene()->GetGameObject<MeshField>(1);

		m_Position.y = meshField->GetHeight(m_Position);

		GetItem();   //アイテムの取得

		m_Shadow->SetPosition(m_Position);
	
		////体力がなくなったらプレイヤーを破壊
		if (m_Hps < 0)
		{
			SetDestroy();
		}
	
		//毒フラグの切り替え
		if (m_isPoison)
		{
			m_PoisonCnt -= 1;

			if (m_PoisonCnt < 10)
			{
				m_isPoison = false;
		
				m_PoisonCnt = 50;
			}
		}

		//プレイヤーの行ける制限,一辺40の正方形 
		if (m_Position.z <= -40.0f || m_Position.z >= 40.0f || m_Position.x >= 40.0f || m_Position.x <= -40.0f)
		{
			m_Position += m_Forward * move;
		}
		CollisionStateBullet();
		CollisionConfuse();
		CollisionHpItem();
		CollisionDoor();
		
		ArrowModeChange();
}
//描画
void Player::Draw()
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
	m_Model->Draw();
	
}

//プレイヤーとアイテムの当たり判定
void Player::GetItem()
{
	//アイテムとの当たり判定
	Scene* scene = Manager::GetScene();
	std::vector<Speed*> ItemList = scene->GetGameObjects<Speed>(1);
	for (Speed* item : ItemList)
	{
		D3DXVECTOR3 ItemPosition = item->GetPosition();   //敵の座標を受け取る
		D3DXVECTOR3 direction = m_Position - ItemPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 2.0f)
		{
			item->SetDestroy();
			m_Hps += 1;
			return;
		}

	}

}
//プレイヤーの操作
void Player::Behavior()
{
	//プレイヤーの挙動
	{
		//混乱してないとき
		if (!m_isConfusion)
		{
			//左に移動
			if (Input::GetKeyPress('A'))
			{
				m_Rotation.y -= 0.1f;
				m_GTraget.y -= 0.1f;
				m_Model->Update("Run", m_Frame);
			}
			else
			{
				m_Model->Update("Idle", m_Frame);
			}
			//右に移動
			if (Input::GetKeyPress('D'))
			{
				m_Rotation.y += 0.1f;
				m_GTraget.y += 0.1f;
				m_Model->Update("Run", m_Frame);

			}

			m_Forward = GetForward();
			//前に移動
			if (Input::GetKeyPress('W'))
			{
				m_Position -= m_Forward * move;
				m_Model->Update("Run", m_Frame);
			}
			//後ろに移動
			if (Input::GetKeyPress('S'))
			{
				m_Position += m_Forward * move;
				m_Model->Update("Run", m_Frame);
			}

			if (Input::GetKeyPress('W') && Input::GetKeyPress(VK_SHIFT))
			{
				m_Position -= m_Forward * move;
				m_Model->Update("Run", m_Frame);
			}
			if (Input::GetKeyTrigger('R'))
			{
				m_isEmote = true;
			}
		}
		//混乱してる時の操作
		else if (m_isConfusion)
		{
			//左に移動
			if (Input::GetKeyPress('A'))
			{
				m_Rotation.y += 0.1f;
				m_GTraget.y -= 0.1f;
				m_Model->Update("Run", m_Frame);
			}
			else
			{
				m_Model->Update("Idle", m_Frame);
			}

			//右に移動
			if (Input::GetKeyPress('D'))
			{
				m_Rotation.y += 0.1f;
				m_GTraget.y += 0.1f;
				m_Model->Update("Run", m_Frame);

			}

		
			//前に移動
			if (Input::GetKeyPress('W'))
			{
				m_Position += m_Forward * move;
				m_Model->Update("Run", m_Frame);
			}
			//後ろに移動
			if (Input::GetKeyPress('S'))
			{
				m_Position -= m_Forward * move;
				m_Model->Update("Run", m_Frame);
			}

			if (Input::GetKeyTrigger('R'))
			{
				m_isEmote = true;
			}
		}
		//エモート
		if (m_isEmote)
		{
			m_Model->Update("Dance", m_Frame);
			m_EmCnt += 1;
			//エモートは約3秒くらい
			if (m_EmCnt > 150)
			{
				m_isEmote = false;
				m_EmCnt = 0;
			}
		}
		//弾を撃つ処理
		{
			if (Input::GetKeyTrigger(VK_SPACE))
			{
				Scene* scene = Manager::GetScene();  //弾用

			
				switch (m_Mode)
				{
				case ArrowMode::ARROWMODE_NORMAL:
					//バレットの座標をセットポジションを変えている
					scene->AddGameObject<Bullet>(1)->SetPosition(D3DXVECTOR3(m_Position.x, m_Position.y + 0.5f, m_Position.z));
					break;
				case ArrowMode::ARROWMODE_DOUBLE:
					//バレットの座標をセットポジションを変えている
					scene->AddGameObject<Bullet>(1)->SetPosition(D3DXVECTOR3(m_Position.x, m_Position.y + 0.5f, m_Position.z));
					//バレットの座標をセットポジションを変えている
					scene->AddGameObject<Bullet>(1)->SetPosition(D3DXVECTOR3(m_Position.x + 0.5f, m_Position.y + 0.5f, m_Position.z));
					break;
				case ArrowMode::ARROWMODE_TWOWAY:
					scene->AddGameObject<TwoWay>(1)->SetPosition(D3DXVECTOR3(m_Position.x + 0.5f, m_Position.y, m_Position.z));
					scene->AddGameObject<TwowayRIght>(1)->SetPosition(D3DXVECTOR3(m_Position.x - 1.5f, m_Position.y, m_Position.z));
					break;
				}
			
				m_shotse->Play();
			}
		}
		//チャージショット
		{
			Scene* l_Charge = Manager::GetScene();
			if (Input::GetKeyPress('T'))
			{
				m_isCharge = true;
			
			}
			else if (Input::GetKeyReleace('T'))
			{
				m_isCharge = false;
				l_Charge->AddGameObject<ChargeBullet>(1)->SetPosition(D3DXVECTOR3(m_Position.x + 0.5f, m_Position.y + 0.5f, m_Position.z));
			}
		}

		//カギを取得していてEキーを押したとき
		{
			if (m_isKey && !m_isCheck)
			{
				if (Input::GetKeyTrigger('E'))
				{
					m_isCheck = true;
				}
			}
		}
	}
}
//毒のくらってる時の処理
void Player::PoisonDamge(float Dameg)
{
	if (m_isPoison)
	{
	//	m_Hps -= Dameg;

		m_PoisonCnt -= 1;

		if (m_PoisonCnt < 0)
		{
			m_isPoison = false;
		/*	m_isPoisonUi = false;*/
			m_PoisonCnt = 50;
		}
	}
}
//混乱したときの処理
void Player::Confusion(int Cnt)
{
	if (m_isConfusion)
	{
		m_Cnt -= 1;

		if (m_Cnt < 0)
		{
			m_isConfusion = false;
			m_Cnt = Cnt;
		}
	}
}
//敵の弾と接触したとき
void Player::CollisionEnemyBullet()
{
	Scene* scenes = Manager::GetScene();
	std::vector<StateBullet*> Enemybulletlist = scenes->GetGameObjects<StateBullet>(1);
	for (StateBullet* ebullet : Enemybulletlist)
	{
		D3DXVECTOR3 EnemyPosition = ebullet->GetPosition();   //敵の座標を受け取る
		D3DXVECTOR3 direction = m_Position - EnemyPosition;
		float length = D3DXVec3Length(&direction);
		if (length < 2.0f)
		{
			m_Hps -= 1;
			m_isPoison = true;
			return;
		}
	}
}

//混乱する弾との当たり判定
void Player::CollisionConfuse()
{
	Scene* scene = Manager::GetScene();
	std::vector<ConfusionBullet*> ConfuseList = scene->GetGameObjects<ConfusionBullet>(1);

	for (ConfusionBullet* confuse : ConfuseList)
	{
		D3DXVECTOR3 ConfBulletPosition = confuse->GetPosition();   //敵の座標を受け取る
		D3DXVECTOR3 direction = m_Position - ConfBulletPosition;
		float length = D3DXVec3Length(&direction);
		if (length < 2.0f)
		{
			m_Hps  -= 1;
			m_isConfusion = true;
			return;
		}
		
	}
}
//毒の弾との当たり判定
void Player::CollisuinPoisonBullet()
{
	Scene* scenes = Manager::GetScene();
	std::vector<PoisonBullet*> Poisonbulletlist = scenes->GetGameObjects<PoisonBullet>(1);
	for (PoisonBullet* ebullet : Poisonbulletlist)
	{

		D3DXVECTOR3 EnemyPosition = ebullet->GetPosition();   //敵の座標を受け取る
		D3DXVECTOR3 direction = m_Position - EnemyPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 2.0f)
		{
			m_Hps -= 1;
		
			m_isPoison = true;
			scenes->AddGameObject<PoisonEffect>(1)->SetPosition(m_Position);
			return;
		}
		
	}
}

//HPアイテムとの当たり判定
void Player::CollisionHpItem()
{
	Scene* scene = Manager::GetScene();
	std::vector<HpItem*> HpItemList = scene->GetGameObjects<HpItem>(1);

	for (HpItem* HpItems : HpItemList)
	{
		D3DXVECTOR3 HpItemPosition = HpItems->GetPosition();   //敵の座標を受け取る
		D3DXVECTOR3 direction = m_Position - HpItemPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 2.0f)
		{
			m_HP += 1;
			HpItems->SetDestroy();
			m_isHpItem = true;
			return;
		}
		HpItemProcess();
	}
}

//ドアとの当たり判定
void Player::CollisionDoor()
{
	Scene* scene = Manager::GetScene();
	std::vector<DoorCollision*> DoorList = scene->GetGameObjects<DoorCollision>(1);

	for (DoorCollision* door : DoorList)
	{
		D3DXVECTOR3 DoorPosition = door->GetPosition();//ドアの座標を受け取る
		D3DXVECTOR3 direction = m_Position - DoorPosition;
		float length = D3DXVec3Length(&direction);
		if (length < 2.0f && !m_isCheck)
		{
			m_Position += m_Forward * move;
		}
	}
}

//敵との当たり判定
void Player::ColllisionEnemy()
{

	Scene* scene = Manager::GetScene();
	std::vector<Enemy*> EnemyList = scene->GetGameObjects<Enemy>(1);

	for (Enemy* enemy : EnemyList)
	{
		D3DXVECTOR3 EnemyPosition = enemy->GetPosition();   //敵の座標を受け取る
		D3DXVECTOR3 direction = m_Position - EnemyPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 2.0f)
		{
			m_HP -= 1;
			SetDestroy();        //弾の破壊
			Change = true;
			return;
		}

	}
}

//矢の種類を変更
void Player::ArrowModeChange()
{
	if (Input::GetKeyTrigger('Q'))
	{
		//二つ同時→二方向
		if (m_Mode == ARROWMODE_DOUBLE)
		{
			m_Mode = ArrowMode::ARROWMODE_TWOWAY;
		}

		//通常→二本同時
		else if (m_Mode == ARROWMODE_NORMAL)
		{
			m_Mode = ArrowMode::ARROWMODE_DOUBLE;
		}

		//二方向→通常
		else if (m_Mode = ARROWMODE_TWOWAY)
		{
			m_Mode = ArrowMode::ARROWMODE_NORMAL;
		}
	}
}
//Hpアイテムを取得したときの処理
void Player::HpItemProcess()
{
	if (m_isHpItem)
	{
		m_HItemCnt -= 1;
		m_HP += 1;
		if (m_HItemCnt < 0)
		{
			m_HItemCnt = 50;
			m_isHpItem = false;
		}
	}
}

void Player::CollisionStateBullet()
{
	Scene* scenes = Manager::GetScene();
	std::vector<StateBullet*> Enemybulletlist = scenes->GetGameObjects<StateBullet>(1);
	for (StateBullet* ebullet : Enemybulletlist)
	{
		D3DXVECTOR3 EnemyPosition = ebullet->GetPosition();   //敵の座標を受け取る
		D3DXVECTOR3 direction = m_Position - EnemyPosition;
		float length = D3DXVec3Length(&direction);
		if (length < 2.0f)
		{
			m_Hps -= 0.5f;
			m_PoisonCnt += 1;
			m_isPoison = true;
			return;
		}
	}
}

//スピードアイテムとの当たり判定
void Player::CollisionSpeed()
{
	Scene* scene = Manager::GetScene();
	std::vector<Speed*> SpeedList = scene->GetGameObjects<Speed>(1);
	for (Speed* speed : SpeedList)
	{
		D3DXVECTOR3 SpeedPosition = speed->GetPosition();   //敵の座標を受け取る
		D3DXVECTOR3 direction = m_Position - SpeedPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 2.0f)
		{
			m_IsSp = true;
			speed->Speedefect();
			speed->SetDestroy();

			return;
		}

	}
}

bool Player::SetPosion()
{
	return m_isPoison;
}

void Player::ChangePoison()
{
	if (m_isPoison)
	{
		m_isPoison = false;
	}

	else if (!m_isPoison)
	{
		m_isPoison = true;
	}
	
}

void Player::ChangeConfusion()
{
	m_isConfusion = true;
}



