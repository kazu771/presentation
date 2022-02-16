//ピクセルシェーダー
#include "common.hlsl" //必ずインクルード


//DirectXのテクスチャの設定を受け継ぐ
Texture2D g_Texture : register(t0);//テクスチャー０番

//DirectXのサンプラーステート設定を受け継ぐ
SamplerState g_SamplerState : register(s0);//テクスチャサンプラー0番


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	
	float4 normal = normalize(In.Normal); //受け取った法線を正規化
	float light = 0.5 - dot(normal.xyz, Light.Direction.xyz); //光源計算をする

	//float light = 0.5f - 0.5f * dot(normal.xyz, Light.Direction.xyz); //光源計算をする
	//このピクセルに使われるテクスチャの色を取得
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse.rgb *= In.Diffuse.rgb * light; //テクスチャー * 明るさ * 頂点色
	outDiffuse.a *= In.Diffuse.a;               //

	//このピクセルのデフューズ色を乗算
	outDiffuse *= In.Diffuse;

	//スペキュラー(鏡面反射)
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz; //視線ベクトル
	eyev = normalize(eyev);                                  //正規化


	//float rim = 1.0 + dot(eyev, normal.xyz); //視線と法線の内積を明るさに変換する
	//rim = pow(rim, 10) * 2.0f; //スペキュラと同じような処理を適当に行う。
	//rim = saturate(rim); //rimをサチュレートする

	//ハーフベクトルの作成
	float3 halfv = eyev + Light.Direction.xyz; //視線とライトベクトルを加算
	halfv = normalize(halfv); //正規化する


	
	float specular = -dot(halfv, normal.xyz); //ハーフベクトルと法
	//線の内積を計算
	specular = saturate(specular); //サチュレートする
	specular = pow(specular, 30);
	outDiffuse.rgb += specular; //スペキュラを足しこ
	
}