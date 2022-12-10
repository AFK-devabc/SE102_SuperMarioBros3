#include "RedLeaf.h"
#include "Animations.h"
#include "DefineInfo.h"
#include "GameObjectType.h"

void CRedLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - 14 / 2;
	t = position.y - 14 / 2;
	r = l + 14;
	b = t + 14;
}

void CRedLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == REDLEAF_STATE_IDLE)
	{
		if (abs(startY - position.y) > 50.0f)
		{
			state = REDLEAF_STATE_DROPPING;
			velocity.y = 0.03f;
			velocity.x = 0.05f;
		}
	}
	else if (state == REDLEAF_STATE_DROPPING)
	{
		if (abs(position.x - startX) >= 24.0f)
		{
			velocity.x = -velocity.x;
			isLookingRight = !isLookingRight;
		}

	}
	position += velocity * dt;

}


void CRedLeaf::Render()
{
	CAnimations::GetInstance()->Get(to_string(REDLEAF_STATE_IDLE))->Render(position, isLookingRight);
}



void CRedLeaf::Hit(int type)
{
}
