#pragma once
#include "MovableObject.h"
#include "KeyEventHandler.h"
class CPlayer :
    public CMovableObject, 
    public  CKeyEventHandler
{
private:
	float maxVx;
	float Ax;
	bool isSitting = false;
public :
	CPlayer(D3DXVECTOR2 position, D3DXVECTOR2 velocity, LPTEXTURE texture) : CMovableObject(position, velocity, texture) {
		maxVx = 1;
		Ax = 0;
	};

	void Update(DWORD dt);
	void Render();

	void SetState(int state, int islookright = 0);
	// keyboard handler
	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

};

