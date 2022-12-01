#pragma once

#include "Texture.h"
#include <string>

using namespace std;

class CSprite
{
	int left;
	int top;
	int width;
	int height;

	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;
public:
	CSprite(int left, int top, int width, int height, LPTEXTURE tex);

	void Draw(D3DXVECTOR2 position, bool flipx = false);
};

typedef CSprite* LPSPRITE;