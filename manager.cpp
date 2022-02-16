//==========================================================================================
//�Q�[�����Ǘ�����.cpp
//date:2021/05/18     name:Kazuki Wada
//==========================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "audio.h"
#include "Game.h"
#include "Title.h"
#include "Menu.h"
#include "Result.h"
#include "Explaine.h"
#include "Clear.h"
#include "GameOver.h"
#include "Rule.h"
//------------------------------
//�O���[�o���ϐ�
//------------------------------
Scene* Manager::m_scene = NULL;

//������
void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	Audio::InitMaster();

	Setscene <Title>(); //scene�̐ݒ�
}

//�I��
void Manager::Uninit()
{
	m_scene->UnInit();
	delete m_scene;

	Audio::UnInitMaster();
	Input::Uninit();
	Renderer::Uninit();
}

//�X�V
void Manager::Update()
{
	Input::Update();
	m_scene->Update();
}

//�`��
void Manager::Draw()
{
	Renderer::Begin();
	m_scene->Draw();
	Renderer::End();
}


