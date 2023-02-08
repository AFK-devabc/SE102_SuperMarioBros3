#pragma once
#include "GameEffect.h"

class CBrickBroken :
    public CGameEffect
{
private:
	D3DXVECTOR2 tl, htl, tr, htr;
	D3DXVECTOR2 vtl, vhtl, vtr, vhtr;

public:
	CBrickBroken(D3DXVECTOR2 position) : CGameEffect(position, 200) {
		tl = htl = tr=htr = position;

		 vtl = D3DXVECTOR2(0.1, -0.2) ;
		 vhtl = D3DXVECTOR2(0.2, -0.4) ;
		 vtr = D3DXVECTOR2(-0.1, -0.2) ;
		 vhtr = D3DXVECTOR2(-0.2, -0.4);

	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {

		vtl.y += GRAVITY * dt;
		vhtl.y += GRAVITY * dt;
		vtr.y += GRAVITY * dt;
		vhtr.y += GRAVITY * dt;

		tl += vtl * dt;
		htl += vhtl * dt;
		tr += vtr * dt;
		htr += vhtr * dt;

		if (GetTickCount64() - startTime > lifeTime)
			this->Delete();
	}


	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{

		l = position.x - 16 / 2;
		t = position.y - 16 / 2;
		r = l + 16;
		b = t + 16;
	}
	void Render()
	{
		CAnimations* ani = CAnimations::GetInstance();
		ani->Get(to_string(BRICK_BROKEN))->Render(tl);
		ani->Get(to_string(BRICK_BROKEN))->Render(tr);
		ani->Get(to_string(BRICK_BROKEN))->Render(htr);
		ani->Get(to_string(BRICK_BROKEN))->Render(htl);

	}

};

