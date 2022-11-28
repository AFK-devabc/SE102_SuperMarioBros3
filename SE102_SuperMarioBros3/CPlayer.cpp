#include "CPlayer.h"
#include "Goomba.h"
#include "Brick.h"
#include "MushRoom.h"
#include "RedLeaf.h"
#include "Koopa.h"
#include "MarioTail.h"

#include "GameObjectType.h"
#include "Scenes.h"
#include "PlayScene.h"
#include "CColorBox.h"


 int CPlayer::GetAniID()
{
	unsigned int aniID = 0;

	if (isChangingform)
	{
		return isChangingform;
	}

	if (!isOnPlatform)
	{
			aniID = MARIO_STATE_JUMP;
			if (abs( velocity.x) >  MARIO_WALKING_SPEED)
				aniID = MARIO_STATE_Run_Jump;
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
	switch (marioType)
	{
	case CAT_MARIO:
	case BIG_MARIO:
		if (isSitting)
		{
			l = position.x - Small_Mario_Width / 2;
			t = position.y - Small_Mario_Height / 2;
			r = l + Small_Mario_Width;
			b = t + Small_Mario_Height;
		}
		else
		{
			l = position.x - Small_Mario_Width / 2;
			t = position.y - Big_Mario_Height / 2;
			r = l + Small_Mario_Width;
			b = t + Big_Mario_Height;
		}
		break;
	case SMALL_MARIO:
		l = position.x - Small_Mario_Width / 2;
		t = position.y - Small_Mario_Height / 2;
		r = l + Small_Mario_Width;
		b = t + Small_Mario_Height;
		break;
	default:
		break;
	}
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
	if (GetTickCount64() - attack_start > MARIO_DAMATE_TIME_START && isAttacking)
	{
		LPGAMEOBJECT marioTail = new CMarioTail(this->GetPosition()  + D3DXVECTOR2(isLookingRight? 16.0f: -16.0f,0));
		CPlayScene* playscene = dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene());
		playscene->AddGameObject(marioTail);
		isAttacking = 0;

	}
	CCollision::GetInstance()->Process(this, dt, coObjects);

	//if (position.y >= 185)
	//{
	//	isOnPlatform = true;
	//	position.y = 185;
	//	velocity.y = 0;
	//}
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
	if (e->ny != 0 && e->obj->IsBlocking() )
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
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CMushRoom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CRedLeaf*>(e->obj))
		OnCollisionWithRedLeaf(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	//else if (dynamic_cast<CColorBox*>(e->obj))
	//	OnCollisionWithColorBox(e);


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
				Attacked();
		}
	}

}

void CPlayer::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (koopa->GetState() == KOOPA_STATE_INSIDE_SHELL)
	{
		int isGoingRight = 0;
		if (position.x > koopa->GetPPosition()->x)
			isGoingRight = 1;
		koopa->SetState(KOOPA_STATE_ROLLING);
		
		return;
	}

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (koopa->GetState() != GAME_OBJECT_STATE_DIE)
		{
			velocity.y = -MARIO_JUMP_DEFLECT_SPEED;

			switch (koopa->GetState())
			{
			case KOOPA_STATE_WING:
				koopa->SetState(KOOPA_STATE_WALKING);
				break;
			case KOOPA_STATE_WALKING:
				koopa->SetState(KOOPA_STATE_INSIDE_SHELL);
				break;
			case KOOPA_STATE_ROLLING:
				koopa->SetState(KOOPA_STATE_INSIDE_SHELL);
				break;
			default:
				break;
			}
		}
		
	}
	else if (untouchable == 0 && e->nx !=0)// hit by Goomba
	{
		if (koopa->GetState() != GAME_OBJECT_STATE_DIE && koopa->GetState() != KOOPA_STATE_INSIDE_SHELL)
			Attacked();
	}

}

void CPlayer::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	if (e->ny > 0) 
	{
		brick->Hit(1);
	}
	else if (e->ny < 0 && brick->GetBehavior() == OBJECT_TYPE_MUSIC_NOTE)
	{
		velocity.y = -MARIO_JUMP_DEFLECT_SPEED;
		brick->Hit(2);
	}
}

void CPlayer::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	if (marioType == SMALL_MARIO)
	{
		SetMarioType(BIG_MARIO);
	}
}

void CPlayer::OnCollisionWithRedLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();

	SetMarioType(CAT_MARIO);

}

//void CPlayer::OnCollisionWithColorBox(LPCOLLISIONEVENT e)
//{
//	if (e->ny < 0) 
//	{
//		position.x += velocity.x;
//		//position.y += e->t * velocity.y + e->ny * BLOCK_PUSH_FACTOR;
//		velocity.y = 0;
//		isOnPlatform = true;
//
//	}
//}


void CPlayer::Attacked()
{
	if (marioType == 100000)
	{

		SetState(GAME_OBJECT_STATE_DIE);
		return;
	}
	else
	{
		SetMarioType(marioType - 10000);

		StartUntouchable();
	}
	DebugOut(L"\n<<<Mario Hitted>>>");

}

void CPlayer::KeyState(BYTE* state)
{
	this->keyStates = state;

	if (isChangingform)
		return;

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
	case DIK_J:
		if (marioType == CAT_MARIO)
		{
			isAttacking = true;
			attack_start = GetTickCount64();
		}
		break;

	case DIK_1:
		SetMarioType(SMALL_MARIO);
		break;
	case DIK_2:
		SetMarioType(BIG_MARIO);
		break;
	case DIK_3:
		SetMarioType(CAT_MARIO);
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
		position = position + D3DXVECTOR2(0, (-Big_Mario_Height + Small_Mario_Height) / 2);
		break;
	}

}

void CPlayer::SetState(int state, int islookright)
{
	if (this->state == GAME_OBJECT_STATE_DIE) return;
	
	this->state = state;


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

}

void CPlayer::SetMarioType( int type)
{
	isChangingform = -(type) - marioType;
	CScenes::GetInstance()->GetCurrentScene()->SetPause(1000);

	switch (type)
	{
	case BIG_MARIO:
	case CAT_MARIO:
		position = position + D3DXVECTOR2(0, (-Big_Mario_Height + Small_Mario_Height) / 2);
		break;
	default:
		break;
	}
	marioType = type;

}