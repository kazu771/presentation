//=================================================================================================
//ゲーム基本処理.cpp
//date:2021/08/31      name:Kauzki Wada
//=================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "audio.h"
#include "input.h"
#include "polygon2D.h"
#include "Field.h"
#include "Camera.h"
#include "Wall.h"
#include "model.h"
#include "player.h"
#include "Enemy.h"
#include "Item.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Sky.h"
#include "Reload.h"
#include "Tree.h"
#include "Shadow.h"
#include "Game.h"
#include "Speed.h"
#include "EnemyBullet.h"
#include "BoxCollision.h"
#include "Title.h"
#include "Result.h"
#include "MeshField.h"
#include "Enemysite.h"
#include "Spider.h"
#include "GameUi.h"
#include "PoisonBullet.h"
#include "Key.h"
#include "Door.h"
#include "RightDoor.h"
#include "TwoWayBullet.h"
#include "TwoWayBulletRight.h"
#include "Rock.h"
#include "ConfusionBullet.h"
#include "HpItem.h"
#include "DoorCollision.h"
#include "ChargeBullet.h"
#include "StateBullet.h"
#include "Trophy.h"
#include "Clear.h"
#include "GameOver.h"

//初期化
void Game::Init()
{
	GameUi_Init();
	Bullet::Load();
	ChargeBullet::Load();
	ConfusionBullet::Load();
	TwoWay::Load();
	TwowayRIght::Load();
	StateBullet::Load();

	isChange = false;
	//0:カメラ,1:3D関係のオブジェクト,2:2Dのポリゴン(UIなど)
	AddGameObject<Camera>(0);
	AddGameObject<MeshField>(1);
	AddGameObject<Sky>(1);
	AddGameObject<Player>(1);
	AddGameObject<BoxCollision>(1)->SetPosition(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	//オブジェクト
	{
		//木の生成
		for (int i = 0; i < 5; i++)
		{
			D3DXVECTOR3 pos;
			//乱数で配置の制御
			pos.x = (float)rand() / RAND_MAX * 100.0f - 50.0f;
			pos.z = (float)rand() / RAND_MAX * 100.0f - 50.0f;
			pos.y = 1.5f;
			Tree* tree = AddGameObject<Tree>(1);
			tree->SetPosition(pos);
			tree->SetRotation(pos);
			D3DXVECTOR3 scl;
			scl.x = scl.y = scl.z = (float)rand() / RAND_MAX * 6.0f + 2.0f;
			tree->SetScale(scl);
		}
		AddGameObject<Rock>(1)->SetPosition(D3DXVECTOR3(10.0f, 1.0f, 30.0f));
		AddGameObject<Wall>(1);
		AddGameObject<Door>(1)->SetPosition(D3DXVECTOR3(-35.0f, 0.5f, 35.0f));
		AddGameObject<RightDoor>(1)->SetPosition(D3DXVECTOR3(-35.0f, 0.5f, 33.0f));
		AddGameObject<DoorCollision>(1)->SetPosition(D3DXVECTOR3(-37.5f, 0.0f, 35.0f));
		AddGameObject<HpItem>(1)->SetPosition(D3DXVECTOR3(4.0f, 1.5f, -10.0f));
		AddGameObject<Trophy>(1)->SetPosition(D3DXVECTOR3(-35.5f, 1.0f, 38.0f));
	}

	//敵関連
	{
		AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(15.0f, 3.0f, 10.0f));
		AddGameObject<Spider>(1)->SetPosition(D3DXVECTOR3(-8.0f, 3.0f, -10.0f));
		AddGameObject<Spider>(1)->SetPosition(D3DXVECTOR3(10.0f, 3.0f, 50.0f));
		AddGameObject<Spider>(1)->SetPosition(D3DXVECTOR3(30.0f, 3.0f, 4.0f));
		AddGameObject<Spider>(1)->SetPosition(D3DXVECTOR3(40.0f, 3.0f, 4.0f));
	}


	
	Audio* bgm = AddGameObject<Audio>(2);

	bgm->Load("asset\\bgm\\neo.wav");
	bgm->Play(true); //ループ再生されるように引数にtrueを代入
}

//終了
void Game::UnInit()
{
	//継承元のUnInit()が呼ばれないため
	Scene::UnInit(); //継承元のuninitの呼び出し,オーバーライドするとどちらかだけが呼ばれるようになるためここで一度呼ばないとダメ
	Bullet::UnLoad();
	ChargeBullet::UnLoad();
	ConfusionBullet::UnLoad();
//	EnemyBullet::UnLoad();
//	PoisonBullet::UnLoad();
	TwoWay::UnLoad();
	TwowayRIght::UnLoad();
	StateBullet::UnLoad();
	GameUi_UnInit();
	/*Enemy::UnLoad();*/
	
}

//更新
void Game::Update()
{
	Scene::Update();
	GameUi_Update();
	
//	std::vector<Enemy*> EnemyList = GetGameObjects<Enemy>(1); //敵が複数いるためgameobjects
	std::vector<Player*> PlayerList = GetGameObjects<Player>(1);
	std::vector<Trophy*> TrophyList = GetGameObjects<Trophy>(1);//今はカギにしている
	
	//トロフィーを取得 → ゲームクリア画面に遷移
	if (TrophyList.size() == 0)
	{
		Manager::Setscene<Clear>();
	}

	//プレイヤーが死んだらゲームオーバー画面に遷移
	if (PlayerList.size() == 0)
	{
		Manager::Setscene<GameOver>();
	}
}

void Game::Draw()
{
	Scene::Draw();
	GameUi_Draw();
}