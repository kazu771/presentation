//=================================================================================================
//‹ó‚Ì‘Ì—Íƒo[Šî–{ˆ—.cpp
//date:2021/11/11  name:Kazuki Wada
//=================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "assetnames.h"
#include "input.h"
#include "Texture.h"
#include "Sprite.h"
#include "EmptyHeart.h"

void EmtyHeart::Init()
{
	Texture::Init();
	Sprite::Init();
}

void EmtyHeart::UnInit()
{
	Texture::Uninit();
	Sprite::Uninit();
}

void EmtyHeart::Update()
{
}

void EmtyHeart::Draw()
{
	Sprite::Draw(Texture::GetNum(TX_EMPTY), 0.0f, 200.0f, 100.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
}
