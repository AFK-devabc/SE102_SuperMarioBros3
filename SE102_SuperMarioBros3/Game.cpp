#include "debug.h"
#include "Game.h"


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
	camera->SetGamePlayZone(D3DXVECTOR2(GAMEPLAY_SCREEN_WIDTH, GAMEPLAY_SCREEN_HEIGHT));
	scenes->InitScenes();
	scenes->SwitchScene();

}

void CGame::LoadResource()
{
}

void CGame::Update(DWORD dt)
{
	scenes->SwitchScene();
	scenes->GetCurrentScene()->Update(dt);

	int state = scenes->GetCurrentScene()->GetState();
	switch (state)
	{
	case SCENE_STATE_PLAYING:
	{
		keyboard->ProcessKeyboard();
		camera->Update(dt);
		break;
	}
	case SCENE_STATE_SWITCHSCENE_DELAY:
	{
		break;
	}
	case SCENE_STATE_IDLE:
	{
		break;
	}
	case SCENE_STATE_PAUSING:
	{
		break;
	}
	default:
		keyboard->ProcessKeyboard();
		break;
	}
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


