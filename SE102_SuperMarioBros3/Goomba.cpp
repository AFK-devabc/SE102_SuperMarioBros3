#include "Goomba.h"
#include "Scenes.h"
#include "PlayScene.h"

void CGoomba::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	l = position.x - GOOMBA_WIDTH / 2;
	t = position.y - GOOMBA_HEIGHT / 2;
	r = l + GOOMBA_WIDTH;
	b = t + GOOMBA_HEIGHT;

	if (state == GOOMBA_STATE_WING)
	{
		b = b + 5;
		t = t + 5;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == GAME_OBJECT_STATE_DIE) 
	{
		if(GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT)
				isDeleted = true;
	}
	else
	{
		velocity.y += GRAVITY * dt;
		isOnPlatform = false;

		if (type == 1)
		{
			D3DXVECTOR2 playerPosition = dynamic_cast<CPlayScene*>(CScenes::GetInstance()
				->GetCurrentScene())->GetPlayer()->GetPosition();

			if(abs(playerPosition.x - position.x) >50.0f)
				velocity.x = position.x < playerPosition.x ? Goomba_Walking_Speed : -Goomba_Walking_Speed;
		}
		CCollision::GetInstance()->Process(this, dt, coObjects);
		if (state == GOOMBA_STATE_WING && isOnPlatform)
		{
			if (GetTickCount64() - jumpstart > GOOMBA_JUMP_DELAY)
			{
				velocity.y = -KOOPA_JUMP_DEFLECT_SPEED;
				jumpstart = GetTickCount64();
			}
		}
	}
}

void CGoomba::Render()
{
	CAnimations* ani = CAnimations::GetInstance();
	if (state == GAME_OBJECT_STATE_DIE)
	{
		ani->Get(to_string(GOOMBA_STATE_DYING + type))->Render(position);
	}
	else
		ani->Get(to_string(state + type))->Render(position);

}

void CGoomba::OnNoCollision(DWORD dt)
{
	position += velocity * dt;
}

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		velocity.y = 0;
		if (e->ny < 0) isOnPlatform = true;

	}

	if (e->nx != 0 && e->obj->IsBlocking())
	{
		velocity.x =  - velocity.x;
	}
}

void CGoomba::SetState(int state, int islookright)
{
	this->state = state;
	this->isLookingRight = islookright;
	switch (state)
	{
	case GOOMBA_STATE_WING:
	case GOOMBA_STATE_WALKING:
		this->velocity = D3DXVECTOR2(Goomba_Walking_Speed * (islookright ? 1:-1), 0);
		break;
	case GAME_OBJECT_STATE_DIE:
		die_start = GetTickCount64();
		//this->position.y = position.y + GOOMBA_HEIGHT / 2;
		this->velocity = D3DXVECTOR2(0, 0);
		break;
	default:
		break;
	}
}
