#pragma once
#include "GameObject.h"
class CMarioTail :
    public CGameObject
{
private: 
	DWORD startTime;
public:
	CMarioTail(D3DXVECTOR2 position, LPTEXTURE texture = NULL) : CGameObject(position, texture) {
		startTime = GetTickCount64();
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void IsCollidingWith(LPGAMEOBJECT e);
};

