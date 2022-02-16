//==========================================================
//�J������{����.cpp[Camera.cpp]
//date;2021/05/10   name;Kazuki Wada
//==========================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "Camera.h"
#include "input.h"
#include "player.h"

void Camera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 5.0f, -7.0f); //�J�����̈ʒu
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    //�����_�̈ʒu
	m_IsDebug = false;
}

void Camera::UnInit()
{

}

void Camera::Update()
{
	//�f�o�b�N���[�h�̑���
	{
		if (m_IsDebug == false)
		{
			//�f�o�b�N���[�h�ɕύX
			if (Input::GetKeyTrigger('I'))
			{
				m_IsDebug = true;
			}
		}
		else
		{
			//�f�o�b�N���[�h����
			if (Input::GetKeyTrigger('I'))
			{
				m_IsDebug = false;
			}
		}

		if (m_IsDebug)
		{
			if (Input::GetKeyTrigger('L'))
			{
				m_Position.x += 1.0f;
			}

			else if (Input::GetKeyTrigger('J'))
			{
				m_Position.x -= 1.0f;
			}
			else if (Input::GetKeyTrigger('I'))
			{
				m_Position.z -= 1.0f;
			}
			else if (Input::GetKeyTrigger('K'))
			{
				m_Position.z -= 1.0f;
			}

		}
	}

	//�g�b�v�r���[
	Player* player = Manager::GetScene()->GetGameObject<Player>(1);
	
	D3DXVECTOR3 forward = player->GetForward();
	m_Target = player->GetPosition();
	//forward.x += 1.0f;
	//�T�[�h�p�[�\��
	if (m_IsDebug == true)
	{
		//���̕����̃x�N�g�����~��������-�����Ă�����A����Ɍ��ɂ��邽�߂�*5.0
		m_Position = m_Target - (-forward) * 5.0f + D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	}
	
	else if (m_IsDebug == false)
	{
		//�����_�Ɏ����Őݒ肵�����J�����̈ʒu�𑫂��Ă�����
		m_Position = m_Target + D3DXVECTOR3(0.0f, 5.0f, -8.0f);
	}
}

void Camera::Draw()
{
	//�r���[�}�g���N�X�̐ݒ�,�J�����̈ʒu�Ȃ�
	
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	Renderer::SetViewMatrix(&m_ViewMatrix);

	//�v���W�F�N�V�����}�g���N�X,���e�ݒ�,��p�̐ݒ�A��A�[�Ȃǂ̂����Ă����s��
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);
}

bool Camera::CheckView(D3DXVECTOR3 Position)
{
	D3DXMATRIX vp, invvp;

	vp = m_ViewMatrix * m_ProjectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);//�t�s������߂Ă���

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];
	//�J�������猩���Ƃ��̉��̂S���_
	{
		vpos[0] = D3DXVECTOR3( -1.0f,  1.0f, 1.0f);//����, �Ƃ肠�����ۑ�p��0�ɂ��Ă�{����-1.0
		vpos[1] = D3DXVECTOR3(  1.0f,  1.0f, 1.0f);//�E��
		vpos[2] = D3DXVECTOR3( -1.0f, -1.0f, 1.0f);//����
		vpos[3] = D3DXVECTOR3(  1.0f, -1.0f, 1.0f);//�E��
	}

	//���W�ϊ�
	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);

	D3DXVECTOR3 v, v1, v2,v3, v4, n, o;

	v = Position - m_Position;//�΂߂̐����Z�o
	v1 = wpos[0] - m_Position;
	v2 = wpos[2] - m_Position;
	v3 = wpos[1] - m_Position;
	v4 = wpos[3] - m_Position;

	D3DXVec3Cross(&n, &v1, &v2);//�����̊O�ς����߂�,v1��v2�ɐ����ȍ����ʂ̖@���x�N�g��
	D3DXVec3Cross(&o, &v3, &v4);//�E���̊O��
	
	//�����������̒��ɂ��邩�ǂ����̔���,D3DXVec3Dot�œ��ς��Z�o
	if (D3DXVec3Dot(&n, &v) < 0.0f)
	{
		//���Ȃ����false�ɂ���
		return false;
	}

	
	return true;
}

