#pragma once
#include "GameObject.h"
#include "DefineInfo.h"
#include "GameObjectType.h"
class CCoin :
    public CGameObject
{
public:
	CCoin(D3DXVECTOR2 position) : CGameObject(position) {
		state = MUSHROOM_STATE_INSIDE;
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();

	virtual int IsCollidable() { return 1; };

};

