#include "CPlayer.h"

void CPlayer::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - 16 / 2;
	t = position.y - 16 / 2;
	r = l + 16;
	b = t + 16;

}

void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects )
{

	velocity.x += Ax * dt;
	velocity.y += MARIO_GRAVITY * dt;
	isOnPlatform = false;

	if (abs(velocity.x) > abs(maxVx))
		velocity.x = maxVx;


	CCollision::GetInstance()->Process(this, dt, coObjects);


	//if (abs(velocity.x) > abs(maxVx))
	//	velocity.x = maxVx;
	//position += velocity * dt;

	//if (position.y > GROUND_Y)
	//{
	//	velocity.y = 0; 
	//	position.y = GROUND_Y;
	//}
}

void CPlayer::Render()
{
	CAnimations* ani = CAnimations::GetInstance();
	ani->Get("12000")->Render(position);
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

}

void CPlayer::KeyState(BYTE* state)
{
	this->keyStates = state;
	if (IsKeyDown(DIK_RIGHT))
	{
		if (IsKeyDown(DIK_A))
			SetState(MARIO_STATE_RUNNING, 1);
		else
			SetState(MARIO_STATE_WALKING,1);
	}
	else if (IsKeyDown(DIK_LEFT))
	{
		if (IsKeyDown(DIK_A))
			SetState(MARIO_STATE_RUNNING,-1);
		else
			SetState(MARIO_STATE_WALKING,-1);
	}
	else
		SetState(MARIO_STATE_IDLE);

	// Sitting state has higher priority 
	if (IsKeyDown(DIK_DOWN))
	{
		SetState(MARIO_STATE_SIT);
	}

}

void CPlayer::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_S:
		SetState(MARIO_STATE_JUMP);
		break;
	}
}

void CPlayer::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_S:
		SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		SetState(MARIO_STATE_SIT_RELEASE);
		break;
	}

}

void CPlayer::SetState(int state, int islookright)
{
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
	}

}
