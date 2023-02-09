#include "Brick.h"
#include "Animations.h"
#include "PlayScene.h"
#include "RedLeaf.h"
#include "BrickBroken.h"
#include "CoinDrop.h"

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - BRICK_WIDTH / 2;
	t = position.y - BRICK_HEIGHT / 2;
	r = l + BRICK_WIDTH;
	b = t + BRICK_WIDTH;
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (state == BRICK_STATE_PUSHED)
	{
		velocity.y += GRAVITY * dt;

		position = position + velocity * dt;

		if (position.y > initialposition.y)
		{
			velocity.y = 0;
			position = initialposition;
			state = BRICK_STATE_IDLE;
		}
	}
	else if (state == BRICK_STATE_CHANGED_INTO_COIN)
	{
		if (GetTickCount64() - startChangeToCoin > BRICK_COIN_TIME_LAST)
			SetState(BRICK_STATE_IDLE);
	}
}



void CBrick::Render()
{
	switch (state)
	{
	case BRICK_STATE_CHANGED_INTO_COIN:
		CAnimations::GetInstance()->Get(to_string(OBJECT_TYPE_COIN))->Render(position);
		break;
	default:
		CAnimations::GetInstance()->Get(to_string(BRICK_STATE_IDLE))->Render(position);
	}
}

void CBrick::Delete()
{
	if (state != BRICK_STATE_CHANGED_INTO_COIN)
	{
		LPGAMEOBJECT effect = new CBrickBroken(this->position);
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene());
		p->AddGameObject(effect);
	}
	this->isDeleted = true;
}

void CBrick::SetState(int state)
{
	this->state = state;
	if (state == BRICK_STATE_PUSHED)
		velocity = D3DXVECTOR2(0,-BRICK_DEFLECT_SPEED);
	else if (state == BRICK_STATE_CHANGED_INTO_COIN)
	{
		startChangeToCoin = GetTickCount64();
	}
}

