#pragma once
#include "KeyEventHandler.h"
#include "D3DX10.h"

#define WMMARIO_WALKING_SPEED 0.1f
class CWorldMapMario :
	public  CKeyEventHandler
{
private :
	D3DXVECTOR2 position;
	D3DXVECTOR2 NextPosition;
	int currentX, currentY;
	int marioType;

	int state;
public :
	CWorldMapMario();

	void SetMario(int type);

	void Update(DWORD dt);
	void Render();

	// keyboard handler
	void OnKeyDown(int KeyCode);

	void SetState(int state) { this->state = state; }
};


