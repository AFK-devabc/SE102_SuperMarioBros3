#pragma once
#include "GameObject.h"

class CKoopa :
    public CGameObject
{
protected : 
	BOOLEAN isOnPlatform;

	ULONGLONG die_start;
	virtual void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithPlant(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithItemContainer(LPCOLLISIONEVENT e);

public:
	CKoopa(D3DXVECTOR2 position) : CGameObject(position) {
		velocity = D3DXVECTOR2(-KOOPA_WALKING_SPEED, 0);
		state = KOOPA_STATE_WING;
	};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsCollidable() { return 1; };
	virtual void SetState(int state, int isGoingRight = 0);


};

