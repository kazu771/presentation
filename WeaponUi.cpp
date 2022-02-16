//====================================================================================================================
//武器UI基本処理.cpp
//date:2021/11/15    name:Kazuki Wada
//====================================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "assetnames.h"
#include "input.h"
#include "Texture.h"
#include "Sprite.h"
#include "WeaponUi.h"

void WeaponUi::Init()
{
	m_mode = WeaponMode::WEAPONMODE_NORMAL;//最初は銃
	Texture::Init();
	Sprite::Init();

}

void WeaponUi::UnInit()
{
	Texture::Uninit();
	Sprite::Uninit();
}

void WeaponUi::Update()
{
	ChangeMode();
}

void WeaponUi::Draw()
{
	switch (m_mode)
	{
	case WeaponUi::WEAPONMODE_NORMAL:
		Sprite::Draw(Texture::GetNum(TX_NORMAL), 400.0f, 200.0f, 100.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case WeaponUi::WEAPONMODE_DOUBLE:
		Sprite::Draw(Texture::GetNum(TX_DOUBLE), 400.0f, 200.0f, 100.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case WeaponUi::WEAPONMODE_TWOWAY:
		Sprite::Draw(Texture::GetNum(TX_TWOWAY), 400.0f, 200.0f, 100.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		break;

	default:
		break;
	}
}

//武器UIのチェンジ
void WeaponUi::ChangeMode()
{
	if (Input::GetKeyTrigger('Q'))
	{
		switch (m_mode)
		{
		case WeaponMode::WEAPONMODE_NORMAL:
			m_mode = WeaponMode::WEAPONMODE_DOUBLE;
			break;

		case WeaponMode::WEAPONMODE_DOUBLE:
			m_mode = WeaponMode::WEAPONMODE_TWOWAY;
			break;

		case WeaponUi::WEAPONMODE_TWOWAY:
			m_mode = WeaponMode::WEAPONMODE_NORMAL;
			break;
		default:
			break;
		}
	}
}
