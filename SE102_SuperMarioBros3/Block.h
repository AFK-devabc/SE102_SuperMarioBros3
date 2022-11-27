#pragma once
#include "GameObject.h"
class CBlock :
    public CGameObject
{
public:
		CBlock(D3DXVECTOR2 position) : CGameObject(position) {
			velocity = D3DXVECTOR2(0, 0);
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
};

