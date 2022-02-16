#pragma once
//============================================
//共通機能.h[GameObject.h]
//date:2021/05/24    name;Kazuki Wada
//============================================

//----------------
//クラス定義
//----------------
class GameObject
{
protected:

	D3DXVECTOR3 m_Position; //座標
	D3DXVECTOR3 m_Rotation; //回転
	D3DXVECTOR3 m_Scale;    //大きさ
	bool m_Destroy = false; //消すよう,trueになると消去
	int m_HP;               //体力
	float move;
	//シェーダー関係も同じなのでまとめてもいい


public:

	GameObject() {}          //コンストラクタ
	virtual ~GameObject() {} //デストラクタ,仮想関数にしてあるから注意
	virtual void Init() = 0;  //純粋仮想関数
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
		MODE_RIGHT, //右側のドア
		MODE_LEFT,  //左側のドア
		MODE_MAX,
	}MODE;
	MODE m_mode;              //種類を変えるよう
	Mode m_modeb;
	//ゲッター
	D3DXVECTOR3 GetPosition() { return m_Position;}
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	D3DXVECTOR3 GetScale() { return m_Scale; }
	Mode GetNMode() { return m_mode; }
	Mode GetModes() { return m_modeb; }
	//前方向ベクトルの取得
	//31.32.33は前方向(Z方向)を表すベクトル
	//21.22.23はy方向ベクトル
	//11.12.13はx方向ベクトル
	//41,42,43は位置
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

	//ビヘイビアツリー、経路探索,AIに使えるもの
	//外部から敵の位置を変えられる(セッター)
	void SetPosition(D3DXVECTOR3 Potision) { m_Position = Potision; }
	//モデルを変えたいときよう(タイプごとに変えられる)
	void SetPosMode(D3DXVECTOR3 pos, MODE modes) { m_Position = pos, m_mode = modes; }
	void SetPosModes(D3DXVECTOR3 pos, Mode modeb) { m_Position = pos, m_modeb = modeb; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }
	void SetScale(D3DXVECTOR3 Scale) { m_Scale = Scale; }
	void SetDestroy() { m_Destroy = true; } //オブジェクト
	void SetType() {}
	//X軸方向の軸を求める
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

		return vx * 0.5f;//0.5fはオブジェクトの大きさの半分を入れるところ、各自でかえる
		
	}



	//Y軸方向の軸を求める
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

		return vy * 0.5f;//0.5fはオブジェクトの大きさの半分を入れるところ、各自でかえる

	}


	//Z軸方向の軸を求める
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

		return vz * 0.5f;//0.5fはオブジェクトの大きさの半分を入れるところ、各自でかえる

	}

	//HPを減らす処理
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