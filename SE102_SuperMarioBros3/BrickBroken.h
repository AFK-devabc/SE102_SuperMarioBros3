#pragma once
#include "GameEffect.h"
#include "DefineInfo.h"
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

		vtl.y += 0.002f * dt;
		vhtl.y += 0.002f * dt;
		vtr.y += 0.002f * dt;
		vhtr.y += 0.002f * dt;

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
		ani->Get("9900")->Render(tl);
		ani->Get("9900")->Render(tr);
		ani->Get("9900")->Render(htr);
		ani->Get("9900")->Render(htl);

	}

};

