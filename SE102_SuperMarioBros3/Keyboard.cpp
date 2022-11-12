#include "Keyboard.h"

CKeyBoard* CKeyBoard::_Instance = NULL;

CKeyBoard::CKeyBoard()
{
	_Instance = this;
}

void CKeyBoard::InitKeyboard(HWND hWnd,HINSTANCE hInstance)
{
	HRESULT
		hr = DirectInput8Create
		(
			hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&di, NULL
		);
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DirectInput8Create failed!\n");
		return;
	}

	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] CreateDevice failed!\n");
		return;
	}

	hr = didv->SetDataFormat(&c_dfDIKeyboard);

	hr = didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
	{
		DebugOut(L"[ERROR] DINPUT8::Acquire failed!\n");
		return;
	}

	DebugOut(L"[INFO] Keyboard has been initialized successfully\n");
}

void CKeyBoard::ProcessKeyboard(vector<LPKEYEVENTHANDLER> LPKeyHandler)
{
	HRESULT hr;
	dwElements = KEYBOARD_BUFFER_SIZE;

	// Collect all key states first
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h == DI_OK)
			{
				DebugOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else {
				DebugOut(L"[INFO] Keyboard re-acquired failed!\n");
				dwElements = 0;
				return;
			}
		}
		else
		{
			DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			dwElements = 0;
			return;
		}
	}
	for (int i = 0;i < LPKeyHandler.size(); i++)
	{
		LPKeyHandler[i]->KeyState((BYTE*)&keyStates);
	}

	// Collect all buffered events
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		DebugOut(L"[ERROR] DINPUT::Get KeyboardData failed. Error: %d\n", hr);
		dwElements = 0;
		return;
	}

	for (int i = 0;i < LPKeyHandler.size(); i++)
	{
		LPKeyHandler[i]->KeyState((BYTE*)&keyStates);
	}


	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			for (int i = 0;i < LPKeyHandler.size(); i++)
			{
				DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
				LPKeyHandler[i]->OnKeyDown(KeyCode);
			}
		else
			for (int i = 0;i < LPKeyHandler.size(); i++)
			{
				DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

				LPKeyHandler[i]->OnKeyUp(KeyCode);
			}
	}


	//DebugOut(L"[INFO] Get KeyBoardData Successful!");
}

int CKeyBoard::GetKeyboardEvents(DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE], DWORD &dwElements)
{
	for (DWORD i = 0; i < this->dwElements; i++)
	{
		keyEvents[i] = this->keyEvents[i];
	}
	dwElements = this->dwElements;

	return 0;
}

int CKeyBoard::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

CKeyBoard* CKeyBoard::GetInstance()
{
	if (_Instance == NULL)
		_Instance = new CKeyBoard();
	return _Instance;
}

CKeyBoard::~CKeyBoard()
{
	di->Release();
	didv->Release();
}