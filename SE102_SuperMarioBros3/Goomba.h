#pragma once
#include "Collision.h"
#include "GameObject.h"
#include "DefineInfo.h"
class CGoomba :
    public CGameObject
{
protected:
	BOOLEAN isOnPlatform;

	DWORD die_start;
	int type;
	DWORD jumpstart;
public:
	CGoomba(D3DXVECTOR2 position, int type = 0) : CGameObject(position) {
		this->type = type;
		this->velocity = D3DXVECTOR2(Goomba_Walking_Speed * (isLookingRight ? 1 : -1), 0);
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsCollidable() { return 1; };
	virtual void SetState(int state, int isGoingRight = 0);
};

