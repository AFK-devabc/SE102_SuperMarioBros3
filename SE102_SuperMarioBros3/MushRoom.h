#pragma once
#include "GameObject.h"
#include "DefineInfo.h"
class CMushRoom :
    public CGameObject

{
public:
	int startY;
public:
	CMushRoom(D3DXVECTOR2 position, LPTEXTURE texture = NULL) : CGameObject(position, texture) {
		velocity = D3DXVECTOR2(0, -0.02f);
		state = MUSHROOM_STATE_INSIDE;
		startY = position.y;
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }


	void SetState(int state, int islookright = 0);

	void Hit(int type = 1);

};

