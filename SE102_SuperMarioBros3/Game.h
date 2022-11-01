#pragma once
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include "CTextures.h"
#include "Animations.h"
#include "Sprites.h"
#include "Keyboard.h"
#include "Graphics.h"

#include "DefineInfo.h"
#include "GameObject.h"
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

	vector<LPGAMEOBJECT> LPGameObject;

public:
	// Init DirectX, Sprite Handler, keyboard device
	void Init(HWND hWnd, HINSTANCE hInstance);
	//
	void LoadResource();
	// Update GameOject, keyboard state
	void Update(DWORD dt);
	// Render gameobject sprite
	void Render();


	static CGame* GetInstance();

	~CGame();
};