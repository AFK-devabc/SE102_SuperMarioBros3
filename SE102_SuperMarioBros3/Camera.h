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
	D3DXVECTOR2 worldSize;
public:


	D3DXVECTOR2 GetPosition() { return position; }
	void SetPosition(D3DXVECTOR2 position) { this->position = position; }

	void SetCamFollow(D3DXVECTOR2* position)
	{
		followObjects = position;
	}
	void SetWorldSize(D3DXVECTOR2 worldSize) { this->worldSize = worldSize; }
	void Update(DWORD dt)
	{
		//DebugOut(L"%f,	%f", followObjects->x, followObjects->y);

	
		this->position.x =  ( followObjects->x - backBuffer.x / 2);
		this->position.y = (int)(followObjects->y - backBuffer.y / 2);

		if (position.x < 0) position.x = 0;
		if (position.x + backBuffer.x > worldSize.x) position.x = worldSize.x - backBuffer.x;


		if (position.y < 0) position.y = 0;
		if (position.y + backBuffer.y > 432) position.y = 432 - backBuffer.y;

		//this->position.y = 236;
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