/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102

	SAMPLE 01 - SKELETON CODE

	This sample illustrates how to:

	1/ Re-organize introductory code to an initial skeleton for better scalability
	2/ CGame is a singleton, playing a role of an "engine".
	3/ CGameObject is an abstract class for all game objects
	4/ CTexture is a wrapper class for ID3D10TEXTURE

	NOTE: to create transparent background, download GIMP, then use Color to Alpha feature
================================================================ */

#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#include <vector>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"

#include "CTextures.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Animation.h"
#include "Animations.h"

#include "DefineInfo.h"


using namespace std;



CMario* mario;


CBrick* brick;

vector<LPGAMEOBJECT> gameObjects;  

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources. In this example, create a brick object and mario object
*/
void LoadResources()
{
	CGame* game = CGame::GetInstance();
	CTextures* textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MARIO, TEXTURE_PATH_MARIO);
	//textures->Add(ID_ENEMY_TEXTURE, TEXTURE_PATH_ENEMIES, D3DCOLOR_XRGB(156, 219, 239));
	textures->Add(ID_TEX_MISC, TEXTURE_PATH_MISC);


	CSprites* sprites = CSprites::GetInstance();

	LPTEXTURE texMario = textures->Get(ID_TEX_MARIO);

	// readline => id, left, top, right 

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

	mario = new CMario( D3DXVECTOR2(10, 10),  D3DXVECTOR2(0, 0),NULL);

}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	mario->Update(dt);
	CGame::GetInstance()->Update();
}

/*
	Render a frame
*/
void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	if (pD3DDevice != NULL)
	{
		// clear the background 
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// Use Alpha blending for transparent sprites
		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

		//brick->Render();
		mario->Render();

		spriteHandler->End();
		pSwapChain->Present(0, 0);
	}
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		DebugOut(L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetDebugWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	CGame* game = CGame::GetInstance();
	game->Init(hWnd, hInstance);



	LoadResources();

	Run();

	return 0;
}