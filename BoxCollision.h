//======================================================================================
//ボックスコリジョン基本処理.h[BoxCollision,h]
//date:2021/08/16  name:Kazuki Wada
//======================================================================================
#ifndef BOXCOLLISION_H_
#define BOXCOLLISION_H_

#include "GameObject.h"

class BoxCollision : public GameObject
{
public:
	struct VERTEX3D
	{
		D3DXVECTOR3 Pos; //頂点座標
		D3DXVECTOR3 Nolmal; //法線
		D3DXVECTOR4 Col; //色
		D3DXVECTOR2 TexCode;
	};
	void Init();
	void UnInit();
	void Update();
	void Draw();

private:
	ID3D11Buffer*				m_VertexBuffer = NULL;	//頂点情報を入れるための領域
	ID3D11Buffer*				m_IndexBuffer = NULL;   //インデックス情報を入れるための領域
	ID3D11ShaderResourceView*	m_Texture = NULL;		//ポリゴンにはるものを保存する領域
	ID3D11VertexShader*			m_VertexShader = NULL;
	ID3D11PixelShader*			m_PixelShader = NULL;
	ID3D11InputLayout*			m_VertexLayout = NULL;
	ID3D11VertexShader*			m_IndexShader = NULL;
	ID3D11PixelShader*			m_IndexPixcelShader = NULL;
	D3DXVECTOR3					m_TargetPos; //プレイヤーの位置座標を入れるよう
	D3DXVECTOR3					m_TargetRot; //プレイヤーの回転回転角度
	D3DXVECTOR3					m_Direction; //プレイヤーの角度を入れる箱
	D3DXVECTOR3					m_Cross;
	float						m_Angle;     //角度
	bool						m_IsVisible;  //コリジョンを有効かするかどうか


};


#endif // !BOXCOLLISION_H_
