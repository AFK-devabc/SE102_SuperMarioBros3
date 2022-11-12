#include "debug.h"
#include "Game.h"
#include "ImportFromXML.h"

#include "PlayScene.h"

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
	keyboard->InitKeyboard(hWnd, this->hInstance);
	graphic->InitGraphic(hWnd, this->hInstance);

	scene11 = new CPlayScene(1, "Resources/Scene_1_1.xml");
	scene11->Load();

	scene11->GetKeyEventHandler(LPKeyHandler);

	camera->SetBackBuffer(graphic->GetBackBuffer());

}

void CGame::LoadResource()
{
}

void CGame::Update(DWORD dt)
{

	keyboard->ProcessKeyboard(LPKeyHandler);

	scene11->Update(dt);

	//camera->SetCamFollow(player->GetPosition());
}
bool IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CGame::Render()
{
	graphic->BeginRender();
	scene11->Render();
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


