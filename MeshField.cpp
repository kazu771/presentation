//---------------------------
//3Dフィールド描画
//---------------------------
#include "main.h"
#include "renderer.h"
#include "MeshField.h"

float g_FieldHeight[21][21] =
{
	{ 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f},
	{  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  1.0f,  0.0f,  0.0f,  2.0f,  2.0f,  0.0f,  2.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  2.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  1.0f,  0.0f,  0.0f,  2.0f,  0.0f,  0.0f,  0.0f,  2.0f,  0.0f,  0.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  2.0f,  2.0f,  0.0f,  2.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  2.0f,  2.0f,  2.0f,  2.0f,  0.0f,  0.0f,  2.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  2.0f,  0.0f,  2.0f,  2.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  2.0f,  3.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  2.0f,  0.0f,  2.0f,  2.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  2.0f,  3.0f,  0.0f,  0.0f,  2.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  3.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
};								   																					   


//疑似判定
float MeshField::GetHeight(D3DXVECTOR3 Position)//プレイヤーと地形の位置を入手し判定に似たものを作る
{
	int x, z;

	//ブロック番号算出
	x = Position.x / 5.0f + 10.0f; //初期化時のポジション
	z = Position.z / -5.0f + 10.0f;

	D3DXVECTOR3 pos0, pos1, pos2, pos3;

	pos0 = m_Vertex[x][z].Position;
	pos1 = m_Vertex[x + 1][z].Position;
	pos2 = m_Vertex[x][z + 1].Position;
	pos3 = m_Vertex[x + 1][z + 1].Position;

	D3DXVECTOR3 v12, v1p, c;

	v12 = pos2 - pos1;
	v1p = Position - pos1;

	D3DXVec3Cross(&c, &v12, &v1p);

	float py;
	D3DXVECTOR3 n;

	if (c.y > 0.0f)
	{
		//左上ポリゴン
		D3DXVECTOR3 v10;
		v10 = pos0 - pos1;
		D3DXVec3Cross(&n, &v10, &v12);
	}
	else
	{
		//右下ポリゴン
		D3DXVECTOR3 v13;
		v13 = pos3 - pos1;
		D3DXVec3Cross(&n, &v12, &v13);
	}

	//高さ取得
	py = -((Position.x - pos1.x) * n.x + (Position.z - pos1.z) * n.z) / n.y + pos1.y;

	return py;
}
//初期化
void MeshField::Init()
{
	//頂点用 forループ
	for (int x = 0; x <= 20; x++)
	{
		for (int z = 0; z <= 20; z++)
		{
			m_Vertex[x][z].Position = D3DXVECTOR3((x - 10) * 5.0f, g_FieldHeight[z][x], (z - 10) * -5.0f);
			m_Vertex[x][z].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //法線ベクトル
			m_Vertex[x][z].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //法線ベクトル
			m_Vertex[x][z].TexCoord = D3DXVECTOR2(x * 0.5f, z * 0.5f); //法線ベクトル
		}
	}

	//法線ベクトル算出
	for (int x = 1; x <= 19; x++)
	{
		for (int z = 1; z <= 19; z++)
		{
			D3DXVECTOR3 vx, vz, vn;

			vx = m_Vertex[x + 1][z].Position - m_Vertex[x - 1][z].Position; //右側へ向かうベクトルを求める
			vz = m_Vertex[x][z - 1].Position - m_Vertex[x][z + 1].Position; //奥側へ向かうベクトルを求める

			D3DXVec3Cross(&vn, &vz, &vx);//外積
			D3DXVec3Normalize(&vn, &vn); //正規化
			m_Vertex[x][z].Normal = vn;
		}
	}
	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{}; //バッファデスクリプション
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 21 * 21; //頂点バッファのサイズ
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; //頂点バッファを表すフラグ
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{}; //サブリソースデータ(頂点バッファに入れておく初期値の設定)
	sd.pSysMem = m_Vertex; //頂点データの先頭アドレス

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);//頂点バッファの作成


	//インデックスバッファ生成
	{
		unsigned int index[(22 * 2) * 20 - 2]; //1行21列＋縮退ポリゴンで22, 横も必要なので *2, 最後は縮退ポリゴンが必要ないので-2

		int i = 0;
		for (int x = 0; x < 20; x++)
		{
			for (int z = 0; z < 21; z++)
			{
				//ライン数
				index[i] = x * 21 + z;
				i++;

				//ブロック数
				index[i] = (x + 1) * 21 + z;
				i++;
			}

			if (x == 19) //最後は縮退ポリゴンが必要ないため
				break;

			//縮退ポリゴン用インデックス1
			index[i] = (x + 1) * 21 + 20;
			i++;

			//縮退ポリゴン用インデックス2
			index[i] = (x + 1) * 21;
			i++;
		}
		//頂点バッファ生成
		static D3D11_BUFFER_DESC bd; //バッファデスクリプション
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * ((22 * 2) * 20 - 2); //頂点バッファのサイズ
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER; //頂点バッファを表すフラグ
		bd.CPUAccessFlags = 0;

		static D3D11_SUBRESOURCE_DATA sd; //サブリソースデータ(頂点バッファに入れておく初期値の設定)
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index; //頂点データの先頭アドレス

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);//頂点バッファの作成

	}

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetDevice(),
		"asset/texture/fields.dds", //テクスチャアドレス
		NULL,
		NULL,
		&m_Texture,//テクスチャを受け取るポインタ
		NULL
	);

	assert(m_Texture);  //NULLの場合にエラーを出す

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso"); //cso(シェーダーが入っているコンパイル済みのシェーダー)を読み込み頂点シェーダーを作る

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");//csoを読み込んでピクセルシェーダを作る

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

}

//終了処理
void MeshField::UnInit()
{
	//クリエイトしたものを解放する
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

//更新処理
void MeshField::Update()
{

}

//描画処理
void MeshField::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans; //合成
	Renderer::SetWorldMatrix(&world);

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//インデックスバッファ設定
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);


	//マテリアル設定
	MATERIAL material{};
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //環境光
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //直接光
	Renderer::SetMaterial(material);

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	Renderer::GetDeviceContext()->DrawIndexed((22 * 2) * 20 - 2, 0, 0);

}
