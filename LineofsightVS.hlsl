//ピクセルシェーダー
#include "common.hlsl" //必ずインクルード

void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp;							  //毎回お約束の頂点変換
	wvp = mul(World, View);               //wvp = ワールド行列 * カメラ行列
	wvp = mul(wvp, Projection);           //wvp = wvp * プロジェクション行列
	Out.Position = mul(In.Position, wvp); //変換結果を出力

	//頂点法線をワールド変換で出力
	float4 worldNormal, normal;           //ローカル変数を作成
	normal = float4(In.Normal.xyz, 0.0);  //法線ベクトルのwを0としてコピー（平行移動しないため)
	worldNormal = mul(normal, World);     //法線をワールド行列で回転する

	worldNormal = normalize(worldNormal); //回転後の法線を正規化する
	Out.Normal = worldNormal;			  //回転後の法線出力 In.Normalでなく回転後の法線を出

	////明るさの計算
	////光ベクトルと法線の内積 XYZ要素のみで計算
	//float light = -dot(Light.Direction.xyz, worldNormal.xyz);
	//light = saturate(light);			  //明るさを0と1の間で飽和化する
	
	
	Out.Diffuse = In.Diffuse;		  //αは頂点の物をそのまま出力

	Out.TexCoord = In.TexCoord;           //頂点のテクスチャ座標を出力


	//ワールド変換した頂点座標を出力
	Out.WorldPosition = mul(In.Position, World);
}
