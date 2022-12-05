#include "KoopaEdgeDetect.h"
#include "DefineInfo.h"

void CKoopaEdgeDetect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - 16 / 2;
	t = position.y - 16 / 2;
	r = l + 16;
	b = t + 16;

}

void CKoopaEdgeDetect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	velocity.y += MARIO_GRAVITY * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CKoopaEdgeDetect::OnNoCollision(DWORD dt)
{
	position += velocity * dt;

}

void CKoopaEdgeDetect::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		velocity.y = 0;

	}

	if (e->nx != 0 && e->obj->IsBlocking())
	{
		velocity.x = -velocity.x;
	}
	RenderBoundingBox();

}
