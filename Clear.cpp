//================================================================================================================
//ゲームクリア基本処理.cpp[Clear.cpp]
//date:2022/01/25         name:Kazuki Wada
//================================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "Texture.h"
#include "Sprite.h"
#include "assetnames.h"
#include "Clear.h"
#include "Title.h"

void Clear::Init()
{
	Texture::Init();
	Sprite::Init();
	m_isUse = false;
	m_isChange = false;
	m_alfa = 1.0f;
	m_Var = 0.0f;
}

void Clear::UnInit()
{
	Scene::UnInit(); //継承元のuninitの呼び出し,オーバーライドするとどちらかだけが呼ばれるようになるためここで一度呼ばないとダメ
	Texture::Uninit();
	Sprite::Uninit();
}

void Clear::Update()
{
	if (Input::GetKeyTrigger(VK_SPACE))
	{
		Manager::Setscene<Title>();
	}

	m_Var += 0.1f;

	m_alfa = sinf(m_Var);
}

void Clear::Draw()
{
	
		Sprite::Draw(Texture::GetNum(TX_CLEAR), 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

		//ボタンロゴ
		Sprite::Draw(Texture::GetNum(TX_PUSH), 50.0f, 190.0f, 512.0f, 512.0f, 100.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, m_alfa);
}
