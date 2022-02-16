//====================================================================================================================
//鍵のエフェクト基本処理.cpp[KeyEffect.cpp]
//date:2021/06/21   name:Kazuki Wada
//====================================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#include "assetnames.h"
#include "input.h"
#include "Texture.h"
#include "Sprite.h"
#include "KeyEffect.h"
#include "Camera.h"

void KeyEffect::Init()
{
	VERTEX_3D vertex[4];
	//爆発ポリゴン
	//座標はZ字になるように配置
	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);      //左上
	vertex[0].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //法線
	vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //頂点の色,前からRGBA
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);             //テクスチャーのはる位置

	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);       //右上
	vertex[1].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //法線
	vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //テクスチャーの色
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);			  //テクスチャーのはる位置

	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);     //左下
	vertex[2].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //法線
	vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //テクスチャーの色
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);			  //テクスチャーのはる位置

	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);      //右下
	vertex[3].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //法線
	vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //テクスチャーの色
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);             //テクスチャーのはる位置

	//頂点バッファーの生成
	D3D11_BUFFER_DESC bd{};
	//ZeroMemory();
	bd.Usage = D3D11_USAGE_DYNAMIC;
	//頂点バッファーのサイズ
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;  //バッファーのサイズも増やさないと三角形が書けない4だと一つ、8だと二つ
	//頂点バッファーということを示すため用
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//最初に入れておく頂点バッファーを保存するやつ
	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャーの読み込み
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetDevice(),
		"asset/texture/KeyEffects.png",
		NULL,
		NULL,
		&m_Texture,
		NULL
	);
	//例外処理用
	assert(m_Texture);

	//爆発は煙みたいなものなのでunlitTextureのほうを使う
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Count = 0;
}

void KeyEffect::UnInit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void KeyEffect::Update()
{
	m_Count++;
	if (m_Count >= 16)
	{
		SetDestroy();
		return;
	}
}

void KeyEffect::Draw()
{
	//テクスチャー座標算出
	float x = m_Count % 5 * (1.0f / 8);
	float y = m_Count / 4 * (1.0f / 4);

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);      //左上
	vertex[0].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //法線
	vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //頂点の色,前からRGBA
	vertex[0].TexCoord = D3DXVECTOR2(x, y);                   //テクスチャーのはる位置

	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);       //右上
	vertex[1].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //法線
	vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //テクスチャーの色
	vertex[1].TexCoord = D3DXVECTOR2(x + 0.25f, y);			  //テクスチャーのはる位置

	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);     //左下
	vertex[2].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //法線
	vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //テクスチャーの色
	vertex[2].TexCoord = D3DXVECTOR2(x, y + 0.25f);			  //テクスチャーのはる位置

	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);      //右下
	vertex[3].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       //法線
	vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //テクスチャーの色
	vertex[3].TexCoord = D3DXVECTOR2(x + 0.25f, y + 0.25f);   //テクスチャーのはる位置7

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(0);
	D3DXMATRIX view = camera->GetViewMatrix();


	//ビューの逆行列
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);
	//41,42,43は移動成分が入っているところでそこを消してあげる=移動成分がなくなる、カメラに張り付かず指定した場所で描画ができる
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;


	//マトリクスの設定
	D3DXMATRIX wold, scale, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);

	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	wold = scale * invView * trans;
	Renderer::SetWorldMatrix(&wold);


	//頂点バッファーの設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//マテリアルの設定
	MATERIAL material;
	//マテリアルの全部を初期化
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	//テクスチャーの設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブトポロジ設定
	//頂点をどうやって結ぶのか
	//三角形の書き方
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	//第一引数:頂点数
	//頂点数をいじることで三角形の数を変えられる
	//第二引数:何番目の頂点から始めるか
	Renderer::GetDeviceContext()->Draw(4, 0);
}
