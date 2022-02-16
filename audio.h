#pragma once

#include <xaudio2.h>
#include "GameObject.h"

class Audio : public GameObject
{
private:
	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	IXAudio2SourceVoice*	m_SourceVoice;
	BYTE*					m_SoundData;

	int						m_Length;
	int						m_PlayLength;

public:

	static void InitMaster(); //staticにしてるからインスタンス生成しなくても違うファイルから呼べる
	static void UnInitMaster();

	void Init() {}; //からのメソッド,GameObject.hで純粋仮想関数にしているため作っているが何もしない
	void UnInit();
	void Update() {};
	void Draw() {}; //からのメソッド

	void Load(const char *FileName);
	void Play(bool Loop = false);




};

