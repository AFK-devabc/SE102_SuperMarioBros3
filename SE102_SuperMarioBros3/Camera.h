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
	D3DXVECTOR2 gamePlayZone;
	D3DXVECTOR2* followObjects;
	D3DXVECTOR2 worldSize;
	bool isCamLock;
public:


	D3DXVECTOR2 GetPosition() { return position; }
	void SetPosition(D3DXVECTOR2 position) { this->position = position; }

	void SetCamFollow(D3DXVECTOR2* position)
	{
		if(position != NULL)
		followObjects = position;
		isCamLock = false;
	}
	void SetWorldSize(D3DXVECTOR2 worldSize) { this->worldSize = worldSize; }
	void Update(DWORD dt)
	{
		//DebugOut(L"%f,	%f", followObjects->x, followObjects->y);

		if (!isCamLock)
		{
			this->position.x = (followObjects->x - gamePlayZone.x / 2);
			this->position.y = (int)(followObjects->y - gamePlayZone.y / 2);

			if (position.x < 0) position.x = 0;
			if (position.x + gamePlayZone.x > worldSize.x) position.x = worldSize.x - gamePlayZone.x;


			if (position.y < 0) position.y = 0;
			if (position.y + gamePlayZone.y > worldSize.y) position.y = worldSize.y - gamePlayZone.y;
		}
	}
	void SetGamePlayZone(D3DXVECTOR2 gamePlayZone)
	{
		this->gamePlayZone = gamePlayZone;
	}

	void SetBackBuffer(D3DXVECTOR2 backBuffer)
	{
		this->backBuffer = backBuffer;
	}
	D3DXVECTOR2 WorldToCam(D3DXVECTOR2 objPosition)
	{
		return objPosition - position;
	}
	void SetCamLock(D3DXVECTOR2 position) {
		if (position.x < 0 && position.y < 0)
		{
			isCamLock = false; 
			return;
		}
		this->position = position; 
		isCamLock = true;
	}
	static CCamera* GetInstance();

};