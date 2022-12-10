#pragma once
#include "GameObject.h"
#include "DefineInfo.h"
class CGameEffect :
    public CGameObject
{
protected:
    DWORD startTime;
    DWORD lifeTime;
public:
	CGameEffect(D3DXVECTOR2 position, DWORD lifeTime) : CGameObject(position) {
		startTime = GetTickCount64();
		this->lifeTime = lifeTime;
		
	}
	virtual	void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {
		this->position += velocity * dt;
		if (GetTickCount64() - startTime > lifeTime)
			this->Delete();
	}

	

	virtual void Render() {};
};

