#pragma once
#include "GameObject.h"
class CMarioTail :
    public CGameObject
{
private: 
	DWORD startTime;
public:
	CMarioTail(D3DXVECTOR2 position) : CGameObject(position) {
		startTime = GetTickCount64();
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();

	virtual int IsCollidable() { return 1; };

	virtual void IsCollidingWith(LPGAMEOBJECT e);
	void OnCollisionWithGoomba(LPGAMEOBJECT e);
	void OnCollisionWithKoopa(LPGAMEOBJECT e);
	void OnCollisionWithBrick(LPGAMEOBJECT e);
	void OnCollisionWithPlant(LPGAMEOBJECT e);
	void OnCollisionWithItemContainer(LPGAMEOBJECT e);

};

