#pragma once
#include "GameEffect.h"

class CHardCollision :
    public CGameEffect
{
	
public:
	CHardCollision(D3DXVECTOR2 position) : CGameEffect(position, 210) {
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
		ani->Get(to_string(HARD_COLLISION))->Render(position);
	};

};

