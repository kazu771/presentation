#pragma once
//============================================
//���ʋ@�\.h[GameObject.h]
//date:2021/05/24    name;Kazuki Wada
//============================================

//----------------
//�N���X��`
//----------------
class GameObject
{
protected:

	D3DXVECTOR3 m_Position; //���W
	D3DXVECTOR3 m_Rotation; //��]
	D3DXVECTOR3 m_Scale;    //�傫��
	bool m_Destroy = false; //�����悤,true�ɂȂ�Ə���
	int m_HP;               //�̗�
	float move;
	//�V�F�[�_�[�֌W�������Ȃ̂ł܂Ƃ߂Ă�����


public:

	GameObject() {}          //�R���X�g���N�^
	virtual ~GameObject() {} //�f�X�g���N�^,���z�֐��ɂ��Ă��邩�璍��
	virtual void Init() = 0;  //�������z�֐�
	virtual void UnInit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	typedef enum Mode
	{
		MODE_NORMAL,
		MODE_ATTACK,
		MODE_ESCAPE,
		MODE_GUN_NORMAL,
		MODE_SPEED,
		MODE_RIGHT, //�E���̃h�A
		MODE_LEFT,  //�����̃h�A
		MODE_MAX,
	}MODE;
	MODE m_mode;              //��ނ�ς���悤
	Mode m_modeb;
	//�Q�b�^�[
	D3DXVECTOR3 GetPosition() { return m_Position;}
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	D3DXVECTOR3 GetScale() { return m_Scale; }
	Mode GetNMode() { return m_mode; }
	Mode GetModes() { return m_modeb; }
	//�O�����x�N�g���̎擾
	//31.32.33�͑O����(Z����)��\���x�N�g��
	//21.22.23��y�����x�N�g��
	//11.12.13��x�����x�N�g��
	//41,42,43�͈ʒu
	D3DXVECTOR3 GetForward()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;
		return forward;
	}

	//�r�w�C�r�A�c���[�A�o�H�T��,AI�Ɏg�������
	//�O������G�̈ʒu��ς�����(�Z�b�^�[)
	void SetPosition(D3DXVECTOR3 Potision) { m_Position = Potision; }
	//���f����ς������Ƃ��悤(�^�C�v���Ƃɕς�����)
	void SetPosMode(D3DXVECTOR3 pos, MODE modes) { m_Position = pos, m_mode = modes; }
	void SetPosModes(D3DXVECTOR3 pos, Mode modeb) { m_Position = pos, m_modeb = modeb; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetScale(D3DXVECTOR3 Scale) { m_Scale = Scale; }
	void SetDestroy() { m_Destroy = true; } //�I�u�W�F�N�g
	void SetType() {}
	//X�������̎������߂�
	D3DXVECTOR3 GetObbX()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);


		world = rot;

		D3DXVECTOR3 vx;
		vx.x = world._11;
		vx.y = world._12;
		vx.z = world._13;

		return vx * 0.5f;//0.5f�̓I�u�W�F�N�g�̑傫���̔���������Ƃ���A�e���ł�����
		
	}



	//Y�������̎������߂�
	D3DXVECTOR3 GetObbY()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);


		world = scale * rot;

		D3DXVECTOR3 vy;
		vy.x = world._21;
		vy.y = world._22;
		vy.z = world._23;

		return vy * 0.5f;//0.5f�̓I�u�W�F�N�g�̑傫���̔���������Ƃ���A�e���ł�����

	}


	//Z�������̎������߂�
	D3DXVECTOR3 GetObbZ()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);


		world = rot;

		D3DXVECTOR3 vz;
		vz.x = world._31;
		vz.y = world._32;
		vz.z = world._33;

		return vz * 0.5f;//0.5f�̓I�u�W�F�N�g�̑傫���̔���������Ƃ���A�e���ł�����

	}

	//HP�����炷����
	void DecreaseHp()
	{
		m_HP -= 1;
	}

	bool Destroy()
	{
		if (m_Destroy)
		{
			UnInit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}
	
};