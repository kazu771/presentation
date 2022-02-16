//===================================================================================================================================
//タイトル基本処理.cpp[Title.cpp]
//date:2021/04/27   name:Kazuki Wada
//====================================================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "assetnames.h"
#include "Title.h"
#include "Titlelogo.h"
#include "Menu.h"
#include "Game.h"
#include "Texture.h"
#include "Sprite.h"
#include "Explaine.h"
#include "player.h"

//初期化
void Title::Init()
{
	Texture::Init();
	Sprite::Init();
	alfa = 0.0f;
	
	isUse = false;
	isVisible = false;
	a = 0.0f;
	fadein = 0.0f;
	fade = 0.0f;
}

//終了
void Title::UnInit()
{
	Scene::UnInit(); //継承元のuninitの呼び出し,オーバーライドするとどちらかだけが呼ばれるようになるためここで一度呼ばないとダメ
	Texture::Uninit();
	Sprite::Uninit();
}

//更新
void Title::Update()
{

	//a += 0.05f;
	a += 0.1f;
	alfa = (float)sinf(a);
	fade += 0.01f;
	//fadein += 0.01f;
	Scene* scene = Manager::GetScene();
	Scene::Update();
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
		Manager::Setscene<Explaine>();
	}
}



void Title::Draw()
{
	Sprite::Draw(Texture::GetNum(TX_FIRST), 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fade);
	//Sprite::Draw(Texture::GetNum(TX_TITLE), 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, fade);
	if (fade >= 1.0f)
	{
		Sprite::Draw(Texture::GetNum(TX_PUSH), 50.0f, 190.0f, 512.0f, 512.0f, 100.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, alfa);
	}
	if (isUse)
	{
		Sprite::Draw(Texture::GetNum(TX_FADE), 0.0f, 0.0f, 960.0f, 700.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fadein);
	}

}