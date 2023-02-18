#pragma once

//Ckeyboard.h use to connect to keyboard device using dinput.h

#include <d3d10.h>
#include <d3dx10.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "debug.h"
#include "DefineInfo.h"
#include <vector>
#include "KeyEventHandler.h"
class CKeyBoard
{
	static CKeyBoard* _Instance;

	LPDIRECTINPUT8       di;								// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;								// The keyboard device 

	BYTE  keyStates[256];									// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	DWORD dwElements;

	vector<LPKEYEVENTHANDLER> LPKeyHandler;

public:
	CKeyBoard();
	//define keyboard
	void InitKeyboard(HWND hWnd, HINSTANCE hInstance);
	void ProcessKeyboard(bool isCall = true);

	//return keyboard states through KeyData and dwElements
	int GetKeyboardEvents(DIDEVICEOBJECTDATA keyEvents[], DWORD  &dwElements);
	int IsKeyDown(int KeyCode);

	static CKeyBoard* GetInstance();
	void SetKeyHandler(vector<LPKEYEVENTHANDLER> LPKeyHandler) {
		for (int i = 0;i < LPKeyHandler.size(); i++)
		{
			this->LPKeyHandler.push_back(LPKeyHandler[i]);
		}
	}
	void Clear()
	{
		LPKeyHandler.clear();
	}
	~CKeyBoard();
};