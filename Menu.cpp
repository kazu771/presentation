//======================================================================================
//menu��{����.h[Menu.h]
//date:2021/07/12  name:Kazuki Wada
//======================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "Menu.h"
#include "Rule.h"
#include "Game.h"
#include "Texture.h"
#include "Sprite.h"
#include "assetnames.h"
#include "Explaine.h"

//������
void Menu::Init()
{
	Texture::Init();
	Sprite::Init();
	x = -370.0f;
	isUse = false;
	isVisible = false;
	fadein = 0.0f;
	
}

//�I��
void Menu::UnInit()
{
	Scene::UnInit(); //�p������uninit�̌Ăяo��,�I�[�o�[���C�h����Ƃǂ��炩�������Ă΂��悤�ɂȂ邽�߂����ň�x�Ă΂Ȃ��ƃ_��
	Texture::Uninit();
	Sprite::Uninit();
}

//�X�V
void Menu::Update()
{
	Scene::Update();


	//�|�C���^�[�̈ړ�
	{
		//���Ɉړ�
		if (Input::GetKeyTrigger('A'))
		{
			x -= 300.0f;
			//Manager::Setscene<Game>();
		}
		//�E�Ɉړ�
		if (Input::GetKeyTrigger('D'))
		{
			x += 300.0f;
		}

		//����
		{
			if (x <= -380.0f)
			{
				x = 230.0f;
			}
			if (x >= 240.0f)
			{
				x = -370.0f;
			}
		}
	}

	//�Q�[����ʂɑJ��
	if (x == -370.0f)
	{
		if (Input::GetKeyTrigger(VK_SPACE))
		{
			isUse = true;
		}
		if (isVisible)
		{
			Manager::Setscene<Game>();
		}
	}
	//���[�����
	if (x == -70.0f)
	{
		if (Input::GetKeyTrigger(VK_SPACE))
		{
			isUse = true;
		}
		if (isVisible == true)
		{
			Manager::Setscene<Rule>();
		}
	}

	//����������
	if (x == 230.0f)
	{
		if (Input::GetKeyTrigger(VK_SPACE))
		{
			isUse = true;
		}
		if (isVisible == true)
		{
			Manager::Setscene<Explaine>();
		}
	}
	if (isUse)
	{
		fadein += 0.01f;
	}
	if (fadein >= 1.0f)
	{
		isVisible = true;
	}

}

void Menu::Draw()
{
	Sprite::Draw(Texture::GetNum(TX_GLOGO), -350.0f, 0.0f, 512.0f, 512.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	Sprite::Draw(Texture::GetNum(TX_HAND), x, 50.0f, 124.0f, 124.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	Sprite::Draw(Texture::GetNum(TX_RULEROGO), 0.0f, 0.0f, 512.0f, 512.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	Sprite::Draw(Texture::GetNum(TX_EXPLOGO), 240.0f, 140.0f, 512.0f, 512.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);



	if (isUse)
	{
		Sprite::Draw(Texture::GetNum(TX_FADE), 0.0f, 0.0f, 960.0f, 540.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, fadein);
	}
}