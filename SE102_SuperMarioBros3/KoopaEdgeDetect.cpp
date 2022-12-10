#include "KoopaEdgeDetect.h"
#include "DefineInfo.h"

void CKoopaEdgeDetect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - BRICK_WIDTH / 2;
	t = position.y - BRICK_HEIGHT / 2;
	r = l + BRICK_WIDTH;
	b = t + BRICK_HEIGHT;

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
