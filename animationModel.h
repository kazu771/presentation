//=================================================================================================
//�X�L�����b�V���A�j���[�V������{����.h[animationModel.h]
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


//�ό`���_�\����
//�畆��\��
struct DEFORM_VERTEX
{
	aiVector3D Position;
	aiVector3D Normal;

	int BoneNum;            //���_�����Ă鍜�̐�,1���_�Ԃ�
	std::string BoneName[4];//�{���̓{�[���X�e�B�b�N�C���f�b�N�X�ŊǗ�,�ǂ̍��ɂ��Ă邩�̏���������
	float BoneWeight[4];    //�ǂ̍��ɂǂꂭ�炢���Ă邩��\�����́A�����ŕ\��
};

//�{�[���\����
//����ō��̌�����ς�����
struct BONE
{
	aiMatrix4x4 Matrix;
	aiMatrix4x4 AnimationMatrix;
	aiMatrix4x4 OffsetMatrix;
};

class AnimetionModel
{
private:
	const aiScene* m_AiScene = NULL; //assimpy�Ճf�[�^�ۑ����邽�߂̕ϐ�
	std::unordered_map<std::string, const aiScene*> m_Animation;
	ID3D11Buffer**	m_VertexBuffer; //�z��ɂ��邽�߂Ƀ|�C���^�̔z��ɂ��Ă���
	ID3D11Buffer**	m_IndexBuffer;

	std::unordered_map<std::string, ID3D11ShaderResourceView*> m_Texture; //�Y�����̕������鎖���ł���

	std::vector<DEFORM_VERTEX>* m_DeformVertex;	  //�ό`�㒸�_�f�[�^
	std::unordered_map<std::string, BONE> m_Bone; //�{�[���f�[�^(���O�ŎQ��)

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