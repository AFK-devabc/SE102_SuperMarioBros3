#include "CColorBox.h"

void CColorBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
		l = position.x - size.x/2;
		t = position.y - size.y / 2;
		r = l + size.x;
		b = t + size.y;
}
