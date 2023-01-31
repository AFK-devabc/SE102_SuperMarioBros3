#include "Sprite.h"
#include <string.h>
#include "Game.h"

CSprite::CSprite(int left, int top, int width, int height, LPTEXTURE tex)
{
	this->left = left;
	this->top = top;
	this->width = width ;
	this->height = height ;
	// Set the sprite’s shader resource view

	float texWidth = (float)tex->getWidth();
	float texHeight = (float)tex->getHeight();

	sprite.pTexture = tex->getShaderResourceView();

	sprite.TexCoord.x = roundf(left / texWidth * 10000.0f) / 10000.0f;
	sprite.TexCoord.y = roundf(top / texHeight * 10000.0f) / 10000.0f;


	sprite.TexSize.x =  roundf(this->width / texWidth * 10000.0f) / 10000.0f;
	sprite.TexSize.y =roundf(this->height / texHeight * 10000.0f) / 10000.0f;

	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	sprite.TextureIndex = 0;

	D3DXMatrixScaling(&this->matScaling, (FLOAT) this->width, (FLOAT) this->height, 1.0f);

}

void CSprite::Draw(D3DXVECTOR2 position)
{
	D3DXVECTOR2 worldToCam = CCamera::GetInstance()->WorldToCam(position);
	CGraphics::GetInstance()->DrawSprite(worldToCam, sprite, matScaling);
}

