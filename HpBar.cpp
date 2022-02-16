//=================================================================================================
//�̗̓o�[�̊�{����.cpp
//date:2021/11/11   name:Kazuki Wada
//================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "assetnames.h"
#include "input.h"
#include "Texture.h"
#include "Sprite.h"
#include "HpItem.h"
#include "HpBar.h"
#include "player.h"

void HpBar::Init()
{
	Texture::Init();
	Sprite::Init();
	Scene* scene = Manager::GetScene();
	m_Player = scene->AddGameObject<Player>(1);
	m_Item = scene->AddGameObject<HpItem>(1);
	m_TexNumX = 5;
	m_TexNumY = 2;
	m_Cnt = 5;
	m_Tx = 100.0f;
	m_Ty = 100.0f;
	m_Minus = 0.0f;
	m_Frame = 0.0f;
	m_isItem = m_Player->GetHpItem();//�A�C�e�����擾�������ǂ����̔���
	m_isShrink = m_Player->GetPoison();//�ŏ��̏�Ԃ𑗂��Ă���
	m_isCon = m_Player->GetConfusion();
	m_isDeath = false;
}

void HpBar::UnInit()
{
	Texture::Uninit();
	Sprite::Uninit();
}

void HpBar::Update()
{
	
	m_isShrink = m_Player->GetPoison();//�ł̒e�ɂ������Ƃ��ǂ����̎󂯎��

	m_isItem = m_Player->GetHpItem();//�A�C�e�����Ƃ������ǂ����̎󂯎��
	m_isCon = m_Player->GetConfusion();//��������e�ɂ��������ǂ����̎󂯎��
	
	//�ŏ�Ԃ̂Ƃ�
	if (m_isShrink)
	{
		m_Tx -= 0.5f;
		m_Ty -= 0.5f;
	}

	//��������e�ɐG�ꂽ�Ƃ�
	if (m_isCon)
	{
		m_Tx -= 0.5f;
		m_Ty -= 0.5f;
	}
	//�̗̓A�C�e�����擾�����Ƃ�
	if (m_isItem)
	{
		m_Cnt -= 1;

		//�g��̐���(x,y�Ƃ���100.0f���ő傻��ȏ�͑傫���Ȃ�Ȃ��悤�ɐ���)
		if (m_Tx < 100.0f && m_Ty < 100.0f)
		{
			m_Tx += 1.1f;
			m_Ty += 1.1f;
		}
	}
	//�J�E���g�łǂꂭ�炢�g�傷�邩���w��
	if (m_Cnt < 0.0f)
	{
		m_isItem = false;
	}
	//�������Ȃ肷���Ȃ��悤�ɐݒ�
	if (m_Tx < 2.0f && m_Ty < 2.0f)
	{
		/*m_isDeath = true;*/
		m_Tx = 2.0f;
		m_Ty = 2.0f;
	}
}

void HpBar::Draw()
{
	Sprite::Draw(Texture::GetNum(TX_HEART), 0.0f, 200.0f, m_Tx, m_Ty, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	
}

bool HpBar::HpFlug()
{
	return m_isDeath;
}
