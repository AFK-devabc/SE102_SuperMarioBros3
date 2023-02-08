#pragma once
#include "GameObject.h"

class CGameEffect :
    public CGameObject
{
protected:
    DWORD startTime;
    DWORD lifeTime;
	float Ay;
public:
	CGameEffect(D3DXVECTOR2 position, DWORD lifeTime) : CGameObject(position) {
		startTime = GetTickCount64();
		this->lifeTime = lifeTime;
		Ay = 0;
	}
	virtual	void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		this->velocity.y += Ay * dt;
		this->position += velocity * dt;
		if (GetTickCount64() - startTime > lifeTime)
			this->Delete();
	}

	virtual void Render() {};
};

