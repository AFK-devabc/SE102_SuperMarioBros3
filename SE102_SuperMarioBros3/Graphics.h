#pragma once
#include "Texture.h"
#include <d3d10.h>
#include <d3dx10.h>

#include "debug.h"
#include "DefineInfo.h"

class CGraphics
{
private:
	static CGraphics* __instance;
	HWND hWnd;									// Window handle
	HINSTANCE hInstance;

	int backBufferWidth = 0;					// Backbuffer width & height, will be set during Direct3D initialization
	int backBufferHeight = 0;

	ID3D10Device* pD3DDevice = NULL;
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	ID3D10BlendState* pBlendStateAlpha = NULL;			// To store alpha blending state

	ID3DX10Sprite* spriteObject = NULL;				// Sprite handling object 

public:
	void InitGraphic(HWND hWnd, HINSTANCE hInstance);

	LPTEXTURE LoadTexture(LPCWSTR texturePath);

	void Draw(float x, float y, LPTEXTURE tex, RECT* rect = NULL);
	void DrawSprite(D3DXVECTOR2* position, D3DX10_SPRITE* sprite, D3DXMATRIX* matScaling);

	void BeginRender();
	void EndRender();

	D3DXVECTOR2 GetBackBuffer()
	{
		return D3DXVECTOR2(backBufferWidth, backBufferHeight);
	}

	//void Render();

	static CGraphics* GetInstance();
};

