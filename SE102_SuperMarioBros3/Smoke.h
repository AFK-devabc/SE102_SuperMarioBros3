#pragma once
#include "GameEffect.h"
class CSmoke :
    public CGameEffect
{
public:
	CSmoke(D3DXVECTOR2 position) : CGameEffect(position, 400) {
		Ay = 0;
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = position.x - 16 / 2;
		t = position.y - 16 / 2;
		r = l + 16;
		b = t + 16;
	}
	virtual void Render() {
		CAnimations* ani = CAnimations::GetInstance();
		ani->Get(to_string(PLANT_DEAD_SMOKE))->Render(position);
	};
};

