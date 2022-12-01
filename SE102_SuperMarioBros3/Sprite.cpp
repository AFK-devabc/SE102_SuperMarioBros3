#include "Sprite.h"
#include <string.h>
#include "Game.h"

CSprite::CSprite(int left, int top, int width, int height, LPTEXTURE tex)
{
	this->left = left;
	this->top = top;
	this->width = width +1;
	this->height = height +1;
	// Set the sprite’s shader resource view
	sprite.pTexture = tex->getShaderResourceView();

	sprite.TexCoord.x = left / (float)tex->getWidth();
	sprite.TexCoord.y = top / (float)tex->getHeight();

	int spriteWidth = width +1;
	int spriteHeight = height +1;

	sprite.TexSize.x = spriteWidth / (float)tex->getWidth();
	sprite.TexSize.y = spriteHeight / (float)tex->getHeight();

	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	sprite.TextureIndex = 0;

	D3DXMatrixScaling(&this->matScaling, (FLOAT)spriteWidth, (FLOAT)spriteHeight, 1.0f);

}

void CSprite::Draw(D3DXVECTOR2 position, bool flipX)
{
	D3DXVECTOR2 worldToCam = CCamera::GetInstance()->WorldToCam(position);
	CGraphics::GetInstance()->DrawSprite(worldToCam, sprite, matScaling, flipX);
}

