#include "Brick.h"
#include "Animations.h"
#include "DefineInfo.h"

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - 16 / 2;
	t = position.y - 16 / 2;
	r = l + 16;
	b = t + 16;
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (hitted == 1)
	{
		velocity.y = velocity.y + 2*MARIO_GRAVITY*dt;

		position = position + velocity * dt;

		if (position.y > initialposition.y)
		{
			velocity.y = 0;
			hitted = 0;
			position = initialposition;
		}
	}
	if (hitted == 2)
	{
		velocity.y = velocity.y - 2 * MARIO_GRAVITY * dt;

		position = position + velocity * dt;

		if (position.y < initialposition.y)
		{
			velocity.y = 0;
			hitted = 0;
			position = initialposition;
		}
	}

}


void CBrick::Render()
{
	switch ( behavior)
	{
	case Question_Mark_IDLE:
		CAnimations::GetInstance()->Get(to_string(Question_Mark_IDLE))->Render(position);
		break;
	case Yellow_Brick_IDLE:
		CAnimations::GetInstance()->Get(to_string(Yellow_Brick_IDLE))->Render(position);
		break;
	case Music_Note_IDLE:
		CAnimations::GetInstance()->Get(to_string(Music_Note_IDLE))->Render(position);
		break;

	default:
		break;
	}
}


void CBrick::SetState(int state, int islookright)
{
}

void CBrick::Hit(int type)
{
	if (!hitted)
	{
		hitted = type;
		velocity = D3DXVECTOR2(0, -MARIO_JUMP_DEFLECT_SPEED);
		if (behavior == Music_Note_IDLE && type == 2)
				velocity = D3DXVECTOR2(0, MARIO_JUMP_DEFLECT_SPEED);
	}
}
