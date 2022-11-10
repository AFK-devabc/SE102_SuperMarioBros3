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
	keyboard->InitKeyboard(hWnd, this->hInstance);
	graphic->InitGraphic(hWnd, this->hInstance);
}

void CGame::LoadResource()
{
	LoadAniData_FromXML("Resources/Mario.xml");
	LoadAniData_FromXML("Resources/Misc.xml");
	LoadAniData_FromXML("Resources/Enemies.xml");

	CPlayer* mario = new CPlayer(D3DXVECTOR2(10, 10), D3DXVECTOR2(0, 0), NULL);
	CPlatform* cloud = new CPlatform(10, GROUND_Y, 16, 16, 20, "CloudBegin", "CloudMidder", "CloudEnd");
	CGoomba* goomba = new CGoomba(D3DXVECTOR2(50, 50), D3DXVECTOR2(Goomba_Walking_Speed, MARIO_GRAVITY), NULL);
	CPlatform* cloud1 = new CPlatform(10, GROUND_Y-16, 16, 16, 1, "CloudBegin", "CloudMidder", "CloudEnd");
	CPlatform* cloud2 = new CPlatform(10 + 16*16, GROUND_Y - 16, 16, 16, 1, "CloudBegin", "CloudMidder", "CloudEnd");
	 goomba = new CGoomba(D3DXVECTOR2(50, 50), D3DXVECTOR2(Goomba_Walking_Speed, MARIO_GRAVITY), NULL);
	 LPGameObject.push_back(goomba);

	 goomba = new CGoomba(D3DXVECTOR2(50, 50), D3DXVECTOR2(Goomba_Walking_Speed, MARIO_GRAVITY), NULL);
	 LPGameObject.push_back(goomba);
	 goomba = new CGoomba(D3DXVECTOR2(100, 50), D3DXVECTOR2(Goomba_Walking_Speed, MARIO_GRAVITY), NULL);
	 LPGameObject.push_back(goomba);
	 goomba = new CGoomba(D3DXVECTOR2(100, 50), D3DXVECTOR2(Goomba_Walking_Speed, MARIO_GRAVITY), NULL);
	 LPGameObject.push_back(goomba);
	 goomba = new CGoomba(D3DXVECTOR2(50, 50), D3DXVECTOR2(Goomba_Walking_Speed, MARIO_GRAVITY), NULL);
	 LPGameObject.push_back(goomba);
	 goomba = new CGoomba(D3DXVECTOR2(100, 50), D3DXVECTOR2(Goomba_Walking_Speed, MARIO_GRAVITY), NULL);
	 LPGameObject.push_back(goomba);

	LPGameObject.push_back(cloud);
	LPGameObject.push_back(mario);
	LPGameObject.push_back(cloud1);
	LPGameObject.push_back(cloud2);

	LPKeyHandler.push_back(mario);
}

void CGame::Update(DWORD dt)
{
	keyboard->ProcessKeyboard(LPKeyHandler);

	for (int i = 0;i < LPGameObject.size(); i++)
	{
		if (LPGameObject[i]->IsDeleted())
		{
			LPGameObject.erase(LPGameObject.begin() + i);
			DebugOut(L"						%d", i);
		}
	}

	for (int i = 0;i < LPGameObject.size(); i++)
	{
		if (LPGameObject[i]->IsDeleted())
		{
			
		}
		LPGameObject[i]->Update(dt, &LPGameObject);
	}


}
bool IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CGame::Render()
{
	graphic->BeginRender();
	for (int i = 0;i < LPGameObject.size(); i++)
	{
		LPGameObject[i]->Render();
	}
	graphic->EndRender();

	//graphic->Render();
}

CGame::~CGame()
{

}

CGame* CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}


