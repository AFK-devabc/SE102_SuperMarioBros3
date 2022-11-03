#pragma once

#include <Windows.h>
#include <dinput.h>

#include "DefineInfo.h"
#include "Keyboard.h"
#include "debug.h"
/*
	Abstract class to define keyboard event handlers
*/
class CKeyEventHandler
{
public:
	virtual void KeyState() = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;

	void ProcessKeyboardEvents()
	{
		DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];
		DWORD dwElements;

		CKeyBoard::GetInstance()->GetKeyboardEvents(keyEvents, dwElements);

		for (DWORD i = 0; i < dwElements; i++)
		{
			int KeyCode = keyEvents[i].dwOfs;
			int KeyState = keyEvents[i].dwData;
			if ((KeyState & 0x80) > 0)
			{
				DebugOut(L"\nOnkeydown : %d", KeyCode);
				OnKeyDown(KeyCode);
			}
			else
			{
				DebugOut(L"\nup: %d", KeyCode);
				OnKeyUp(KeyCode);
			}
		}
	}
};

typedef CKeyEventHandler* LPKEYEVENTHANDLER;
