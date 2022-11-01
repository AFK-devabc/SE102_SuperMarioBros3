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

void CKeyBoard::ProcessKeyboard()
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
			}
		}
		else
		{
			DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
		}
	}

	// Collect all buffered events
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		DebugOut(L"[ERROR] DINPUT::Get KeyboardData failed. Error: %d\n", hr);
	}

	//for (DWORD i = 0; i < dwElements; i++)
	//{
	//	int KeyCode = keyEvents[i].dwOfs;
	//	int KeyState = keyEvents[i].dwData;
	//	if ((KeyState & 0x80) > 0)
	//		DebugOut(L"\nOnkeydown");
	//	else
	//		DebugOut(L"\nup");
	//}

	//DebugOut(L"[INFO] Get KeyBoardData Successful!");
}

int CKeyBoard::GetKeyboardData(DIDEVICEOBJECTDATA KeyData[KEYBOARD_BUFFER_SIZE], DWORD &dwElements)
{

	KeyData = this->keyEvents;
	dwElements = this->dwElements;
	return 0;
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