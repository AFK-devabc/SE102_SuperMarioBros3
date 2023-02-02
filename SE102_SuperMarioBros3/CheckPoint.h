#pragma once
#include "GameObject.h"
#include "DefineInfo.h"
class CCheckPoint :
    public CGameObject
{
	int tickCount;
public :
	CCheckPoint(D3DXVECTOR2 position) : CGameObject(position) {
		state = CHECKPOINT_FLOWER;
		tickCount = CHECKPOINT_SWAPTIME;
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	virtual int IsCollidable() { return 1; };

};

