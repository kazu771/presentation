//======================================================================
//�v���C���[��{����.h[player.h]
//date:2021/05/17     name:Kazuki Wada
//======================================================================

#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject.h"

class Player : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	void ChangePoison();		  //�v���C���[�̏�Ԃ�ύX����悤
	void ChangeConfusion();		  //�v���C���[�̍�����Ԃ�ύX����悤
	void CollisionEnemyBullet();  //�G�ƃv���C���[�̓����蔻��
	void CollisuinPoisonBullet(); //�ł̒e�Ƃ̓����蔻��
	void ColllisionEnemy();       //�v���C���[�ƓG�̓����蔻��
	int GetHp() { return m_Hps; } //�̗͂𑗂�悤
	bool Change;
	bool GetPoison() { return m_isPoison; }      //�łɂ������Ă邩�ǂ����̔���𑗂�֐�
	bool GetChange() { return Change; }          //scene��؂�ւ���悤
	bool GetConfusion() { return m_isConfusion; }//�����ϐ��𑗂�悤
	bool GetHpItem() { return m_isHpItem; }		 //HP�t���O����悤
	bool GetCharge() { return m_isCharge; }		 //�`���[�W�t���O�𑗂�p
	enum ArrowMode
	{
		ARROWMODE_NORMAL = 0,
		ARROWMODE_DOUBLE,
		ARROWMODE_TWOWAY,
		ARROWMODE_MAX
	};
	void ArrowModeChange();//�t���O��ύX����悤
	
	ArrowMode m_Mode;//��̏��
private:
	class AnimetionModel* m_Model;		 //���f����ǂݍ��ނ��ߗp
	class Shadow*         m_Shadow;		 //�e��ǂݍ��ނ悤
	class Speed*          m_Speed;       //�X�s�[�h�A�C�e���p
	class Camera*         m_Camera;      //�J�����p
	class BoxCollision*   m_collisions;
	class Audio*          m_shotse;		 //���������̉�
	class Key*            m_Key;
	ID3D11VertexShader*   m_VertexShader = NULL;
	ID3D11PixelShader*    m_PixelShader  = NULL;
	ID3D11InputLayout*    m_VertexLayout = NULL;
	D3DXVECTOR3           m_site;
	D3DXVECTOR3			  m_GTraget;	 //�e�̕������󂯎��
	D3DXVECTOR3           m_Forward;
	float                 m_speed;		 //�X�s�[�h
	bool                  m_isConfusion; //�������Ă��邩�ǂ���
	bool                  m_isEmote;	 //�G���[�g�t���O,false:�������[�h,true:�G���[�g
	bool                  m_isPoison;	 //�ł̏�ԂɕύX
	bool				  m_isHpItem;    //�A�C�e�����擾�������ǂ���
	bool				  m_IsSp;        //�X�s�[�h�A�C�e���擾�������ǂ���
	bool				  m_isCharge;    //�`���[�W���Ă邩�ǂ���
	bool				  m_isKey;	     //���擾�t���O
	bool				  m_isCheck;  	 //�J�M���g�p�������ǂ���
	bool				  m_isDeath;	 //���S�t���O
	int				      m_PoisonCnt;   //�ŗp�J�E���g
	int					  m_Frame;       //�A�j���[�V�����Đ��p
	int					  m_Hps;         //�̗�
	int				      m_Cnt;	     //�����J�E���g�p
	int					  m_HItemCnt;    //�̗̓A�C�e���J�E���g�p
	int				      m_EmCnt;	     //�G���[�g�p�J�E���g
	void CollisionSpeed();				 //�X�s�[�h�A�C�e���Ƃ̂��蔻��
	void GetItem();						 //�v���C���[�ƒe�̓����蔻��
	void Behavior();					 //�v���C���[�̑�����܂Ƃ߂�֐�
	void PoisonDamge(float Dameg);
	void Confusion(int Cnt);			 //�����p�֐�
	void CollisionConfuse();
	void CollisionHpItem();			     //�񕜃A�C�e���Ƃ̓����蔻��
	void CollisionDoor();				 //���Ƃ̓����蔻��
	void HpItemProcess();				 //�񕜂��鏈��
	void CollisionStateBullet();
	bool SetPosion();					 //��Ԃ𑗂遨�ŏ�ԂɂȂ�����e�N�X�`���[�A�j���[�V������\�����邽��
};

#endif // !PLAYER_H_