//======================================================================================
//menu基本処理.h[Menu.h]
//date:2021/07/12  name:Kazuki Wada
//======================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "Menu.h"
#include "Rule.h"
#include "Game.h"
#include "Texture.h"
#include "Sprite.h"
#include "assetnames.h"
#include "Explaine.h"

//初期化
void Menu::Init()
{
	Texture::Init();
	Sprite::Init();
	x = -370.0f;
	isUse = false;
	isVisible = false;
	fadein = 0.0f;
	
}

//終了
void Menu::UnInit()
{
	Scene::UnInit(); //継承元のuninitの呼び出し,オーバーライドするとどちらかだけが呼ばれるようになるためここで一度呼ばないとダメ
	Texture::Uninit();
	Sprite::Uninit();
}

//更新
void Menu::Update()
{
	Scene::Update();


	//ポインターの移動
	{
		//左に移動
		if (Input::GetKeyTrigger('A'))
		{
			x -= 300.0f;
			//Manager::Setscene<Game>();
		}
		//右に移動
		if (Input::GetKeyTrigger('D'))
		{
			x += 300.0f;
		}

		//制限
		{
			if (x <= -380.0f)
			{
				x = 230.0f;
			}
			if (x >= 240.0f)
			{
				x = -370.0f;
			}
		}
	}

	//ゲーム画面に遷移
	if (x == -370.0f)
	{
		if (Input::GetKeyTrigger(VK_SPACE))
		{
			isUse = true;
		}
		if (isVisible)
		{
			Manager::Setscene<Game>();
		}
	}
	//ルール画面
	if (x == -70.0f)
	{
		if (Input::GetKeyTrigger(VK_SPACE))
		{
			isUse = true;
		}
		if (isVisible == true)
		{
			Manager::Setscene<Rule>();
		}
	}

	//操作説明画面
	if (x == 230.0f)
	{
		if (Input::GetKeyTrigger(VK_SPACE))
		{
			isUse = true;
		}
		if (isVisible == true)
		{
			Manager::Setscene<Explaine>();
		}
	}
	if (isUse)
	{
		fadein += 0.01f;
	}
	if (fadein >= 1.0f)
	{
		isVisible = true;
	}

}

void Menu::Draw()
{
	Sprite::Draw(Texture::GetNum(TX_GLOGO), -350.0f, 0.0f, 512.0f, 512.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	Sprite::Draw(Texture::GetNum(TX_HAND), x, 50.0f, 124.0f, 124.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	Sprite::Draw(Texture::GetNum(TX_RULEROGO), 0.0f, 0.0f, 512.0f, 512.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	Sprite::Draw(Texture::GetNum(TX_EXPLOGO), 240.0f, 140.0f, 512.0f, 512.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);



	if (isUse)
	{
		Sprite::Draw(Texture::GetNum(TX_FADE), 0.0f, 0.0f, 960.0f, 540.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fadein);
	}
}