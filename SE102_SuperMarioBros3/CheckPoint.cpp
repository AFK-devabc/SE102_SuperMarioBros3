#include "CheckPoint.h"

void CCheckPoint::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - 16 / 2;
	t = position.y - 16 / 2;
	r = l + 16;
	b = t + 16;

}

void CCheckPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isChecked)
	{
		position += velocity * dt;
	}
	else
	{


		tickCount -= dt;
		if (tickCount < 0)
		{
			tickCount = CHECKPOINT_SWAPTIME;
			switch (state)
			{
			case CHECKPOINT_FLOWER:
				state = CHECKPOINT_STAR;
				break;
			case CHECKPOINT_STAR:
				state = CHECKPOINT_MUSHROOM;
				break;
			case CHECKPOINT_MUSHROOM:
				state = CHECKPOINT_FLOWER;
				break;
			default:
				state = CHECKPOINT_STAR;
				break;
			}
		}
	}
}

void CCheckPoint::Render()
{
	CAnimations::GetInstance()->Get(to_string(state))->Render(position);
}

void CCheckPoint::Check()
{
	if (!isChecked)
	{
		checkpointBlock->Delete();
		isChecked = true;
		this->velocity = D3DXVECTOR2(0, -BRICK_DEFLECT_SPEED);
	}
}
