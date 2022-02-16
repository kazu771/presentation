//=================================================================================================
//スキンメッシュアニメーション基本処理.h[animationModel.h]
//date:2021/09/02   date:Kazuki Wada
//=================================================================================================
#ifndef ANIMETIONMODEL_H_
#define ANIMETIONMODEL_H_

#include <unordered_map>

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#pragma comment (lib, "assimp.lib")


//変形頂点構造体
//皮膚を表す
struct DEFORM_VERTEX
{
	aiVector3D Position;
	aiVector3D Normal;

	int BoneNum;            //頂点がついてる骨の数,1頂点ぶん
	std::string BoneName[4];//本来はボーンスティックインデックスで管理,どの骨についてるかの情報を持つもの
	float BoneWeight[4];    //どの骨にどれくらいついてるかを表すもの、割合で表す
};

//ボーン構造体
//これで骨の向きを変えられる
struct BONE
{
	aiMatrix4x4 Matrix;
	aiMatrix4x4 AnimationMatrix;
	aiMatrix4x4 OffsetMatrix;
};

class AnimetionModel
{
private:
	const aiScene* m_AiScene = NULL; //assimpyぷデータ保存するための変数
	std::unordered_map<std::string, const aiScene*> m_Animation;
	ID3D11Buffer**	m_VertexBuffer; //配列にするためにポインタの配列にしている
	ID3D11Buffer**	m_IndexBuffer;

	std::unordered_map<std::string, ID3D11ShaderResourceView*> m_Texture; //添え字の方を入れる事ができる

	std::vector<DEFORM_VERTEX>* m_DeformVertex;	  //変形後頂点データ
	std::unordered_map<std::string, BONE> m_Bone; //ボーンデータ(名前で参照)

	void CreateBone(aiNode* node);
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);
public:
	void Load(const char *FileName);
	void LoadAnimation(const char *FileName, const char *AnimationName);
	void Unload();
	void Update(const char *AnimationName, int Frame);
	void Draw();

};

#endif // !ANIMETIONMODEL_H_