#pragma once

//Ckeyboard.h use to connect to keyboard device using dinput.h

#define DIRECTINPUT_VERSION 0x0800
#include <d3d10.h>
#include <d3dx10.h>
#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#include "debug.h"
#define KEYBOARD_BUFFER_SIZE 1024
class CKeyBoard
{
	static CKeyBoard* _Instance;

	LPDIRECTINPUT8       di;								// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;								// The keyboard device 

	BYTE  keyStates[256];									// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	DWORD dwElements;

public:
	CKeyBoard();
	//define keyboard
	void InitKeyboard(HWND hWnd, HINSTANCE hInstance);
	void ProcessKeyboard();

	//return keyboard states through KeyData and dwElements
	int GetKeyboardData(DIDEVICEOBJECTDATA KeyData[KEYBOARD_BUFFER_SIZE], DWORD  &dwElements);


	static CKeyBoard* GetInstance();

	~CKeyBoard();
};