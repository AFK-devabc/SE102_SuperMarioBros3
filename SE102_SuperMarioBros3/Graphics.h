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
	void Draw(float x, float y, LPTEXTURE tex, int l, int t, int r, int b)
	{
		RECT rect;
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		this->Draw(x, y, tex, &rect);
	}

	void BeginRender();
	void EndRender();



	static CGraphics* GetInstance();
};

