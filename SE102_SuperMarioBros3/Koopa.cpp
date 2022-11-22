#include "Koopa.h"
#include "DefineInfo.h"
#include "GameObjectType.h"

void CKoopa::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	l = position.x - 16 / 2;
	t = position.y - 16 / 2;
	r = l + 16;
	b = t + 16;
	if (state == KOOPA_STATE_WALKING)
	{
		t = position.y - 26 / 2;
		b = t + 26 ;
	}

}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	isOnPlatform = false;
	velocity.y += MARIO_GRAVITY * dt;

	if ((state == GAME_OBJECT_STATE_DIE))
	{
		isDeleted = true;
		return;
	}


	CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CKoopa::Render()
{
	CAnimations* ani = CAnimations::GetInstance();
	ani->Get(to_string(state))->Render(position);
	RenderBoundingBox();
}

void CKoopa::OnNoCollision(DWORD dt)
{
	position += velocity * dt;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		velocity.y = 0;
		if (e->ny < 0) isOnPlatform = true;

	}

	if (e->nx != 0 && e->obj->IsBlocking())
	{
		velocity.x = -velocity.x;
		isLookingRight = !isLookingRight;
	}
}

void CKoopa::SetState(int state, int isGoingRight)
{
	this->state = state;
	this->position.y += -1.0f;
	switch (state)
	{
	case KOOPA_STATE_ROLLING:
		this->velocity.x = 0.2f * (isGoingRight ? 1 : -1);
		break;
	case KOOPA_STATE_INSIDE_SHELL :
		this->velocity.x = 0;
		break;
	default:
		break;
	}
}
