#pragma once
#include "GameObject.h"
class CBlock :
    public CGameObject
{
protected:
    int itemContain = 0;
    D3DXVECTOR2 initialposition;
public:
	CBlock(D3DXVECTOR2 position, int itemContain = 0) : CGameObject(position) {
		initialposition = position;
		velocity = D3DXVECTOR2(0, 0);
		this->itemContain = itemContain;
	};

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() {};

	virtual int IsLateRender() { return 1; }
	virtual int IsBlocking() { return 1; }

	virtual void DropItems();

};

