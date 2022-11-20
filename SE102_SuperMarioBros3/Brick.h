#pragma once
#include "GameObject.h"
class CBrick :
    public CGameObject
{
private:
	D3DXVECTOR2 initialposition;

	int behavior;
	int hitted = 0;
	int itemContain = 0;
public:
	CBrick(D3DXVECTOR2 position, int behavior, int itemContain = 0, LPTEXTURE texture = NULL) : CGameObject(position, texture) {
		this->behavior = behavior;
		initialposition = position;
		velocity = D3DXVECTOR2(0, 0);
		this->itemContain = itemContain;
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	int GetBehavior() { return behavior; }

	void SetState(int state, int islookright = 0);
	int GetItemContain() { return itemContain; }
	void Hit(int type = 1);
};

