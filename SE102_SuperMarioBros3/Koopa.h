#pragma once
#include "GameObject.h"
class CKoopa :
    public CGameObject
{
public:
	CKoopa(D3DXVECTOR2 position, int behavior, LPTEXTURE texture = NULL) : CGameObject(position, texture) {
		velocity = D3DXVECTOR2(0, 0);
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	void SetState(int state, int islookright = 0);

	void Hit(int type = 1);
};

