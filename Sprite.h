//=============================================================================
//  スプライト描画 [Sprite.h]
//  Date:2021/08/18   name:Kazuki Wada
//=============================================================================
#ifndef SPRITE_H_
#define SPRITE_H_


class Sprite
{
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Load();
	static void Draw(ID3D11ShaderResourceView* textureId, float x, float y, float width, float height,
		float tx, float ty, float tw, float th,
		float RED, float GREEN, float BLUE, float ALPHA);//描画処理

	//1:ID, 2:X座標, 3:y座標, 4:横幅, 5:立幅,6:切り取りx,7:切り取りy//8:切り取り横幅, 9:切り取り縦幅, 10:赤, 11:緑, 12:青, 13:アルファ値
	static void Draws(ID3D11ShaderResourceView* textureId, float x, float y, float width, float height, float tx, float ty, float tw, float th, 
		float RED, float GREEN, float BLUE, float ALPHA);//描画処理2(切り取り時に下の頂点のみ切り取るもの)

private:
	//実態を持ちたくないからstatic
	static ID3D11Buffer* m_VertexBuffer;
	static ID3D11VertexShader* m_VertexShader;
	static ID3D11PixelShader* m_PixelShader;
	static ID3D11InputLayout* m_VertexLayout;



};

#endif