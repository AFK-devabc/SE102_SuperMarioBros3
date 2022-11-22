#include "RedKoopa.h"

void CRedKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	isOnPlatform = false;
	velocity.y += MARIO_GRAVITY * dt;

	if ((state == GAME_OBJECT_STATE_DIE))
	{
		isDeleted = true;
		return;
	}


	CCollision::GetInstance()->Process(this, dt, coObjects);
	if (this->state == KOOPA_STATE_WALKING)
	{
		if (edgeDetect->GetPosition().y > position.y + 16.0f)
		{
			isLookingRight = !isLookingRight;
			edgeDetect->SetPosition(this->position.x + (isLookingRight ? 16.0f : -16.0f), this->position.y);
			this->velocity.x = -this->velocity.x;
		}
		else
			edgeDetect->SetPosition(this->position.x + (isLookingRight ? 16.0f : -16.0f), edgeDetect->GetPosition().y);
	}
}
