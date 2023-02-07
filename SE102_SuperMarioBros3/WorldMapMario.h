#pragma once
#include "KeyEventHandler.h"
#include "D3DX10.h"


class CWorldMapMario :
	public  CKeyEventHandler
{
private :
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 position;
	D3DXVECTOR2 NextPosition;
	int currentX, currentY;
	int marioType;

	int state;
public :
	CWorldMapMario();

	void SetMarioType(int type) { this->marioType = type; }

	void Update(DWORD dt);
	void Render();

	// keyboard handler
	void OnKeyDown(int KeyCode);

	void SetState(int state) { this->state = state; }
};


