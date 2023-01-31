#pragma once
#include "GameObject.h"
#include "DefineInfo.h"
class CPlant :
	public CGameObject
{
protected:
	D3DXVECTOR2 pinePosition;
	int plantType;

	int isGoingUp;
	DWORD startTime;
	int isDamage = 0;
	int isLookingTop;
	DWORD attackCount;

	int isFiring;
public:
	CPlant(D3DXVECTOR2 position, int plantType = PLANT_STATE_BITE) : CGameObject(position) {
		pinePosition = position;
		startTime = GetTickCount64();
		this->plantType = plantType;
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	int IsDamage() { return isDamage; }

	int GetAniID();
		virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	void SetState(int state, int islookright = 0);

};

