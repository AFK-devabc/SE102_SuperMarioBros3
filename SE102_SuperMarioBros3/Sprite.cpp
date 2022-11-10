#include "Sprite.h"
#include <string.h>
#include "Game.h"

CSprite::CSprite(int left, int top, int width, int height, LPTEXTURE tex)
{
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
	// Set the sprite’s shader resource view
	sprite.pTexture = tex->getShaderResourceView();

	sprite.TexCoord.x = left / (float)tex->getWidth();
	sprite.TexCoord.y = top / (float)tex->getHeight();

	int spriteWidth = width;
	int spriteHeight = height;

	sprite.TexSize.x = spriteWidth / (float)tex->getWidth();
	sprite.TexSize.y = spriteHeight / (float)tex->getHeight();

	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	sprite.TextureIndex = 0;

	D3DXMatrixScaling(&this->matScaling, (FLOAT)spriteWidth, (FLOAT)spriteHeight, 1.0f);

}

void CSprite::Draw(D3DXVECTOR2* position)
{
	D3DXVECTOR2 worldToCam = CCamera::GetInstance()->WorldToCam(*position);
	CGraphics::GetInstance()->DrawSprite(&worldToCam, &sprite, &matScaling);
}

