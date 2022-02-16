//=====================================================================================================
//スカイドーム基本処理.h[Sky,h]
//date:2021/07/31          name:Kazuki Wada
//=====================================================================================================
#ifndef SKY_H_
#define SKY_H_

class Sky : public GameObject
{
public:
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:
	Model* m_Model;  //モデルを読み込むため用
	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader*  m_PixelShader = NULL;
	ID3D11InputLayout*  m_VertexLayout = NULL;
};

#endif // !PLAYER_H_