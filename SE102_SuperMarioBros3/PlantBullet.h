#pragma once
#include "GameObject.h"
class CPlantBullet :
    public CGameObject
{
public:
	CPlantBullet(D3DXVECTOR2 position,D3DXVECTOR2 velocity) : CGameObject(position) {
		this->velocity = velocity;
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }


};

