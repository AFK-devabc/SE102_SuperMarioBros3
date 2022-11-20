#include "MushRoom.h"
#include "Animations.h"
#include "DefineInfo.h"
#include "GameObjectType.h"

void CMushRoom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - 16 / 2;
	t = position.y - 16 / 2;
	r = l + 16;
	b = t + 16;
}

void CMushRoom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == MUSHROOM_STATE_INSIDE)
	{
		position += velocity * dt;
		if (startY - position.y > 17.0f)
		{
			state = MUSHROOM_STATE_OUTSIDE;
			velocity.x = 0.05f;
			
		}
	}
	else if(state == MUSHROOM_STATE_OUTSIDE)
	{
		velocity.y += MARIO_GRAVITY * dt;

		CCollision::GetInstance()->Process(this, dt, coObjects);

	}

	

}


void CMushRoom::Render()
{
		CAnimations::GetInstance()->Get(to_string(OBJECT_TYPE_MUSHROOM))->Render(position);
		RenderBoundingBox();
}

void CMushRoom::OnNoCollision(DWORD dt)
{
	position += velocity * dt;
}

void CMushRoom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		velocity.y = 0;

	}

	if (e->nx != 0 && e->obj->IsBlocking())
	{
		velocity.x = -velocity.x;
	}

}


void CMushRoom::SetState(int state, int islookright)
{
}

void CMushRoom::Hit(int type)
{
}
