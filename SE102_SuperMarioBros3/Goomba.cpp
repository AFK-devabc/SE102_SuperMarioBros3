#include "Goomba.h"
#include "DefineInfo.h"
#include "GameObjectType.h"

void CGoomba::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	l = position.x - GOOMBA_WIDTH / 2;
	t = position.y - GOOMBA_HEIGHT / 2;
	r = l + GOOMBA_WIDTH;
	b = t + GOOMBA_HEIGHT;
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (state == GAME_OBJECT_STATE_DIE) 
	{
		if(GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT)
				isDeleted = true;
	}
	else if (state == GAME_OBJECT_STATE_HITTED)
	{
		if (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT)
			isDeleted = true;
		OnNoCollision(dt);
	}
	else
	{
		velocity.y += GRAVITY * dt;
		isOnPlatform = false;
		CCollision::GetInstance()->Process(this, dt, coObjects);

	}



}

void CGoomba::Render()
{
	CAnimations* ani = CAnimations::GetInstance();
	if (state == GAME_OBJECT_STATE_DIE)
	{
		ani->Get(to_string(GOOMBA_STATE_DYING))->Render(position);
		return;
	}
	ani->Get(to_string(GOOMBA_STATE_WALKING))->Render(position);

}

void CGoomba::OnNoCollision(DWORD dt)
{
	position += velocity * dt;
}

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		velocity.y = 0;
		if (e->ny < 0) isOnPlatform = true;

	}

	if (e->nx != 0 && e->obj->IsBlocking())
	{
		velocity.x =  - velocity.x;
	}
}

void CGoomba::SetState(int state, int islookright)
{
	this->state = state;
	if(state != GOOMBA_STATE_WALKING)
		die_start = GetTickCount64();
	this->position.y = position.y + GOOMBA_HEIGHT / 2;
}
