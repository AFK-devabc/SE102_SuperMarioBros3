#include "MarioTail.h"
#include "GameObject.h"
#include "CPlayer.h"
void CMarioTail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - 16 / 2;
	t = position.y - 8 / 2;
	r = l + 16;
	b = t + 8;

}

void CMarioTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CCollision::GetInstance()->ProcessIsColliding(this, dt, coObjects);
	if(GetTickCount64() - startTime> 100)

	this->Delete();
}

void CMarioTail::Render()
{
	RenderBoundingBox();
}

void CMarioTail::IsCollidingWith(LPGAMEOBJECT e)
{
	if (! (dynamic_cast<CPlayer*>(e)))
		e->Attacked();
}

