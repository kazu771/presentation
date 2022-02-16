//
//
// date:2020/07/28   name:Kazuki Wada  
//
#define _CRT_SECURE_NO_WARNINGS
#include "Keylogger.h"
#include "keyboard.h"

//グローバル変数
typedef unsigned long KeyloggerType;
static  KeyloggerType g_CurrentDate = 0;  //その前のフレームでのキーの状態を保持用
static  KeyloggerType g_PrevDate = 0;     //前のフレームでの状態キーを保持
static  KeyloggerType g_TriggerDate = 0;
static  KeyloggerType g_ReleaceDate = 0;
static int g_KeyloggerMode = 0;   //0ノーマル 1:記録 2:再生
static  KeyloggerType* g_pRecordCurrentDate = NULL;
static int g_RecordFrame = 0;
static int g_RecordPlayFrame = 0;
static int g_RecordFrameMax = 0;

//キーボードとキーロガーの変換表
//hのenumの中の順番
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

//更新
void Keylogger_Update(void)
{
	//前フレームの状態を保存
	g_PrevDate = g_CurrentDate;

	//キーロガーモードによって動作変更
	//記録か通常の時に入るif文
	if (g_KeyloggerMode <= 1)
	{
		g_CurrentDate = 0; //g_Currentkeystate
		//キーロガーの状態を取得
		for (int i = 0; i < KL_MAX; i++)
		{
			if (Keyboard_IsKeyDown(g_KKs[i]))
			{
				//押されていたら１左にシフトされて1が入る
				//ビットが立っているところが押されているという事になる
				g_CurrentDate |= 1u << i;
			}
		}
		//キーを記録するモードの時
		if (g_KeyloggerMode == 1)
		{
			//安全処置
			if (g_RecordFrame < g_RecordFrameMax)
			{
				g_pRecordCurrentDate[g_RecordFrame++] = g_CurrentDate;
				//g_RecordFrame++でもよいがその場合[]の中の++を取る,今の状態は可読性が悪い

			}
		}
	}
	else
	{
		//再生モードの時

		//安全装置
		//記録フレーム数より多く再生したとき
		if (g_RecordPlayFrame < g_RecordFrame)
		{
			g_CurrentDate = g_pRecordCurrentDate[g_RecordPlayFrame++];

		}
		else
		{
			g_CurrentDate = 0;
			g_KeyloggerMode = 0; //普通モード
		}
		//参考演算子でも書き換え可能
		//g_CurrentDate = g_RecordPlayFrame < g_RecordFrame ? g_pRecordCurrentDate[g_RecordPlayFrame++] : 0;
	}
	//はなした瞬間と押した瞬間を見分ける
	g_TriggerDate = (g_PrevDate ^ g_CurrentDate) & g_CurrentDate;
	g_ReleaceDate = (g_PrevDate ^ g_CurrentDate) & g_PrevDate;

}

//押てたら検知
//戻り値：押されてたらtrue
//先生のやつには(int)がない
bool Keylogger_Press(KeyKind kl)
{
	//何か押されていたら数値になり押されてるよって教えてくれる
	return g_CurrentDate & (1u << (int)kl);
}
//押したら検知
bool Keylogger_Trigger(KeyKind kl)
{
	return g_TriggerDate & (1u << (int)kl);
}
//はなした瞬間を検知
bool Keylogger_Releace(KeyKind kl)
{
	return g_ReleaceDate & (1u << (int)kl);
}


void Keylogger_RecordStart(int frame_max)
{
	//初回は通らない
	if (g_pRecordCurrentDate)
	{
		free(g_pRecordCurrentDate);
	}
	g_pRecordCurrentDate = (KeyloggerType*)malloc(sizeof(KeyloggerType) *frame_max);
	g_KeyloggerMode = 1;  //記録モード
	g_RecordFrame = 0;
	g_RecordFrameMax = frame_max;  //安全策用
}

void Keylogger_RecordEnd(void)
{
	if (!g_pRecordCurrentDate)
	{
		return;
	}
	FILE* fp = fopen("keylogger.dat", "wb");
	//バイナリの先頭にデータ量を記録
	fwrite(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);  //４バイト一回
	//ファイルへデータ保存
	fwrite(g_pRecordCurrentDate, sizeof(unsigned long), g_RecordFrame, fp);
	fclose(fp);

	g_KeyloggerMode = 0;  //通常モードに切り替え
	if (g_pRecordCurrentDate)
	{
		free(g_pRecordCurrentDate);
		g_pRecordCurrentDate = NULL;
	}
}

void Keylogger_RecordLoad(void)
{
	FILE* fp = fopen("keylogger.dat", "rb");
	//バイナリの先頭にデータ量を記録
	fread(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);  //４バイト一回
	//初回は通らない
	if (g_pRecordCurrentDate)
	{
		free(g_pRecordCurrentDate);
	}
	g_pRecordCurrentDate = (KeyloggerType*)malloc(sizeof(unsigned char) * g_RecordFrame);
	//ファイルへデータ保存
	fread(g_pRecordCurrentDate, sizeof(KeyloggerType), g_RecordFrame, fp);
	fclose(fp);


}
void Keylogger_RecordPlay(void)
{
	g_RecordPlayFrame = 0;
	g_KeyloggerMode = 2; //再生モード
}
bool Keylogger_IsRecordPlay(void)
{
	if (g_KeyloggerMode == 2)
	{
		return true;
	}
	return false;
}