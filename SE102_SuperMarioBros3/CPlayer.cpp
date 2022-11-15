#include "CPlayer.h"
#include "Goomba.h"

unsigned int CPlayer::GetAniID()
{
	unsigned int aniID = 0;

	if (!isOnPlatform)
	{
			aniID = MARIO_STATE_JUMP;
	}
	else
		if (isSitting)
		{
			if (marioType != SMALL_MARIO)
				aniID = MARIO_STATE_SIT;
		}
		else
			if (velocity.x == 0)
			{
				aniID = MARIO_STATE_IDLE;
			}
			else if (velocity.x != 0)
			{
				if (velocity.x * Ax < 0)
					aniID = MARIO_STATE_BRAKE;
				else if (abs(Ax) == MARIO_ACCEL_RUN_X)
					aniID = MARIO_STATE_RUNNING;
				else if (abs(Ax) == MARIO_ACCEL_WALK_X)
					aniID = MARIO_STATE_WALKING;
					
			}


	return aniID + marioType;
}

void CPlayer::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - 16 / 2;
	t = position.y - 26 / 2;
	r = l + 16;
	b = t + 26;

}

void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects )
{

	velocity.x += Ax * dt;
	velocity.y += MARIO_GRAVITY * dt;
	isOnPlatform = false;

	if (abs(velocity.x) > abs(maxVx))
		velocity.x = maxVx;

	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlayer::Render()
{
	string aniId = to_string(this->GetAniID());
	CAnimations* ani = CAnimations::GetInstance();
	ani->Get(aniId)->Render(position, !isLookingRight);

	RenderBoundingBox();
}

void CPlayer::OnNoCollision(DWORD dt)
{
	position += velocity * dt;
}

void CPlayer::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		velocity.y = 0;
		if (e->ny < 0) isOnPlatform = true;
	}

	if (e->nx != 0 && e->obj->IsBlocking())
	{
		velocity.x = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);

}

void CPlayer::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GAME_OBJECT_STATE_DIE)
		{
			goomba->SetState(GAME_OBJECT_STATE_DIE);
			velocity.y = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GAME_OBJECT_STATE_DIE)
			{
				//if (level > MARIO_LEVEL_SMALL)
				//{
				//	level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				//}
				//else
				//{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(GAME_OBJECT_STATE_DIE);
				//}
			}
		}
	}

}

void CPlayer::KeyState(BYTE* state)
{
	this->keyStates = state;
	if (IsKeyDown(DIK_D))
	{
		isLookingRight = true;
		if (IsKeyDown(DIK_J))
			SetState(MARIO_STATE_RUNNING, 1);
		else
			SetState(MARIO_STATE_WALKING,1);
	}
	else if (IsKeyDown(DIK_A))
	{
		isLookingRight = false;
		if (IsKeyDown(DIK_J))
			SetState(MARIO_STATE_RUNNING,-1);
		else
			SetState(MARIO_STATE_WALKING,-1);
	}
	else
		SetState(MARIO_STATE_IDLE);

	// Sitting state has higher priority 
	if (IsKeyDown(DIK_S))
	{
		SetState(MARIO_STATE_SIT);
	}

}

void CPlayer::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_K:
		SetState(MARIO_STATE_JUMP);
		break;
	}
}

void CPlayer::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_K:
		SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_S:
		SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}

}

void CPlayer::SetState(int state, int islookright)
{
	if (this->state == GAME_OBJECT_STATE_DIE) return;

	if (islookright > 0)
		isLookingRight = true;
	else if (islookright < 0)
		islookright = false;

	switch (state)
	{
	case MARIO_STATE_RUNNING:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED * (islookright ? 1 : -1);
		Ax = MARIO_ACCEL_RUN_X * (islookright? 1:-1);
		break;
	case MARIO_STATE_WALKING:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED * (islookright ? 1 : -1);
		Ax = MARIO_ACCEL_WALK_X * (islookright ? 1 : -1);
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->velocity.x) == MARIO_RUNNING_SPEED)
				velocity.y = -MARIO_JUMP_RUN_SPEED_Y;
			else
				velocity.y = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (velocity.y < 0) 
			velocity.y += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			velocity.x = velocity.y = 0;
			//y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		isSitting = false;
		state = MARIO_STATE_IDLE;
		//y -= MARIO_SIT_HEIGHT_ADJUST;
		break;

	case MARIO_STATE_IDLE:
		Ax = 0.0f;
		velocity.x = 0.0f;
		break;
	case GAME_OBJECT_STATE_DIE:
		velocity.y = -MARIO_JUMP_DEFLECT_SPEED;
		velocity.x = 0;
		Ax = 0;
		break;

	}

	this->state = state;


}
