//�s�N�Z���V�F�[�_�[
#include "common.hlsl" //�K���C���N���[�h


//DirectX�̃e�N�X�`���̐ݒ���󂯌p��
Texture2D g_Texture : register(t0);//�e�N�X�`���[�O��

//DirectX�̃T���v���[�X�e�[�g�ݒ���󂯌p��
SamplerState g_SamplerState : register(s0);//�e�N�X�`���T���v���[0��


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	
	float4 normal = normalize(In.Normal); //�󂯎�����@���𐳋K��
	float light = 0.5 - dot(normal.xyz, Light.Direction.xyz); //�����v�Z������

	//float light = 0.5f - 0.5f * dot(normal.xyz, Light.Direction.xyz); //�����v�Z������
	//���̃s�N�Z���Ɏg����e�N�X�`���̐F���擾
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse.rgb *= In.Diffuse.rgb * light; //�e�N�X�`���[ * ���邳 * ���_�F
	outDiffuse.a *= In.Diffuse.a;               //

	//���̃s�N�Z���̃f�t���[�Y�F����Z
	outDiffuse *= In.Diffuse;

	//�X�y�L�����[(���ʔ���)
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz; //�����x�N�g��
	eyev = normalize(eyev);                                  //���K��


	//float rim = 1.0 + dot(eyev, normal.xyz); //�����Ɩ@���̓��ς𖾂邳�ɕϊ�����
	//rim = pow(rim, 10) * 2.0f; //�X�y�L�����Ɠ����悤�ȏ�����K���ɍs���B
	//rim = saturate(rim); //rim���T�`�����[�g����

	//�n�[�t�x�N�g���̍쐬
	float3 halfv = eyev + Light.Direction.xyz; //�����ƃ��C�g�x�N�g�������Z
	halfv = normalize(halfv); //���K������


	
	float specular = -dot(halfv, normal.xyz); //�n�[�t�x�N�g���Ɩ@
	//���̓��ς��v�Z
	specular = saturate(specular); //�T�`�����[�g����
	specular = pow(specular, 30);
	outDiffuse.rgb += specular; //�X�y�L�����𑫂���
	
}