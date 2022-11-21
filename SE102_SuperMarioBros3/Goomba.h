#pragma once
#include "Collision.h"
#include "GameObject.h"
#include "DefineInfo.h"
class CGoomba :
    public CGameObject
{
protected:
	BOOLEAN isOnPlatform;

	ULONGLONG die_start;

public:
	CGoomba(D3DXVECTOR2 position, LPTEXTURE texture) : CGameObject(position, texture) {
		this->velocity = D3DXVECTOR2(Goomba_Walking_Speed,0);
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	void SetState(int state, int islookright = 0);
};

