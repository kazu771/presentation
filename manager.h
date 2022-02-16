//
//�Q�[�����Ǘ�����.h
//
//

#include "Scene.h"


//
//�Q�[�����Ǘ�����N���X
//
class Manager
{
private:
	//class�Ƃ��邱�Ƃɂ��Scene.h���C���N���[�h���Ȃ��Ă��悭�Ȃ�B�������A�|�C���^�ϐ��̂�
	static class Scene* m_scene; //��{�֐�(����4��static�̂��߂�������static�ɂ���)

public:
	static void Init();   //������
	static void Uninit(); //�I��
	static void Update(); //�X�V
	static void Draw();   //�`��

	static class Scene* GetScene() { return m_scene; }

	//�e���v���[�g�֐�
	template <typename T>
	static void Setscene()
	{
		if (m_scene)
		{
			m_scene->UnInit();
			delete m_scene;
		}
		m_scene = new T();
		m_scene->Init();
	}
};