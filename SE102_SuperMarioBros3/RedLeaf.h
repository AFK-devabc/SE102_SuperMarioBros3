#pragma once
#include "GameObject.h"

class CRedLeaf :
    public CGameObject
{
private:
	int startY;
	int startX;
	float ax = 0.001f;
public:
	CRedLeaf(D3DXVECTOR2 position) : CGameObject(position) {
		velocity = D3DXVECTOR2(0,-0.1f);
		state = MUSHROOM_STATE_INSIDE;
		startY = position.y;
		startX = position.x;
		state = REDLEAF_STATE_IDLE;
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	virtual int IsCollidable() { return 1; };

	void Hit(int type = 1);

};

