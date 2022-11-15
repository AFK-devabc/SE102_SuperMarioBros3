#pragma once
#include <D3DX10.h>
#include "debug.h"
class CCamera
{
private:
	static CCamera* __instance;

protected:
	D3DXVECTOR2 position;
	D3DXVECTOR2 backBuffer;
	D3DXVECTOR2* followObjects;
public:


	D3DXVECTOR2 GetPosition() { return position; }
	void SetPosition(D3DXVECTOR2 position) { this->position = position; }

	void SetCamFollow(D3DXVECTOR2* position)
	{
		followObjects = position;
	}

	void Update(DWORD dt)
	{
		DebugOut(L"%d,	%d", followObjects->x, followObjects->y);
		this->position.x = followObjects->x - backBuffer.x / 2;
		this->position.y = 0;
	}

	void SetBackBuffer(D3DXVECTOR2 backBuffer)
	{
		this->backBuffer = backBuffer;
	}
	D3DXVECTOR2 WorldToCam(D3DXVECTOR2 objPosition)
	{
		return objPosition - position;
	}

	static CCamera* GetInstance();

};