#include "KoopaEdgeDetect.h"

void CKoopaEdgeDetect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - 2 / 2;
	t = position.y - 2 / 2;
	r = l + 2;
	b = t + 2;

}

void CKoopaEdgeDetect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	velocity.y += GRAVITY * dt;
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
}
