#pragma once
#include "GameObject.h"
class CItemContainer :
    public CGameObject
{
private:
    int itemContain = 0;
    D3DXVECTOR2 initialposition;
	int hitted = 0;

public:
	CItemContainer(D3DXVECTOR2 position, int itemContain , int state) : CGameObject(position) {
		initialposition = position;
		velocity = D3DXVECTOR2(0, 0);
		this->itemContain = itemContain;
		this->state = state;
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();

	void SetState(int state);

	virtual int IsLateRender() { return 1; }
	virtual int IsBlocking() { return 1; }

	void DropItems();

};

