#pragma once
#include "GameObject.h"
#include "KeyEventHandler.h"
class CPlayer :
    public CGameObject,
    public  CKeyEventHandler
{
private:
	float maxVx;
	float Ax;
	bool isSitting = false;
public :
	CPlayer(D3DXVECTOR2 position, D3DXVECTOR2 velocity, LPTEXTURE texture) : CGameObject(position, texture) {
		maxVx = 1;
		Ax = 0;
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b);


	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) ;
	void Render();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	int IsCollidable()
	{
		return 1;
	}

	int IsBlocking() { return true; }

	void SetState(int state, int islookright = 0);
	// keyboard handler
	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

};

