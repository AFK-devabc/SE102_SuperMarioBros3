#include "Platform.h"

#include "Sprite.h"
#include "Sprites.h"

void CPlatform::Render()
{
	if (this->length <= 0) return;
	float xx = position.x;
	CSprites* s = CSprites::GetInstance();

	s->Get(this->spriteIdBegin)->Draw( D3DXVECTOR2(xx, position.y));
	xx += this->cellWidth;
	for (int i = 1; i < this->length - 1; i++)
	{
		s->Get(this->spriteIdMiddle)->Draw( D3DXVECTOR2(xx, position.y));
		xx += this->cellWidth;
	}
	if (length > 1)
		s->Get(this->spriteIdEnd)->Draw( D3DXVECTOR2(xx, position.y));
}

void CPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = position.x - cellWidth_div_2;
	t = position.y - this->cellHeight / 2;
	r = l + this->cellWidth * this->length;
	b = t + this->cellHeight;
}