#include "debug.h"
#include "Game.h"
#include "ImportFromXML.h"


#include "Platform.h"
#include "Goomba.h"
#include "CPlayer.h"

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
	keyboard = CKeyBoard::GetInstance();
	graphic = CGraphics::GetInstance();
	camera = CCamera::GetInstance();
	 scenes = CScenes::GetInstance();

	keyboard->InitKeyboard(hWnd, this->hInstance);
	graphic->InitGraphic(hWnd, this->hInstance);

	camera->SetBackBuffer(graphic->GetBackBuffer());

	scenes->InitScenes();
	scenes->SwitchScene();

}

void CGame::LoadResource()
{
}

void CGame::Update(DWORD dt)
{

	keyboard->ProcessKeyboard();
	scenes->GetCurrentScene()->Update(dt);

	camera->Update(dt);
	scenes->SwitchScene();

}

void CGame::Render()
{
	graphic->BeginRender();

	scenes->GetCurrentScene()->Render();

	graphic->EndRender();

}


CGame::~CGame()
{

}

CGame* CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}


