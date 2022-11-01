#pragma once
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include "Texture.h"
#include "Keyboard.h"
#include "Graphics.h"

#include "DefineInfo.h"
/*
	Our simple game framework
*/
class CGame
{
	static CGame* __instance;
	HWND hWnd;									// Window handle
	HINSTANCE hInstance;

	CKeyBoard* keyboard;
	CGraphics* graphic;

public:
	// Init DirectX, Sprite Handler
	void Init(HWND hWnd, HINSTANCE hInstance);
	//
	void Update();
	static CGame* GetInstance();

	~CGame();
};