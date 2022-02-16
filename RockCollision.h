////================================================================================================================
////岩コリジョン基本処理.h[RockCollision.h]
////date:2022/02/01           name:Kauzki Wada
////================================================================================================================
//#ifndef ROCKCOLLISION_H_
//#define ROCKCOLLISION_H_
//
//#include "GameObject.h"
//
//class RockCollision : public GameObject
//{
//private:
//	ID3D11Buffer*				m_VertexBuffer = NULL;	//頂点情報を入れるための領域
//	ID3D11Buffer*				m_IndexBuffer = NULL;   //インデックス情報を入れるための領域
//
//	ID3D11ShaderResourceView*	m_Texture = NULL;		//ポリゴンにはるものを保存する領域
//
//	ID3D11VertexShader* m_VertexShader = NULL;
//	ID3D11PixelShader*  m_PixelShader = NULL;
//	ID3D11InputLayout*  m_VertexLayout = NULL;
//
//	ID3D11VertexShader* m_IndexShader = NULL;
//	ID3D11PixelShader* m_IndexPixcelShader = NULL;
//	D3DXVECTOR3 targetpos; //プレイヤーの位置座標を入れるよう
//	D3DXVECTOR3 targetrot; //プレイヤーの回転回転角度
//	D3DXVECTOR3 Direction; //プレイヤーの角度を入れる箱
//	D3DXVECTOR3 cross;
//	float  angle;     //角度
//	bool isVisible;  //コリジョンを有効かするかどうか
//
//public:
//	struct VERTEX3D
//	{
//		D3DXVECTOR3 pos; //頂点座標
//		D3DXVECTOR3 nolmal; //法線
//		D3DXVECTOR4 col; //色
//		D3DXVECTOR2 texcode;
//	};
//	void Init();
//	void UnInit();
//	void Update();
//	void Draw();
//};
//#endif // !ROCKCOLLISION_H_
