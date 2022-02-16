//======================================================================================
//プレイヤー用箱型コリジョン基本処理.cpp[BoxCollision.cpp]
//date:2021/08/18  name:Kazuki Wada
//======================================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Scene.h"
#include "BoxCollision.h"
#include "Enemy.h"
#include "input.h"
#include "player.h"

//頂点データ
//座標, 法線, 色, テクスチャー座標
BoxCollision::VERTEX3D g_VertexList[]
{
	//一番右
	//前面
	{{ 0.0f, 3.0f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, //0,左上
	{{ 2.0f, 3.0f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, //1,右上
	{{ 0.0f, 0.0f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, //2,左下
	{{ 2.0f, 0.0f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, //3,右下

	//右面
	{{ 2.0f, 3.0f,   1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, //4
	{{ 2.0f, 0.0f,   1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, //5

	//後ろ面
	{{ 0.0f, 3.0f,   1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, //6
	{{ 0.0f, 0.0f,   1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, //7

	//左面
	//同じ座標を用いるため省略
};


//インデックスデータ
WORD g_IndexList[]
{

	//------
	//正面
	//------
	 0, 1, //上
	 2, 3, //下
	 2, 0, //左
	 3, 1, //右

	//-----
	//右
	//-----
	 1, 4, //下
	 3, 5, //上
	 3, 1, //右
	 5, 4, //左

	//-----
	//後ろ
	//-----
	 6, 4, //下
	 7, 5, //上
	 7, 6, //左
	 5, 4, //右

	 //-----
	 //左
	 //-----
	 0, 6, //下
	 2, 7, //上
	 7, 6, //左
	 2, 0, //右
};

//初期化
void BoxCollision::Init()
{
	m_IsVisible = false;
	m_TargetPos = { 0.0f, 0.0f, 0.0f };
	m_TargetRot = { 0.0f, 0.0f, 0.0f };
	m_Direction = { 0.0f, 0.0f, 0.0f };
	m_Angle = 0.0f;
	//頂点バッファーの生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	//頂点バッファーのサイズ(頂点数)
	bd.ByteWidth = sizeof(VERTEX3D) * 16;
	//頂点バッファーということを示すため用
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	//最初に入れておく頂点バッファーを保存するやつ
	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = g_VertexList;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//インデックスバッファーの生成
	D3D11_BUFFER_DESC ibDesc{};
	ibDesc.Usage = D3D11_USAGE_DEFAULT;
	ibDesc.ByteWidth = sizeof(WORD) * 28;
	//インデックスバッファーということを証明
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA irDate{};
	irDate.pSysMem = g_IndexList;

	Renderer::GetDevice()->CreateBuffer(&ibDesc, &irDate, &m_IndexBuffer);

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	//テクスチャーの読み込み
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetDevice(),
		"asset/model/Treasure.png",
		NULL,
		NULL,
		&m_Texture,
		NULL
	);
	//例外処理用
	assert(m_Texture);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	Renderer::CreateVertexShader(&m_IndexShader, &m_VertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_IndexPixcelShader, "vertexLightingPS.cso");
}
//終了
void BoxCollision::UnInit()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_IndexShader->Release();
	m_IndexPixcelShader->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//更新
void BoxCollision::Update()
{
	Scene* scene = Manager::GetScene();
	//プレイヤーの情報を受け取る
	std::vector<Player*> PlayerList = scene->GetGameObjects<Player>(1);
	for (Player* player : PlayerList)
	{
		D3DXVECTOR3 l_PlayerPosition = player->GetPosition();
		D3DXVECTOR3 l_PlayerRotation = player->GetRotation();
		//m_Position.x = enemyPosition.x - 0.8f;
		m_Position.x = l_PlayerPosition.x;
		m_Position.y = l_PlayerPosition.y;
		m_Position.z = l_PlayerPosition.z;
		Player* p_player = Manager::GetScene()->GetGameObject<Player>(1);
		m_TargetPos = l_PlayerPosition;

		//敵とプレイヤーの距離の差分を算出
		m_Direction.x = m_TargetPos.x - m_Position.x;
		m_Direction.z = m_TargetPos.z - m_Position.z;

		//正規化
		D3DXVec3Normalize(&m_Direction, &m_Direction);

		m_Angle = atan2(fabsf(m_TargetPos.z - m_Position.z), fabsf(m_TargetPos.x - m_Position.x));

		//角度の更新
		m_Rotation.x = l_PlayerRotation.x;
		m_Rotation.y = l_PlayerRotation.y + 1.6f;
		m_Rotation.z = l_PlayerRotation.z;
	}
}

//描画
void BoxCollision::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//頂点バッファーの設定
	UINT stride = sizeof(VERTEX3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	//マトリクスの設定
	D3DXMATRIX wold, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);

	//前からy, x, zの順で設定していく
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	wold = scale * rot * trans;
	Renderer::SetWorldMatrix(&wold);

	//プリミティブトポロジ設定
	//頂点をどうやって結ぶのか
	//三角形の書き方
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	//ポリゴン描画
	Renderer::GetDeviceContext()->DrawIndexed(28, 0, 0);

}

