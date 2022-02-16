//==============================================================================================
//�V�[����{����.h[Scene.h]
//date:2021/06/01   namr:Kazuki Wada
//==============================================================================================
#ifndef SCENE_H_
#define SCENE_H_


#include <list>
#include <vector>
#include <typeinfo>
#include "GameObject.h"
#include "State.h"


class Scene
{

protected:
	std::list<GameObject*> m_gameobject[3]; //STL���X�g,GameObject���p�����č���Ă��邽�߂��̌`���̗p
	
public:
	Scene() {}         //�R���X�g���N�^
	virtual ~Scene() {} //�f�X�g���N�^,���z�֐��ɂ��Ă��邩�璍��

	virtual void Init() = 0; //�������z�֐��ɕύX

	//�e���v���[�g�֐�
	template <typename T>
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		m_gameobject[Layer].push_back(gameObject);//�C�ӂ̂��̂�layer�ɓ���邽��
		gameObject->Init(); //�J�������v���C���[�Ȃǂ̍��W���ق�����Init�̑O��push���Ă����Ȃ��ƃG���[�ɂȂ�
		return gameObject;
	}

	
	
	//��̌^���擾
	template <typename T>
	T* GetGameObject(int Layer)
	{
		for (GameObject* object : m_gameobject[Layer])
		{
			if (typeid(*object) == typeid(T)) //�^�𒲂ׂ�(RTTI = ���I�^���)
			{
				return (T*)object;
			}
		}
		return NULL;
	}

	//�����I�u�W�F�N�g�̌^���擾
	template <typename T>
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*>objects; //STL�\��
		for (GameObject* object : m_gameobject[Layer])
		{
			if (typeid(*object) == typeid(T)) //�^�𒲂ׂ�
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}

	//�I��
	virtual	void UnInit()
	{
		for (int i = 0; i < 3; i++)
		{
			//�Ӗ�:m_gameobject�̒��ɂ�����̂��ЂƂÂĂяo���čs���Ă����
		//����for���[�v�ł́A���X�g�̒��g�̂��̂��f���[�g�Ƃ��Ă��邾��
			for (GameObject* object : m_gameobject[i])
			{
				object->UnInit();
				delete object;
			}
			//���X�g�̒������ꂢ�ɂ��邽��
			m_gameobject[i].clear(); //���X�g�S����
		}
		
	}

	//�X�V
	virtual	void Update()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_gameobject[i])
			{
				object->Update();
			}

			//�����_��
			//�����\��true�̂Ƃ��A���X�g����������ݒ�
			m_gameobject[i].remove_if([](GameObject* object) {return object->Destroy(); });
		}
	}

	//�`��
	virtual	void Draw()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_gameobject[i])
			{
				object->Draw();
			}
		}
	}


};

#endif // !SCENE_H_