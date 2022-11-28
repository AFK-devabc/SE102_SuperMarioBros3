#pragma once
#include <Windows.h>
#include <d3dx10.h>

#include "Animations.h"
#include "Sprites.h"
#include "Textures.h"
#include "Collision.h"
#include "Camera.h"

class CGameObject
{
protected:

	D3DXVECTOR2 position;
	D3DXVECTOR2 velocity;
	bool isLookingRight = true;

	// This should be a pointer to an object containing all graphic/sound/audio assets for rendering this object. 
	// For now, just a pointer to a single texture	
	int state;

	bool isDeleted;

public:
	CGameObject(D3DXVECTOR2 position = D3DXVECTOR2(0, 0));

	void SetPosition(D3DXVECTOR2 position) { this->position = position; }
	D3DXVECTOR2 GetPosition() { return position; }
	D3DXVECTOR2* GetPPosition() { return &position; }

	void SetVelocity(D3DXVECTOR2 velocity) { this->velocity = velocity; }
	D3DXVECTOR2 GetVelocity() { return velocity; }
	void SetPosition(float x, float y) { this->position.x = x, this->position.y = y; }
	void SetSpeed(float vx, float vy) { this->velocity.x = vx, this->velocity.y = vy; }
	void GetPosition(float& x, float& y) { x = this->position.x; y = this->position.y; }
	void GetSpeed(float& vx, float& vy) { vx = this->velocity.x; vy = this->velocity.y; }


	int GetState() { return this->state; }
	virtual void Delete() { isDeleted = true; }
	bool IsDeleted() { return isDeleted; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;

	void RenderBoundingBox();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render();
	virtual void SetState(int state) { this->state = state; }
	//
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	//
	virtual int IsCollidable() { return 0; };
	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};
	virtual void IsCollidingWith(LPGAMEOBJECT e) {};

	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	// Is this object block all side or only top side ? 1 = All side, 2 = top side only
	virtual int IsBlocking() { return 0; }

	~CGameObject();
};

