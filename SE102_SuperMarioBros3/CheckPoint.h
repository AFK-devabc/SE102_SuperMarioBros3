#pragma once
#include "GameObject.h"
#include "DefineInfo.h"
class CCheckPoint :
    public CGameObject
{
	int tickCount;
	LPGAMEOBJECT checkpointBlock;
public :
	CCheckPoint(D3DXVECTOR2 position, LPGAMEOBJECT block) : CGameObject(position) {
		state = CHECKPOINT_FLOWER;
		tickCount = CHECKPOINT_SWAPTIME;
		this->checkpointBlock = block;
	};

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	virtual int IsCollidable() { return 1; };
	virtual void Delete() { isDeleted = true; checkpointBlock->Delete(); }

};

