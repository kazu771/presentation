//======================================================================================================================
//リロードUI基本処理.cpp
//date:2021/11/17  name:Kazuki Wada
//=======================================================================================================================
#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "Reload.h"

void Reload::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(480.0f, 0.0f, 0.0f);//左上
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //法線
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f); //頂点の色,前からRGBA
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);//テクスチャーのはる位置

	vertex[1].Position = D3DXVECTOR3(780.0f, 0.0f, 0.0f);//右上
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //法線
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //テクスチャーの色
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);//テクスチャーのはる位置

	vertex[2].Position = D3DXVECTOR3(0.0f, 480.0f, 0.0f);//左下
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //法線
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //テクスチャーの色
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);//テクスチャーのはる位置

	vertex[3].Position = D3DXVECTOR3(780.0f, 480.0f, 0.0f);//右下
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //法線
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //テクスチャーの色
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);//テクスチャーのはる位置


	//頂点バッファーの生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	//頂点バッファーのサイズ
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	//頂点バッファーということを示すため用
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	//最初に入れておく頂点バッファーを保存するやつ
	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャーの読み込み
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetDevice(),
		"asset/texture/Reload.png",
		NULL,
		NULL,
		&m_Texture,
		NULL
	);

	//例外処理用
	assert(m_Texture);

	//2Dポリゴン用シェーダー
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");
}


//終了
void Reload::UnInit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

//更新
void Reload::Update()
{

}

//描画
void Reload::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクスの設定
	Renderer::SetWorldViewProjection2D();

	//頂点バッファーの設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//テクスチャーの設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブトポロジ設定
	//頂点をどうやって結ぶのか
	//三角形の書き方
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	if (m_IsUse == false)
	{
		//ポリゴン描画
		//第一引数:頂点数
		//頂点数をいじることで三角形の数を変えられる
		//第二引数:何番目の頂点から始めるか
		Renderer::GetDeviceContext()->Draw(4, 0);

	}
}

//表示の切り替え
void Reload::Change()
{
	if (m_IsUse == true)
	{
		m_IsUse =	false;
	}
	else if(m_IsUse == false)
	{
		m_IsUse = true;
	}
}