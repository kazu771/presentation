//==================================================================================================================
//チャージUI基本処理.cpp[ChargeUi.cpp]
//date:2022/01/12   name:Kazuki Wada
//==================================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "assetnames.h"
#include "Texture.h"
#include "Sprite.h"
#include "player.h"
#include "ChargeUi.h"
#include "input.h"

void ChargeUi::Init()
{
	Texture::Init();
	Sprite::Init();
	Scene* scene = Manager::GetScene();
	m_Player = scene->AddGameObject<Player>(1);
	m_Extend = 0.0f;
	m_PosX = 0.0f;
	m_IsCarges = false;
}

void ChargeUi::UnInit()
{
	Texture::Uninit();
	Sprite::Uninit();
}

void ChargeUi::Update()
{
	m_IsCarges = m_Player->GetCharge(); //チャージ変数の受け取り
	
	//チャージしてる時はのバス用の変数を+していく
	if (m_IsCarges)
	{
		m_Extend += 1.0f;
	}
	//チャージをやめたとき
	else if (!m_IsCarges)
	{
		m_Extend = 0.0f;
	}
	//拡大の範囲指定
	if (m_Extend > 100.0f)
	{
		m_Extend = 100.0f;
	}
}

void ChargeUi::Draw()
{
	if (m_IsCarges)
	{
		Sprite::Draws(Texture::GetNum(TX_CHARGEBAR), -400.0f + m_PosX, 200.0f, 10.0f + m_Extend, 10.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	}
}
