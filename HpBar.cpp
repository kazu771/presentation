//=================================================================================================
//体力バーの基本処理.cpp
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
	m_isItem = m_Player->GetHpItem();//アイテムを取得したかどうかの判定
	m_isShrink = m_Player->GetPoison();//最初の状態を送っておく
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
	
	m_isShrink = m_Player->GetPoison();//毒の弾にあったとかどうかの受け取り

	m_isItem = m_Player->GetHpItem();//アイテムをとったかどうかの受け取り
	m_isCon = m_Player->GetConfusion();//混乱する弾にあったかどうかの受け取り
	
	//毒状態のとき
	if (m_isShrink)
	{
		m_Tx -= 0.5f;
		m_Ty -= 0.5f;
	}

	//混乱する弾に触れたとき
	if (m_isCon)
	{
		m_Tx -= 0.5f;
		m_Ty -= 0.5f;
	}
	//体力アイテムを取得したとき
	if (m_isItem)
	{
		m_Cnt -= 1;

		//拡大の制限(x,yともに100.0fが最大それ以上は大きくならないように制限)
		if (m_Tx < 100.0f && m_Ty < 100.0f)
		{
			m_Tx += 1.1f;
			m_Ty += 1.1f;
		}
	}
	//カウントでどれくらい拡大するかを指定
	if (m_Cnt < 0.0f)
	{
		m_isItem = false;
	}
	//小さくなりすぎないように設定
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
