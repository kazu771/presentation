//
//ゲームを管理する.h
//
//

#include "Scene.h"


//
//ゲームを管理するクラス
//
class Manager
{
private:
	//classとつけることによりScene.hをインクルードしなくてもよくなる。ただし、ポインタ変数のみ
	static class Scene* m_scene; //基本関数(下の4個がstaticのためこっちもstaticにする)

public:
	static void Init();   //初期化
	static void Uninit(); //終了
	static void Update(); //更新
	static void Draw();   //描画

	static class Scene* GetScene() { return m_scene; }

	//テンプレート関数
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