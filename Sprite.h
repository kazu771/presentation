//=============================================================================
//  �X�v���C�g�`�� [Sprite.h]
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
		float RED, float GREEN, float BLUE, float ALPHA);//�`�揈��

	//1:ID, 2:X���W, 3:y���W, 4:����, 5:����,6:�؂���x,7:�؂���y//8:�؂��艡��, 9:�؂���c��, 10:��, 11:��, 12:��, 13:�A���t�@�l
	static void Draws(ID3D11ShaderResourceView* textureId, float x, float y, float width, float height, float tx, float ty, float tw, float th, 
		float RED, float GREEN, float BLUE, float ALPHA);//�`�揈��2(�؂��莞�ɉ��̒��_�̂ݐ؂������)

private:
	//���Ԃ����������Ȃ�����static
	static ID3D11Buffer* m_VertexBuffer;
	static ID3D11VertexShader* m_VertexShader;
	static ID3D11PixelShader* m_PixelShader;
	static ID3D11InputLayout* m_VertexLayout;



};

#endif