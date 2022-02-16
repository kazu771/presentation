//=================================================================================================
//�Q�[����{����.cpp
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

//������
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
	//0:�J����,1:3D�֌W�̃I�u�W�F�N�g,2:2D�̃|���S��(UI�Ȃ�)
	AddGameObject<Camera>(0);
	AddGameObject<MeshField>(1);
	AddGameObject<Sky>(1);
	AddGameObject<Player>(1);
	AddGameObject<BoxCollision>(1)->SetPosition(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	//�I�u�W�F�N�g
	{
		//�؂̐���
		for (int i = 0; i < 5; i++)
		{
			D3DXVECTOR3 pos;
			//�����Ŕz�u�̐���
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

	//�G�֘A
	{
		AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(15.0f, 3.0f, 10.0f));
		AddGameObject<Spider>(1)->SetPosition(D3DXVECTOR3(-8.0f, 3.0f, -10.0f));
		AddGameObject<Spider>(1)->SetPosition(D3DXVECTOR3(10.0f, 3.0f, 50.0f));
		AddGameObject<Spider>(1)->SetPosition(D3DXVECTOR3(30.0f, 3.0f, 4.0f));
		AddGameObject<Spider>(1)->SetPosition(D3DXVECTOR3(40.0f, 3.0f, 4.0f));
	}


	
	Audio* bgm = AddGameObject<Audio>(2);

	bgm->Load("asset\\bgm\\neo.wav");
	bgm->Play(true); //���[�v�Đ������悤�Ɉ�����true����
}

//�I��
void Game::UnInit()
{
	//�p������UnInit()���Ă΂�Ȃ�����
	Scene::UnInit(); //�p������uninit�̌Ăяo��,�I�[�o�[���C�h����Ƃǂ��炩�������Ă΂��悤�ɂȂ邽�߂����ň�x�Ă΂Ȃ��ƃ_��
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

//�X�V
void Game::Update()
{
	Scene::Update();
	GameUi_Update();
	
//	std::vector<Enemy*> EnemyList = GetGameObjects<Enemy>(1); //�G���������邽��gameobjects
	std::vector<Player*> PlayerList = GetGameObjects<Player>(1);
	std::vector<Trophy*> TrophyList = GetGameObjects<Trophy>(1);//���̓J�M�ɂ��Ă���
	
	//�g���t�B�[���擾 �� �Q�[���N���A��ʂɑJ��
	if (TrophyList.size() == 0)
	{
		Manager::Setscene<Clear>();
	}

	//�v���C���[�����񂾂�Q�[���I�[�o�[��ʂɑJ��
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