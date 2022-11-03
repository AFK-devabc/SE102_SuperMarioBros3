#include "debug.h"
#include "Game.h"
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
	CTextures* textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MARIO, TEXTURE_PATH_MARIO);
	textures->Add(ID_TEX_MISC, TEXTURE_PATH_MISC);


	CSprites* sprites = CSprites::GetInstance();

	LPTEXTURE texMario = textures->Get(ID_TEX_MARIO);

	// readline => id, left, top, right , bottom, texture

	sprites->Add("10001", 246, 154, 259, 181, texMario);
	sprites->Add("10002", 275, 154, 290, 181, texMario);
	sprites->Add("10003", 304, 154, 321, 181, texMario);

	sprites->Add("10011", 186, 154, 200, 181, texMario);
	sprites->Add("10012", 155, 154, 171, 181, texMario);
	sprites->Add("10013", 125, 154, 141, 181, texMario);

	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add("10001");
	ani->Add("10002");
	ani->Add("10003");
	animations->Add("500", ani);



	ani = new CAnimation(100);
	ani->Add("10011");
	ani->Add("10012");
	ani->Add("10013");
	animations->Add("501", ani);



	LPTEXTURE texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add("20001", 300, 117, 317, 133, texMisc);
	sprites->Add("20002", 318, 117, 335, 133, texMisc);
	sprites->Add("20003", 336, 117, 353, 133, texMisc);
	sprites->Add("20004", 354, 117, 371, 133, texMisc);

	ani = new CAnimation(100);
	ani->Add("20001", 1000);
	ani->Add("20002");
	ani->Add("20003");
	ani->Add("20004");
	animations->Add("510", ani);


	CPlayer* mario = new CPlayer(D3DXVECTOR2(10, 10), D3DXVECTOR2(0, 0), NULL);

	CPlayer* mario2 = new CPlayer(D3DXVECTOR2(20, 10), D3DXVECTOR2(0, 0), NULL);

	LPGameObject.push_back(mario2);

	LPGameObject.push_back(mario);
}

void CGame::Update(DWORD dt)
{
	keyboard->ProcessKeyboard();
	for (int i = 0;i < LPGameObject.size(); i++)
	{
		LPGameObject[i]->Update(dt);
	}

}

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


