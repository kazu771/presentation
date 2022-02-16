//---------------------------
//3D�t�B�[���h�`��
//---------------------------
#include "main.h"
#include "renderer.h"
#include "MeshField.h"

float g_FieldHeight[21][21] =
{
	{ 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f},
	{  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  1.0f,  0.0f,  0.0f,  2.0f,  2.0f,  0.0f,  2.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  2.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  1.0f,  0.0f,  0.0f,  2.0f,  0.0f,  0.0f,  0.0f,  2.0f,  0.0f,  0.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  2.0f,  2.0f,  0.0f,  2.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  2.0f,  2.0f,  2.0f,  2.0f,  0.0f,  0.0f,  2.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  2.0f,  0.0f,  2.0f,  2.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  2.0f,  3.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  2.0f,  0.0f,  2.0f,  2.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  2.0f,  3.0f,  0.0f,  0.0f,  2.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  2.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  3.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
	{  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f},
};								   																					   


//�^������
float MeshField::GetHeight(D3DXVECTOR3 Position)//�v���C���[�ƒn�`�̈ʒu����肵����Ɏ������̂����
{
	int x, z;

	//�u���b�N�ԍ��Z�o
	x = Position.x / 5.0f + 10.0f; //���������̃|�W�V����
	z = Position.z / -5.0f + 10.0f;

	D3DXVECTOR3 pos0, pos1, pos2, pos3;

	pos0 = m_Vertex[x][z].Position;
	pos1 = m_Vertex[x + 1][z].Position;
	pos2 = m_Vertex[x][z + 1].Position;
	pos3 = m_Vertex[x + 1][z + 1].Position;

	D3DXVECTOR3 v12, v1p, c;

	v12 = pos2 - pos1;
	v1p = Position - pos1;

	D3DXVec3Cross(&c, &v12, &v1p);

	float py;
	D3DXVECTOR3 n;

	if (c.y > 0.0f)
	{
		//����|���S��
		D3DXVECTOR3 v10;
		v10 = pos0 - pos1;
		D3DXVec3Cross(&n, &v10, &v12);
	}
	else
	{
		//�E���|���S��
		D3DXVECTOR3 v13;
		v13 = pos3 - pos1;
		D3DXVec3Cross(&n, &v12, &v13);
	}

	//�����擾
	py = -((Position.x - pos1.x) * n.x + (Position.z - pos1.z) * n.z) / n.y + pos1.y;

	return py;
}
//������
void MeshField::Init()
{
	//���_�p for���[�v
	for (int x = 0; x <= 20; x++)
	{
		for (int z = 0; z <= 20; z++)
		{
			m_Vertex[x][z].Position = D3DXVECTOR3((x - 10) * 5.0f, g_FieldHeight[z][x], (z - 10) * -5.0f);
			m_Vertex[x][z].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f); //�@���x�N�g��
			m_Vertex[x][z].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f); //�@���x�N�g��
			m_Vertex[x][z].TexCoord = D3DXVECTOR2(x * 0.5f, z * 0.5f); //�@���x�N�g��
		}
	}

	//�@���x�N�g���Z�o
	for (int x = 1; x <= 19; x++)
	{
		for (int z = 1; z <= 19; z++)
		{
			D3DXVECTOR3 vx, vz, vn;

			vx = m_Vertex[x + 1][z].Position - m_Vertex[x - 1][z].Position; //�E���֌������x�N�g�������߂�
			vz = m_Vertex[x][z - 1].Position - m_Vertex[x][z + 1].Position; //�����֌������x�N�g�������߂�

			D3DXVec3Cross(&vn, &vz, &vx);//�O��
			D3DXVec3Normalize(&vn, &vn); //���K��
			m_Vertex[x][z].Normal = vn;
		}
	}
	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{}; //�o�b�t�@�f�X�N���v�V����
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 21 * 21; //���_�o�b�t�@�̃T�C�Y
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; //���_�o�b�t�@��\���t���O
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{}; //�T�u���\�[�X�f�[�^(���_�o�b�t�@�ɓ���Ă��������l�̐ݒ�)
	sd.pSysMem = m_Vertex; //���_�f�[�^�̐擪�A�h���X

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);//���_�o�b�t�@�̍쐬


	//�C���f�b�N�X�o�b�t�@����
	{
		unsigned int index[(22 * 2) * 20 - 2]; //1�s21��{�k�ރ|���S����22, �����K�v�Ȃ̂� *2, �Ō�͏k�ރ|���S�����K�v�Ȃ��̂�-2

		int i = 0;
		for (int x = 0; x < 20; x++)
		{
			for (int z = 0; z < 21; z++)
			{
				//���C����
				index[i] = x * 21 + z;
				i++;

				//�u���b�N��
				index[i] = (x + 1) * 21 + z;
				i++;
			}

			if (x == 19) //�Ō�͏k�ރ|���S�����K�v�Ȃ�����
				break;

			//�k�ރ|���S���p�C���f�b�N�X1
			index[i] = (x + 1) * 21 + 20;
			i++;

			//�k�ރ|���S���p�C���f�b�N�X2
			index[i] = (x + 1) * 21;
			i++;
		}
		//���_�o�b�t�@����
		static D3D11_BUFFER_DESC bd; //�o�b�t�@�f�X�N���v�V����
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * ((22 * 2) * 20 - 2); //���_�o�b�t�@�̃T�C�Y
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER; //���_�o�b�t�@��\���t���O
		bd.CPUAccessFlags = 0;

		static D3D11_SUBRESOURCE_DATA sd; //�T�u���\�[�X�f�[�^(���_�o�b�t�@�ɓ���Ă��������l�̐ݒ�)
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = index; //���_�f�[�^�̐擪�A�h���X

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);//���_�o�b�t�@�̍쐬

	}

	//�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetDevice(),
		"asset/texture/fields.dds", //�e�N�X�`���A�h���X
		NULL,
		NULL,
		&m_Texture,//�e�N�X�`�����󂯎��|�C���^
		NULL
	);

	assert(m_Texture);  //NULL�̏ꍇ�ɃG���[���o��

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso"); //cso(�V�F�[�_�[�������Ă���R���p�C���ς݂̃V�F�[�_�[)��ǂݍ��ݒ��_�V�F�[�_�[�����

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");//cso��ǂݍ���Ńs�N�Z���V�F�[�_�����

	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

}

//�I������
void MeshField::UnInit()
{
	//�N���G�C�g�������̂��������
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

//�X�V����
void MeshField::Update()
{

}

//�`�揈��
void MeshField::Draw()
{
	//���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//�V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//�}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans; //����
	Renderer::SetWorldMatrix(&world);

	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//�C���f�b�N�X�o�b�t�@�ݒ�
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);


	//�}�e���A���ݒ�
	MATERIAL material{};
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //����
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); //���ڌ�
	Renderer::SetMaterial(material);

	//�e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//�v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�|���S���`��
	Renderer::GetDeviceContext()->DrawIndexed((22 * 2) * 20 - 2, 0, 0);

}
