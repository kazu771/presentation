//=========================================================================================================
//ç¨óêäÓñ{èàóù.h[Confusion.h]
//date:2021/11/30   name:Kauzki Wada
//=========================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "assetnames.h"
#include "Texture.h"
#include "Sprite.h"
#include "player.h"
#include "Confusion.h"

void Confusion::Change()
{
	if (!m_isConfusion)
	{
		m_isConfusion = true;
	}
}

bool Confusion::State()
{
	return m_isConfusion;
}

void Confusion::Init()
{
	Texture::Init();
	Sprite::Init();
	Scene* scene = Manager::GetScene();
	m_player = scene->AddGameObject<Player>(1);
	m_isConfusion = m_player->GetConfusion();//åªç›ÇÃç¨óêÇ©Ç«Ç§Ç©ÇéÊìæ
	m_Alfa = 0.0f;
}

void Confusion::UnInit()
{
	Texture::Uninit();
	Sprite::Uninit();
}

void Confusion::Update()
{
	m_isConfusion = m_player->GetConfusion();//åªç›ÇÃç¨óêÇ©Ç«Ç§Ç©ÇéÊìæ
	if (m_isConfusion)
	{
		if (m_Alfa == 0.0f)
		{
			m_Alfa = 1.0f;
		}
	}
	else if (!m_isConfusion)
	{
		if (m_Alfa == 1.0f)
		{
			m_Alfa = 0.0f;
		}
	}
}

void Confusion::Draw()
{
	if (m_isConfusion)
	{
		Sprite::Draw(Texture::GetNum(TX_CONFUSE), 100.0f, 200.0f, 80.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, m_Alfa);
	}
}
