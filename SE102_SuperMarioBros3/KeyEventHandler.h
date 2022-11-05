#pragma once

#include <Windows.h>
#include <dinput.h>

#include "DefineInfo.h"
#include "debug.h"
/*
	Abstract class to define keyboard event handlers
*/
class CKeyEventHandler
{
protected:
	BYTE*  keyStates;									// DirectInput keyboard state buffer 
public:
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;

	int IsKeyDown(int KeyCode)
	{
		return (keyStates[KeyCode] & 0x80) > 0;
	}
};

typedef CKeyEventHandler* LPKEYEVENTHANDLER;
