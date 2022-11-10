#pragma once
#include <D3DX10.h>
class CCamera
{
private:
	static CCamera* __instance;

protected:
	D3DXVECTOR2 position;
	D3DXVECTOR2 backBuffer;
public:


	D3DXVECTOR2 GetPosition() { return position; }
	void SetPosition(D3DXVECTOR2 position) { this->position = position; }

	void SetCamFollow(D3DXVECTOR2 position)
	{
		this->position.x = position.x - backBuffer.x / 2;
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