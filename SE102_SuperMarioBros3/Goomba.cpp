#include "Goomba.h"
#include "DefineInfo.h"

void CGoomba::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	l = position.x - 16 / 2;
	t = position.y - 16 / 2;
	r = l + 16;
	b = t + 16;
	if (state == GAME_OBJECT_STATE_DIE)
	{
		r = l + 16 / 2;
		b = t + 16 / 2;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	isOnPlatform = false;
	velocity.y += MARIO_GRAVITY * dt;

	if ((state == GAME_OBJECT_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}


	CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CGoomba::Render()
{
	CAnimations* ani = CAnimations::GetInstance();
	ani->Get("20000")->Render(position);
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

}
