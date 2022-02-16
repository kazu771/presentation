//========================================================================================
//操作説明基本処理.cpp[Explaine.cpp]
//ate:2021/08/28  name:Kazuki Wada
//========================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "assetnames.h"
#include "Texture.h"
#include "Sprite.h"
#include "Menu.h"
#include "Explaine.h"
#include "Rule.h"

void Explaine::Init()
{
	Texture::Init();
	Sprite::Init();
	alfa = 0.0f;
	a = 0.0f;
	fadein = 0.0f;
	isUse = false;
	isVisible = false;
	
}

void Explaine::UnInit()
{
	Scene::UnInit(); //継承元のuninitの呼び出し,オーバーライドするとどちらかだけが呼ばれるようになるためここで一度呼ばないとダメ
	Texture::Uninit();
	Sprite::Uninit();
}


void Explaine::Update()
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
		Manager::Setscene<Rule>();
	}
}


void Explaine::Draw()
{
	Sprite::Draw(Texture::GetNum(TX_BACK), 0.0f, 0.0f, 960.0f, 540.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	Sprite::Draw(Texture::GetNum(TX_EXP), 0.0f, 0.0f, 960.0f,540.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	Sprite::Draw(Texture::GetNum(TX_WPUSH), 150.0f, 300.0f, 512.0f, 512.0f, 100.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, alfa);
	if (isUse)
	{
		Sprite::Draw(Texture::GetNum(TX_FADE), 0.0f, 0.0f, 960.0f, 700.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fadein);
	}
}