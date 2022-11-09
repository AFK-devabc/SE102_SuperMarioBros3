#pragma once
#include "Collision.h"
#include "GameObject.h"
class CGoomba :
    public CGameObject
{
protected:
	BOOLEAN isOnPlatform;
public:
	CGoomba(D3DXVECTOR2 position, D3DXVECTOR2 velocity, LPTEXTURE texture) : CGameObject(position, texture) {
		this->velocity = velocity;
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	int IsCollidable()
	{
		return 1;
	}

	int IsBlocking() { return true; }

	void SetState(int state, int islookright = 0);
};

