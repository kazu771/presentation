//====================================================================================================================
//èÛë‘àŸèÌÅiì≈ÅjäÓñ{èàóù.cpp[Poison.cpp]
//date:2021/11/18   name:Kazuki Wada
//====================================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "assetnames.h"
#include "input.h"
#include "Texture.h"
#include "Sprite.h"
#include "Poison.h"
#include "player.h"

void Poison::Init()
{
	Texture::Init();
	Sprite::Init();
	Scene* scene = Manager::GetScene();
	m_player = scene->AddGameObject<Player>(1);
	
	m_isUse = m_player->GetPoison();
	m_Alfa = 0.0f;
}

void Poison::UnInit()
{
	Texture::Uninit();
	Sprite::Uninit();
}

void Poison::Update()
{
	m_isUse = m_player->GetPoison();
	if (m_isUse)
	{
		if (m_Alfa == 0.0f)
		{
			m_Alfa = 1.0f;
		}
	}
	else if (!m_isUse)
	{
	 if (m_Alfa == 1.0f)
		{
			m_Alfa = 0.0f;
		}
	}
}

void Poison::Draw()
{
	if (m_isUse)
	{
		Sprite::Draw(Texture::GetNum(TX_POISON), 300.0f, 200.0f, 80.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, m_Alfa);
	}
}

//ì≈ÇÃèÛë‘ÇïœÇ¶ÇÈÇÊÇ§
void Poison::ChangePoison()
{
	if (m_isUse)
	{
		m_isUse = false;
	}
	else if (!m_isUse)
	{
		m_isUse = true;
	}
}

void Poison::PoisonChange()
{
	m_isUse = true;
}
