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

	static void InitMaster(); //static�ɂ��Ă邩��C���X�^���X�������Ȃ��Ă��Ⴄ�t�@�C������Ăׂ�
	static void UnInitMaster();

	void Init() {}; //����̃��\�b�h,GameObject.h�ŏ������z�֐��ɂ��Ă��邽�ߍ���Ă��邪�������Ȃ�
	void UnInit();
	void Update() {};
	void Draw() {}; //����̃��\�b�h

	void Load(const char *FileName);
	void Play(bool Loop = false);




};

