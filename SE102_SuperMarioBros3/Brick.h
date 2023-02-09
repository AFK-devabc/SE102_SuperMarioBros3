#pragma once
#include "GameObject.h"

class CBrick :
    public CGameObject
{
private:
	D3DXVECTOR2 initialposition;
	DWORD startChangeToCoin;
public:
	CBrick(D3DXVECTOR2 position) : CGameObject(position) {
		initialposition = position;
		state = BRICK_STATE_IDLE;
		startChangeToCoin = -1;
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void Delete();

	void SetState(int state);

	virtual int IsBlocking() { return state != BRICK_STATE_CHANGED_INTO_COIN; }

};

