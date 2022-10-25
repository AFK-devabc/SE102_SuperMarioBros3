#pragma once
#include"GameObject.h"
class CMovableObject : public CGameObject
{
protected:
	D3DXVECTOR2 velocity;

public:
	void SetVelocity(D3DXVECTOR2 velocity) {	this->velocity = velocity;}

	D3DXVECTOR2 GetVelocity() {		return velocity;	}

	virtual void Update(DWORD dt) = 0;


};

