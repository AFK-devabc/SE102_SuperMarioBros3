#pragma once
#include "GameObject.h"
class CCheckPoint :
    public CGameObject
{
	int tickCount;
	LPGAMEOBJECT checkpointBlock;

	bool isChecked;
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
	virtual void Delete() { isDeleted = true;  }

	virtual void Check();
	bool IsChecked() { return isChecked; }
};

