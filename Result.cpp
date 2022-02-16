//==================================================================================================
//���U���g��{����.cpp[Result.cpp]
//date:2021/08/30  name:Kazuki Wada
//==================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "Result.h"
#include "Title.h"

#include "Texture.h"
#include "Sprite.h"
#include "assetnames.h"

//������
void Result::Init()
{
	Texture::Init();
	Sprite::Init();
	isUse = false;
	isFade = false;
	a = 0.0f;
	alfa = 0.0f;
	fadein = 0.0f;
	
}

//�I��
void Result::UnInit()
{
	Scene::UnInit(); //�p������uninit�̌Ăяo��,�I�[�o�[���C�h����Ƃǂ��炩�������Ă΂��悤�ɂȂ邽�߂����ň�x�Ă΂Ȃ��ƃ_��
	Scene::UnInit(); //�p������uninit�̌Ăяo��,�I�[�o�[���C�h����Ƃǂ��炩�������Ă΂��悤�ɂȂ邽�߂����ň�x�Ă΂Ȃ��ƃ_��
	Texture::Uninit();
	Sprite::Uninit();
}

//�X�V
void Result::Update()
{
	Scene::Update();
	fadein += 0.1f;
	alfa += 0.01f;
	a = (float)sinf(fadein);
	if (alfa>= 1.0f)
	{
		isUse = true;
	}
	
	//�V�[���̈ڍs
	if (Input::GetKeyTrigger(VK_SPACE))
	{
		Manager::Setscene<Title>();
	}
}

void Result::Draw()
{
	//Sprite::Draw(Texture::GetNum(TX_BACK), 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 512.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, alfa);
		Sprite::Draw(Texture::GetNum(TX_BACK), 10.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, alfa);
		Sprite::Draw(Texture::GetNum(TX_END), 0.0f, 200.0f, 512.0f, 512.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, alfa);
		if (isUse)
		{
			Sprite::Draw(Texture::GetNum(TX_PUSH), 50.0f, 120.0f, 512.0f, 512.0f, 100.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, a);
		}
}