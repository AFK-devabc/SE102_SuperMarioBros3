#pragma once
#include "GameObject.h"
#include "DefineInfo.h"
class CKoopa :
    public CGameObject
{
protected : 
	BOOLEAN isOnPlatform;

	ULONGLONG die_start;

public:
	CKoopa(D3DXVECTOR2 position, LPTEXTURE texture = NULL) : CGameObject(position, texture) {
		velocity = D3DXVECTOR2(Goomba_Walking_Speed, 0);
		state = KOOPA_STATE_WALKING;
	};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void SetState(int state, int isGoingRight = 0);
};

