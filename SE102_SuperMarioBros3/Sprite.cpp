#include "Sprite.h"
#include <string.h>
#include "Game.h"



CSprite::CSprite(RECT spriteRect, LPTEXTURE tex)
{
	this->spriteRect = spriteRect;

	// Set the sprite’s shader resource view
	sprite.pTexture = tex->getShaderResourceView();

	sprite.TexCoord.x =	this->spriteRect.left / (float)tex->getSize().x;
	sprite.TexCoord.y = this->spriteRect.top / (float)tex->getSize().y;

	int spriteWidth = (this->spriteRect.right - this->spriteRect.left + 1);
	int spriteHeight = (this->spriteRect.bottom - this->spriteRect.top + 1);

	sprite.TexSize.x = spriteWidth / (float)tex->getSize().x;
	sprite.TexSize.y = spriteHeight / (float)tex->getSize().y;

	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	sprite.TextureIndex = 0;

	D3DXMatrixScaling(&this->matScaling, (FLOAT)spriteWidth, (FLOAT)spriteHeight, 1.0f);

}

void CSprite::Draw(D3DXVECTOR2* position)
{
	CGraphics::GetInstance()->DrawSprite(position, &sprite, &matScaling);
}

