#pragma once
#include"GameObject.h"
class CMovableObject : public CGameObject
{
protected:
	D3DXVECTOR2 velocity;
	bool isLookingRight = true;
public:

	CMovableObject(D3DXVECTOR2 position, D3DXVECTOR2 velocity, LPTEXTURE texture) : CGameObject(position, texture) {
		this->velocity = velocity;
	};

	void SetVelocity(D3DXVECTOR2 velocity) {	this->velocity = velocity;}

	D3DXVECTOR2 GetVelocity() {		return velocity;	}

	virtual void Update(DWORD dt) = 0;
};

