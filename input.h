#pragma once


class Input
{
public:
	enum KeyState
	{
		KEYNORMAL = 0,
		KEYPUSH,
		KEYRELASE,
		KEYMAX
	};

	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );
	static bool GetKeyReleace(BYTE keycode);//ó£ÇµÇΩèuä‘Ç…åüím
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];
	
};
