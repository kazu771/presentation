#ifndef KEYLOGGER_H
#define KEYLOGGER_H

typedef enum KeyKind_tag
{
	//�A�v���Ŏg���{�^���������Ă���
	//0����X�^�[�g
	KL_FRONT,
	KL_BACK,
	KL_LEFT,
	KL_RIGHT,
	KL_UP,
	KL_DOWN,
	KL_TURN_LEFT,
	KL_TURN_RIGHT,
	KL_TURN_FRONT,
	KL_TURN_BACK,
	KL_SPACE,

	KL_MAX
} KeyKind;

void Keylogger_Initialize(void);
void Keylogger_Finalize(void);
void Keylogger_Update(void);

//�L�[�̏�Ԏ擾
//���Ă��猟�m
bool Keylogger_Press(KeyKind kl);

//�L�[�̏�Ԏ擾
//�������猟�m
bool Keylogger_Trigger(KeyKind kl);

//�L�[�̏�Ԏ擾
//�͂Ȃ����u�Ԃ����m
bool Keylogger_Releace(KeyKind kl);

void Keylogger_RecordStart(int frame_max);
void Keylogger_RecordEnd(void);
void Keylogger_RecordLoad(void);
void Keylogger_RecordPlay(void);
bool Keylogger_IsRecordPlay(void);
#endif // !KEYLOGGER_H
