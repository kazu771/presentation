//
//
// date:2020/07/28   name:Kazuki Wada  
//
#define _CRT_SECURE_NO_WARNINGS
#include "Keylogger.h"
#include "keyboard.h"

//�O���[�o���ϐ�
typedef unsigned long KeyloggerType;
static  KeyloggerType g_CurrentDate = 0;  //���̑O�̃t���[���ł̃L�[�̏�Ԃ�ێ��p
static  KeyloggerType g_PrevDate = 0;     //�O�̃t���[���ł̏�ԃL�[��ێ�
static  KeyloggerType g_TriggerDate = 0;
static  KeyloggerType g_ReleaceDate = 0;
static int g_KeyloggerMode = 0;   //0�m�[�}�� 1:�L�^ 2:�Đ�
static  KeyloggerType* g_pRecordCurrentDate = NULL;
static int g_RecordFrame = 0;
static int g_RecordPlayFrame = 0;
static int g_RecordFrameMax = 0;

//�L�[�{�[�h�ƃL�[���K�[�̕ϊ��\
//h��enum�̒��̏���
static Keyboard_Keys g_KKs[KL_MAX] = {
		KK_W,
		KK_S,
		KK_A,
		KK_D,
		KK_E,
		KK_Q,
		KK_LEFT,
		KK_RIGHT,
		KK_UP,
		KK_DOWN,
		KK_SPACE,
};

void Keylogger_Initialize(void)
{
	g_CurrentDate = 0;
	g_PrevDate = 0;
	g_TriggerDate = 0;
	g_ReleaceDate = 0;
	g_KeyloggerMode = 0;
	g_pRecordCurrentDate = NULL;
	g_RecordFrame = 0;
	g_RecordPlayFrame = 0;
	g_RecordFrameMax = 0;

};
void Keylogger_Finalize(void)
{
	if (g_pRecordCurrentDate)
	{
		free(g_pRecordCurrentDate);
		g_pRecordCurrentDate = NULL;
	}
}

//�X�V
void Keylogger_Update(void)
{
	//�O�t���[���̏�Ԃ�ۑ�
	g_PrevDate = g_CurrentDate;

	//�L�[���K�[���[�h�ɂ���ē���ύX
	//�L�^���ʏ�̎��ɓ���if��
	if (g_KeyloggerMode <= 1)
	{
		g_CurrentDate = 0; //g_Currentkeystate
		//�L�[���K�[�̏�Ԃ��擾
		for (int i = 0; i < KL_MAX; i++)
		{
			if (Keyboard_IsKeyDown(g_KKs[i]))
			{
				//������Ă�����P���ɃV�t�g�����1������
				//�r�b�g�������Ă���Ƃ��낪������Ă���Ƃ������ɂȂ�
				g_CurrentDate |= 1u << i;
			}
		}
		//�L�[���L�^���郂�[�h�̎�
		if (g_KeyloggerMode == 1)
		{
			//���S���u
			if (g_RecordFrame < g_RecordFrameMax)
			{
				g_pRecordCurrentDate[g_RecordFrame++] = g_CurrentDate;
				//g_RecordFrame++�ł��悢�����̏ꍇ[]�̒���++�����,���̏�Ԃ͉ǐ�������

			}
		}
	}
	else
	{
		//�Đ����[�h�̎�

		//���S���u
		//�L�^�t���[������葽���Đ������Ƃ�
		if (g_RecordPlayFrame < g_RecordFrame)
		{
			g_CurrentDate = g_pRecordCurrentDate[g_RecordPlayFrame++];

		}
		else
		{
			g_CurrentDate = 0;
			g_KeyloggerMode = 0; //���ʃ��[�h
		}
		//�Q�l���Z�q�ł����������\
		//g_CurrentDate = g_RecordPlayFrame < g_RecordFrame ? g_pRecordCurrentDate[g_RecordPlayFrame++] : 0;
	}
	//�͂Ȃ����u�ԂƉ������u�Ԃ���������
	g_TriggerDate = (g_PrevDate ^ g_CurrentDate) & g_CurrentDate;
	g_ReleaceDate = (g_PrevDate ^ g_CurrentDate) & g_PrevDate;

}

//���Ă��猟�m
//�߂�l�F������Ă���true
//�搶�̂�ɂ�(int)���Ȃ�
bool Keylogger_Press(KeyKind kl)
{
	//����������Ă����琔�l�ɂȂ艟����Ă����ċ����Ă����
	return g_CurrentDate & (1u << (int)kl);
}
//�������猟�m
bool Keylogger_Trigger(KeyKind kl)
{
	return g_TriggerDate & (1u << (int)kl);
}
//�͂Ȃ����u�Ԃ����m
bool Keylogger_Releace(KeyKind kl)
{
	return g_ReleaceDate & (1u << (int)kl);
}


void Keylogger_RecordStart(int frame_max)
{
	//����͒ʂ�Ȃ�
	if (g_pRecordCurrentDate)
	{
		free(g_pRecordCurrentDate);
	}
	g_pRecordCurrentDate = (KeyloggerType*)malloc(sizeof(KeyloggerType) *frame_max);
	g_KeyloggerMode = 1;  //�L�^���[�h
	g_RecordFrame = 0;
	g_RecordFrameMax = frame_max;  //���S���p
}

void Keylogger_RecordEnd(void)
{
	if (!g_pRecordCurrentDate)
	{
		return;
	}
	FILE* fp = fopen("keylogger.dat", "wb");
	//�o�C�i���̐擪�Ƀf�[�^�ʂ��L�^
	fwrite(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);  //�S�o�C�g���
	//�t�@�C���փf�[�^�ۑ�
	fwrite(g_pRecordCurrentDate, sizeof(unsigned long), g_RecordFrame, fp);
	fclose(fp);

	g_KeyloggerMode = 0;  //�ʏ탂�[�h�ɐ؂�ւ�
	if (g_pRecordCurrentDate)
	{
		free(g_pRecordCurrentDate);
		g_pRecordCurrentDate = NULL;
	}
}

void Keylogger_RecordLoad(void)
{
	FILE* fp = fopen("keylogger.dat", "rb");
	//�o�C�i���̐擪�Ƀf�[�^�ʂ��L�^
	fread(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);  //�S�o�C�g���
	//����͒ʂ�Ȃ�
	if (g_pRecordCurrentDate)
	{
		free(g_pRecordCurrentDate);
	}
	g_pRecordCurrentDate = (KeyloggerType*)malloc(sizeof(unsigned char) * g_RecordFrame);
	//�t�@�C���փf�[�^�ۑ�
	fread(g_pRecordCurrentDate, sizeof(KeyloggerType), g_RecordFrame, fp);
	fclose(fp);


}
void Keylogger_RecordPlay(void)
{
	g_RecordPlayFrame = 0;
	g_KeyloggerMode = 2; //�Đ����[�h
}
bool Keylogger_IsRecordPlay(void)
{
	if (g_KeyloggerMode == 2)
	{
		return true;
	}
	return false;
}