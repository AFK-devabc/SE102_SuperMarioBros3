#pragma once
#include "GameEffect.h"
class CCoinDrop :
    public CGameEffect
{
public:
	CCoinDrop(D3DXVECTOR2 position) : CGameEffect(position, 210) {
		this->velocity = D3DXVECTOR2(0, -BRICK_DEFLECT_SPEED);

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
		ani->Get(to_string(COIN_DROP))->Render(position);
	};
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL)
	//{
	//	position += velocity * dt;
	//}

};

