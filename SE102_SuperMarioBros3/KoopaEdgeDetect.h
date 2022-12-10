#pragma once
#include "GameObject.h"
class CKoopaEdgeDetect :
    public CGameObject
{
public:
	CKoopaEdgeDetect(D3DXVECTOR2 position) : CGameObject(position) {
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
};

