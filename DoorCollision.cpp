//===================================================================================================================
//ドア用コリジョン基本処理.h[DoorCollision.h]
//date:2022/01/11     name:Kauzki Wada
//===================================================================================================================
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Scene.h"
#include "Enemy.h"
#include "DoorCollision.h"
#include "Door.h"

//頂点データ
//座標, 法線, 色, テクスチャー座標
//図形を種面から見たときに左→右、下→上の順になるように配置
DoorCollision::VERTEX3D g_vertexList[]
{
	
//正面ad
{{ 0.0f, 0.0f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, //0
{{ 7.5f, 0.0f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, //1
{{ 0.0f, 7.0f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, //2
{{ 7.5f, 7.0f,  -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, //3


//右面
{{ 7.5f, 0.0f,   0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, //4
{{ 7.5f, 7.0f,   0.5f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, //5


//後ろ面
{{ 0.0f, 0.0f,   0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, //6
{{ 0.0f, 7.0f,   0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, //7

//左面は今までの頂点データを使えばいいので省略

};

//インデックスデータ
WORD g_DoorIndexList[]
{

	//------
	//正面
	//------
	 0, 1, //下
	 2, 3, //上
	 0, 2, //左
	 1, 3, //右

	//-----
	//右
	//-----
	 1, 4, //下
	 3, 5, //上
	 1, 3, //左
	 4, 5, //右

	//-----
	//後ろ
	//-----
	 6, 4, //下
	7, 5, //上
	 6, 7, //左
	 4, 5, //右

	 //-----
	 //左
	 //-----
	 6, 0, //下
	 7, 2, //上
	 6, 7, //左
	 0, 2, //右
};

void DoorCollision::Init()
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
	bd.ByteWidth = sizeof(VERTEX3D) * 8;
	//頂点バッファーということを示すため用
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	//最初に入れておく頂点バッファーを保存するやつ
	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = g_vertexList;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//インデックスバッファーの生成
	D3D11_BUFFER_DESC ibDesc{};
	ibDesc.Usage = D3D11_USAGE_DEFAULT;
	ibDesc.ByteWidth = sizeof(WORD) * 32;
	//インデックスバッファーということを証明
	ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA irDate{};
	irDate.pSysMem = g_DoorIndexList;

	Renderer::GetDevice()->CreateBuffer(&ibDesc, &irDate, &m_IndexBuffer);

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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

void DoorCollision::UnInit()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_IndexShader->Release();
	m_IndexPixcelShader->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void DoorCollision::Update()
{
	
}

void DoorCollision::Draw()
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
	Renderer::GetDeviceContext()->DrawIndexed(32, 0, 0);
}
