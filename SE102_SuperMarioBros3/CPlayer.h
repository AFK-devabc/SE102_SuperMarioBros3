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
	DWORD untouchable_start;

	 int GetAniID();
	 int marioType = SMALL_MARIO;
	
	int isChangingform = 0;
	int isAttacking = 0;
	DWORD attack_start;

	int isFlying;
	DWORD flyingStart;

public :
	CPlayer(D3DXVECTOR2 position) : CGameObject(position) {
		maxVx = 0.8f;
		Ax = 0;
		attack_start = 0;
		untouchable_start = 0;
		flyingStart = 0;

	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) ;
	void Render();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithRedLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);

	int IsCollidable()
	{
		return (state != GAME_OBJECT_STATE_DIE);
	}

	int IsBlocking() { return (state != GAME_OBJECT_STATE_DIE && untouchable == 0); }

	void SetState(int state, int islookright = 0);

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void EndChangingForm() { isChangingform = 0; }
	virtual void Attacked();
	// keyboard handler
	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void SetMarioType( int type);
	int GetMarioType() { return marioType; }

};

