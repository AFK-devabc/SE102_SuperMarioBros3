#pragma once

#include "Texture.h"
#include "Game.h"
#include <string.h>

class CSprite
{
	//int left;
	//int top;
	//int right;
	//int bottom;
	RECT spriteRect;

	LPTEXTURE texture;
	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;
public:
	//CSprite( int left, int top, int right, int bottom, LPTEXTURE tex);

	CSprite(RECT spriteRect, LPTEXTURE tex);

	void Draw(D3DXVECTOR2* position);
};

typedef CSprite* LPSPRITE;