#include "RedKoopa.h"

void CRedKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == KOOPA_STATE_HOLDED)
		return;

	if (state == KOOPA_STATE_INSIDE_SHELL)
		if (GetTickCount64() - insideShellStart > KOOPA_TOTAL_INSDE_SHELLTIME)
			SetState(KOOPA_STATE_ESCAPE_SHELL, !isLookingRight);

	if (state == KOOPA_STATE_ESCAPE_SHELL)
		if (GetTickCount64() - escapeShellStart > KOOPA_TOTAL_INSDE_SHELLTIME)
		{
			SetState(KOOPA_STATE_WALKING, !isLookingRight);
			this->position.y -= KOOPA_NORMAL_HEIGHT - KOOPA_SHEILD_HEIGHT;
		}
	isOnPlatform = false;
	velocity.y += GRAVITY * dt;

	if ((state == GAME_OBJECT_STATE_DIE))
	{
		isDeleted = true;
		return;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
	if (this->state == KOOPA_STATE_WALKING)
	{
		if (edgeDetect->GetPosition().y > position.y + 14.0f)
		{
			isLookingRight = !isLookingRight;
			edgeDetect->SetPosition(this->position.x + (isLookingRight ? 16.0f : -16.0f), this->position.y);
			this->velocity.x = -this->velocity.x;
		}
		else
			edgeDetect->SetPosition(this->position.x + (isLookingRight ? -16.0f : 16.0f), edgeDetect->GetPosition().y);
	}
}

void CRedKoopa::Render()
{
	string aniId = to_string(state + 1);

	if (!isLookingRight)
		aniId += "FlipX";
	CAnimations* ani = CAnimations::GetInstance();
	ani->Get(aniId)->Render(position);

}
