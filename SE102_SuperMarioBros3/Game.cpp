#include "debug.h"
#include "Game.h"

CGame* CGame::__instance = NULL;

/*
	Initialize DirectX, create a Direct3D device for rendering within the window, initial Sprite library for
	rendering 2D images
	- hWnd: Application window handle
*/
void CGame::Init(HWND hWnd, HINSTANCE hInstance)
{
	this->hWnd = hWnd;
	this->hInstance = hInstance;
	keyboard->GetInstance()->InitKeyboard(hWnd, this->hInstance);
	graphic->GetInstance()->InitGraphic(hWnd, this->hInstance);
}

void CGame::Update()
{
	keyboard->GetInstance()->ProcessKeyboard();
}

CGame::~CGame()
{

}

CGame* CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}


