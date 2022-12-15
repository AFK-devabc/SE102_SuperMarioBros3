#include "Coin.h"

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - 16 / 2;
	t = position.y - 16 / 2;
	r = l + 16;
	b = t + 16;

}

void CCoin::Render()
{
	CAnimations::GetInstance()->Get(to_string(OBJECT_TYPE_COIN))->Render(position);
}
