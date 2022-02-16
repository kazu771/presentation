//==============================================================================================
//シーン基本処理.h[Scene.h]
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
	std::list<GameObject*> m_gameobject[3]; //STLリスト,GameObjectを継承して作っているためこの形を採用
	
public:
	Scene() {}         //コンストラクタ
	virtual ~Scene() {} //デストラクタ,仮想関数にしてあるから注意

	virtual void Init() = 0; //純粋仮想関数に変更

	//テンプレート関数
	template <typename T>
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		m_gameobject[Layer].push_back(gameObject);//任意のものをlayerに入れるため
		gameObject->Init(); //カメラがプレイヤーなどの座標がほしい時Initの前にpushしておかないとエラーになる
		return gameObject;
	}

	
	
	//一個の型を取得
	template <typename T>
	T* GetGameObject(int Layer)
	{
		for (GameObject* object : m_gameobject[Layer])
		{
			if (typeid(*object) == typeid(T)) //型を調べる(RTTI = 動的型情報)
			{
				return (T*)object;
			}
		}
		return NULL;
	}

	//複数オブジェクトの型を取得
	template <typename T>
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*>objects; //STL構造
		for (GameObject* object : m_gameobject[Layer])
		{
			if (typeid(*object) == typeid(T)) //型を調べる
			{
				objects.push_back((T*)object);
			}
		}
		return objects;
	}

	//終了
	virtual	void UnInit()
	{
		for (int i = 0; i < 3; i++)
		{
			//意味:m_gameobjectの中にあるものをひとつづつ呼び出して行ってくれる
		//このforループでは、リストの中身のものをデリートとしているだけ
			for (GameObject* object : m_gameobject[i])
			{
				object->UnInit();
				delete object;
			}
			//リストの中をきれいにするため
			m_gameobject[i].clear(); //リスト全消去
		}
		
	}

	//更新
	virtual	void Update()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_gameobject[i])
			{
				object->Update();
			}

			//ラムダ式
			//消す予約がtrueのとき、リストからも消す設定
			m_gameobject[i].remove_if([](GameObject* object) {return object->Destroy(); });
		}
	}

	//描画
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