//=========================================================================================================
//������̒e��{����(�E).h[TwoWayBulletRight.h]
//date:2021/11/30     name:Kazuki Wada
//=========================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "GameObject.h"
#include "model.h"
#include "TwoWayBulletRight.h"
#include "player.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Spider.h"

//----------------
//�ϐ���`
//----------------
Model* TwowayRIght::m_Model;//�X�^�e�B�b�N�ϐ�������cpp���ł��錾���K�v



void TwowayRIght::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\Arrows.obj");
}

void TwowayRIght::UnLoad()
{
	m_Model->Unload();
	delete m_Model;
}

void TwowayRIght::Init()
{
	m_Position = D3DXVECTOR3(3.0f, 1.0f, 2.0f);
	m_Rotation = D3DXVECTOR3(90.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	//�v���C���[�̏����󂯎��
	Player* player = Manager::GetScene()->GetGameObject<Player>(1);
	m_Direction = player->GetForward();

}

void TwowayRIght::UnInit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void TwowayRIght::Update()
{
	m_Position.x -= (m_Direction.x - 1.0f) * 0.5f;
	m_Position.y  = m_Direction.y * 0.5f;
	m_Position.z -= m_Direction.z * 0.5f;
	//�G�Ƃ̓����蔻��
	{
		Scene* scene = Manager::GetScene();
		//�ʏ�̓G�Ƃ̓����蔻��
		{
			std::vector<Enemy*> enemyList = scene->GetGameObjects<Enemy>(1); //�G���������邽��gameobjects
			for (Enemy* enemy : enemyList)
			{
				D3DXVECTOR3 enemyPosition = enemy->GetPosition();   //�G�̍��W���󂯎��
				D3DXVECTOR3 direction = m_Position - enemyPosition;

				D3DXVECTOR3 obbx, obbz;
				float obblenX, obblenZ;

				obbx = enemy->GetObbX();
				obblenX = D3DXVec3Length(&obbx);//�x�N�g���̒��������߂Ă���
				obbx /= obblenX;//�����������̒������P�ɂ��Ă���

				obbz = enemy->GetObbZ();
				obblenZ = D3DXVec3Length(&obbz);
				obbz /= obblenZ;

				float lenX, lenZ;
				lenX = D3DXVec3Dot(&obbx, &direction);//����
				lenZ = D3DXVec3Dot(&obbz, &direction);

				//fabs�Ő�Βl�����߂Ă���
				if (fabs(lenX) < obblenX && fabs(lenZ) < obblenZ)
				{
					//�����G�t�F�N�g�̐���
					//scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);
					scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);
					//enemy->SetDestroy(); //�G�̔j��
					SetDestroy();        //�e�̔j��

					return;
				}

			}

		}
		//�ʒu���W�Ƀv���C���[�̌���������A�Ō�̊|���Z�ŃX�s�[�h�𒲐�
		m_Position -= m_Direction * 0.5;
		//�t�B�[���h�O�ɏo��������\��
		if (m_Position.z > 100.0f || m_Position.z < -80.0f || m_Position.x > 70.0f || m_Position.x < -70.0f)
		{
			//�����G�t�F�N�g�̐���
			scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);
			//	m_Spider.DecreaseHp();
			SetDestroy();

			return;
		}
	}

}

void TwowayRIght::Draw()
{//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�}�g���N�X�̐ݒ�
	D3DXMATRIX wold, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//�O����y, x, z�̏��Őݒ肵�Ă���
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	wold = scale * rot * trans;

	Renderer::SetWorldMatrix(&wold);

	//�`�悷�邾��
	m_Model->Draw();
}
