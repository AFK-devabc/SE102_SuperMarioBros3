#pragma once
#include "GameObject.h"
class CPinePortal :
	public CGameObject
{
private:
	D3DXVECTOR2 desPosition;
	D3DXVECTOR2 camLockPosition;
	int type; // 1: godown, 0 : goup
public:

	CPinePortal(D3DXVECTOR2 position, D3DXVECTOR2 desPosition,D3DXVECTOR2 camLockPosition, int type ) : CGameObject(position) {
		this->desPosition = desPosition;
		this->camLockPosition = camLockPosition;
		this->type = type;
	};

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b)
	{		l = position.x - 24 / 2;
	t = position.y - 24 / 2;
	r = l + 24;
	b = t + 24;
}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render() {
		if (type == 1)
		{
			CAnimations::GetInstance()->Get(to_string(GREEN_PIPE))->Render(position);
			CAnimations::GetInstance()->Get(to_string(GREEN_PIPE))->Render(desPosition);
		}
		else
		{
			CAnimations::GetInstance()->Get(to_string(GREEN_PIPE))->Render(desPosition);
			CAnimations::GetInstance()->Get(to_string(BLACK_PINE))->Render(position);
		}
	};
	int GetType() { return type; }
	virtual int IsLateRender() { return 1; }

	D3DXVECTOR2 GetDesPosition() { return desPosition; }
	D3DXVECTOR2 GetCamLockPosition() { return camLockPosition; }

};

