//===================================================================================================================================
//ルール基本処理.cpp[Rule.cpp]
//date:2021/04/27   name:Kazuki Wada
//====================================================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "Menu.h"
#include "Rule.h"
#include "Game.h"
#include "assetnames.h"
#include "Texture.h"
#include "Sprite.h"
//初期化
void Rule::Init()
{
	Texture::Init();
	Sprite::Init();
	isUse = false;
	isVisible = false;
	a = 0.0f;
	alfa = 0.0f;
	fadein = 0.0f;
}

//終了
void Rule::UnInit()
{
	Scene::UnInit(); //継承元のuninitの呼び出し,オーバーライドするとどちらかだけが呼ばれるようになるためここで一度呼ばないとダメ
	Texture::Uninit();
	Sprite::Uninit();
}

//更新
void Rule::Update()
{
	Scene::Update();
	a += 0.1f;
	alfa = (float)sinf(a);

	if (Input::GetKeyTrigger(VK_SPACE))
	{
		isUse = true;
	}

	if (isUse)
	{
		fadein += 0.01f;
	}

	if (fadein >= 1.0f)
	{
		isVisible = true;
	}

	if (isVisible)
	{
		Manager::Setscene<Game>();
	}
}

void Rule::Draw()
{
	Sprite::Draw(Texture::GetNum(TX_BACK), 0.0f, 0.0f, 960.0f, 540.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	Sprite::Draw(Texture::GetNum(TX_RULE), 0.0f, 0.0f, 512.0f, 512.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	
	Sprite::Draw(Texture::GetNum(TX_WPUSH), 50.0f, 340.0f, 512.0f, 512.0f, 100.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, alfa);
	if (isUse)
	{
		Sprite::Draw(Texture::GetNum(TX_FADE), 0.0f, 0.0f, 960.0f, 700.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fadein);
	}
}

