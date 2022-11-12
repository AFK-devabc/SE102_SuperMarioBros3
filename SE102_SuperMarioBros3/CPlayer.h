#pragma once
#include "GameObject.h"
#include "KeyEventHandler.h"
class CPlayer :
    public CGameObject,
    public  CKeyEventHandler
{
protected:
	float maxVx;
	float Ax;
	bool isSitting = false;
	BOOLEAN isOnPlatform;

	int untouchable;
	ULONGLONG untouchable_start;


	
public :
	CPlayer(D3DXVECTOR2 position, LPTEXTURE texture = NULL) : CGameObject(position, texture) {
		maxVx = 1;
		Ax = 0;
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) ;
	void Render();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);

	int IsCollidable()
	{
		return (state != GAME_OBJECT_STATE_DIE);
	}

	int IsBlocking() { return (state != GAME_OBJECT_STATE_DIE && untouchable == 0); }

	void SetState(int state, int islookright = 0);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	// keyboard handler
	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

};

