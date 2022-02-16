//================================================================================================
//�_���[�W�pUI��{����.cpp[DamageUi.cpp]
//date:2021/12/07      name:Kazuki Wada
//================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "assetnames.h"
#include "input.h"
#include "Texture.h"
#include "Sprite.h"
#include "DamageUi.h"

void DamageUi::Init()
{
	m_Cnt = 0;
	m_Tx = 100.0f;
	m_Ty = 200.0f;
	m_PosX = 0.0f;
	m_PosY = 0.0f;
	m_Poison = false;
	m_Confusion = false;
}

void DamageUi::UnInit()
{
	Texture::Uninit();
	Sprite::Uninit();
}

void DamageUi::Update()
{
	//�ŏ�ԂȂ�k��
	if (m_Poison)
	{
		m_Tx += 95;
	}
	//������Ԃł��k��
	else if (m_Confusion)
	{
		if (m_Tx >= 95)
		{
			m_Tx += 95;
		}

		
		else if (m_Tx < 95)
		{
			m_Tx += 190;
		}

		for (int i = 0; i < 5; i++)
		{
			m_Cnt += 1;
			m_PosY += 0.1f;
		}
	}
	
	//50�Ő���
	if (m_Cnt > 50)
	{
		m_Cnt = 0;
		//�ł̕ϐ���true�Ȃ�false�֕ϊ�
		if (m_Poison)
		{
			m_Poison = false;
		}
		//�����̕ϐ���true�Ȃ�false�ɕϊ�
		else if (m_Confusion)
		{
			m_Confusion = false;
		}
	}
}

void DamageUi::Draw()
{
	if (m_Cnt < 50 && m_Poison || m_Confusion)
	{
		Sprite::Draw(Texture::GetNum(TX_DAMAGE), m_PosX, m_PosY, m_Ty, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	}
}

void DamageUi::ChangePosion()
{
	m_Poison = true;
}

void DamageUi::ChangeConfusion()
{
	m_Confusion = true;
}

void DamageUi::SetPosition(float x, float y)
{
	m_PosX = x;
	m_PosY = y;
}
