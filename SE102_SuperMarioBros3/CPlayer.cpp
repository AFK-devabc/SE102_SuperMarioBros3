#include "CPlayer.h"
#include "Goomba.h"
#include "Brick.h"
#include "MushRoom.h"
#include "RedLeaf.h"
#include "Koopa.h"
#include "MarioTail.h"
#include "Portal.h"
#include "Coin.h"
#include "CheckPoint.h"
#include "WorldMap.h"

#include "GameObjectType.h"
#include "Scenes.h"
#include "PlayScene.h"
#include "CColorBox.h"
#include "Plant.h"
#include "PlantBullet.h"
#include "AddPoint.h"

int CPlayer::GetAniID()
{
	unsigned int aniID = 0;

	if (state == GAME_OBJECT_STATE_DIE)
	{
		return SMALL_MARIO_DEAD;
	}
	if (isChangingform)
	{
		return isChangingform;
	}
	if (koopaHolding != NULL)
	{
		aniID = MARIO_STATE_IDLE_HOLDING;
		if (velocity.x != NULL)
			aniID = MARIO_STATE_WALKING_HOLDING;
	}
	else if (GetTickCount64() - attack_start <= 200)
	{
		return CAT_MARIO_ATTACK;
	}
	else if (!isOnPlatform)
	{
		aniID = MARIO_STATE_JUMP;
		if (abs(velocity.x) > 0.9f * MARIO_RUNNING_SPEED)
			aniID = MARIO_STATE_Run_Jump;
		if (isFlying)
			aniID = MARIO_STATE_FLYING_DROPDOWN;

	}
	else if (isSitting)
	{
		if (marioType != SMALL_MARIO)
			aniID = MARIO_STATE_SIT;
	}
	else if (velocity.x == 0)
	{
		aniID = MARIO_STATE_IDLE;
	}
	else if (velocity.x != 0)
	{
		if (velocity.x * Ax < 0)
			aniID = MARIO_STATE_BRAKE;
		else if (abs(velocity.x) > 0.9f * MARIO_RUNNING_SPEED)
			aniID = MARIO_STATE_RUNNING;
		else if (abs(Ax) != 0)
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

void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if(!(!isOnPlatform && abs(velocity.x) >= MARIO_WALKING_SPEED && velocity.x * Ax > 0 )|| abs(velocity.x) >= 0.8 * MARIO_RUNNING_SPEED )
		velocity.x += Ax * dt;

	if (!(isFlying && velocity.y <= -1.4 * MARIO_FLY_DROPDOWN_SPEED))
		velocity.y += MARIO_GRAVITY * dt;
	isOnPlatform = 0;
	if (abs(velocity.x) > abs(maxVx))
		velocity.x = maxVx;
	//if (velocity.y  <=-2*MARIO_FLYING_DROPDOWN_SPEED)
	//	velocity.y = -2*MARIO_FLYING_DROPDOWN_SPEED;

	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME && untouchable)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (CanFlyUp)
	{
		if (GetTickCount64() - FlyUpStart > MARIO_FLYUP_TIME)

			CanFlyUp = false;

		if (velocity.x * Ax < 0)
			CanFlyUp = 0;
	}
	if (koopaHolding != NULL)
	{
		koopaHolding->SetPosition(this->position + D3DXVECTOR2(isLookingRight ? Small_Mario_Width : -Small_Mario_Width, 0));
	}
	if (isFlying)
	{
		if (velocity.y >= MARIO_FLYING_DROPDOWN_SPEED)
			velocity.y = MARIO_FLYING_DROPDOWN_SPEED;

		if (GetTickCount64() - flyingStart > MARIO_FLYING_TIME)
		{
			flyingStart = 0;
			isFlying = 0;
		}
	}
	else if (GetTickCount64() - attack_start > MARIO_DAMATE_TIME_START && isAttacking)
	{
		LPGAMEOBJECT marioTail = new CMarioTail(this->GetPosition() + D3DXVECTOR2(isLookingRight ? MARIO_TAIL_WIDTH : -MARIO_TAIL_WIDTH, 4.0f));
		CPlayScene* playscene = dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene());
		playscene->AddGameObject(marioTail);
		isAttacking = 0;

	}
	if (velocity.y >= 3 * MARIO_FLYING_DROPDOWN_SPEED)
		velocity.y = 3 * MARIO_FLYING_DROPDOWN_SPEED;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlayer::Render()
{
	string aniId = to_string(this->GetAniID());
	CAnimations* ani = CAnimations::GetInstance();
	if (!isLookingRight)
		aniId += "FlipX";
	ani->Get(aniId)->Render(position);

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
		if (e->ny < 0) {
			isOnPlatform = 1;
			CanFlyUp = true;
			FlyUpStart = GetTickCount64();
			isFlying = 0;
		}
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
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPlant*>(e->obj))
		OnCollisionWithPlant(e);
	else if (dynamic_cast<CPlantBullet*>(e->obj))
		OnCollisionWithPlantBullet(e);
	else if (dynamic_cast<CCheckPoint*>(e->obj))
		OnCollisionWithCheckPoint(e);


}

void CPlayer::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GAME_OBJECT_STATE_DIE)
		{
			int goombastate = goomba->GetState();
			LPGAMEOBJECT addPoint = new CAddPoint(e->obj->GetPosition(), 100);
			dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene())->AddGameObject(addPoint);

			switch (goombastate)
			{
			case GOOMBA_STATE_WING:
				goomba->SetState(GOOMBA_STATE_WALKING);

				break;
			case GOOMBA_STATE_WALKING:
				goomba->SetState(GAME_OBJECT_STATE_DIE);
				break;
			}
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
		if (e->nx != 0 && CanHoldKoopa)
		{
			koopaHolding = koopa;
			koopa->SetState(KOOPA_STATE_HOLDED);
		}
		else
		{
			int isGoingRight = 1;
			if (position.x > koopa->GetPPosition()->x)
				isGoingRight = 0;
			koopa->SetState(KOOPA_STATE_ROLLING, isGoingRight);
		}
	}
	// jump on top >> kill Goomba and deflect a bit 
	else if (e->ny < 0)
	{
		if (koopa->GetState() != GAME_OBJECT_STATE_DIE)
		{
			velocity.y = -MARIO_JUMP_DEFLECT_SPEED;
			LPGAMEOBJECT addPoint = new CAddPoint(e->obj->GetPosition(), 100);
			dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene())->AddGameObject(addPoint);

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
	else if (untouchable == 0)// hit by Goomba
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
	else
	{
		CHub::GetInstance()->AddLife(1);
	}
	LPGAMEOBJECT addPoint = new CAddPoint(e->obj->GetPosition(), 1000);
	dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene())->AddGameObject(addPoint);

}

void CPlayer::OnCollisionWithRedLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	LPGAMEOBJECT addPoint = new CAddPoint(e->obj->GetPosition(), 1000);
	dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene())->AddGameObject(addPoint);

	SetMarioType(CAT_MARIO);

}

void CPlayer::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* portal = dynamic_cast<CPortal*>(e->obj);
	CScenes::GetInstance()->InitiateSwitchScene(portal->GetNextScene());
}

void CPlayer::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	LPGAMEOBJECT addPoint = new CAddPoint(e->obj->GetPosition(), 50);
	dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene())->AddGameObject(addPoint);

	e->obj->Delete();

}

void CPlayer::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CPlant*>(e->obj)->IsDamage())
		this->Attacked();
}

void CPlayer::OnCollisionWithPlantBullet(LPCOLLISIONEVENT e)
{
	this->Attacked();
	e->obj->Delete();
}

void CPlayer::OnCollisionWithCheckPoint(LPCOLLISIONEVENT e)
{
	CKeyBoard::GetInstance()->Clear();
	SetState(MARIO_STATE_WALKING, 1);

	e->obj->Delete();
	CHub::GetInstance()->AddItems(e->obj->GetState());
	CWorldMap::GetInstance()->SetNodeComplete();
}

void CPlayer::Attacked()
{
	if (marioType == 100000)
	{

		SetState(GAME_OBJECT_STATE_DIE);
		CHub::GetInstance()->AddLife(-1);
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

	if (IsKeyDown(DIK_RIGHT))
	{
		isLookingRight = true;
		if (IsKeyDown(DIK_A))
			SetState(MARIO_STATE_RUNNING, 1);
		else
			SetState(MARIO_STATE_WALKING, 1);
	}
	else if (IsKeyDown(DIK_LEFT))
	{
		isLookingRight = false;
		if (IsKeyDown(DIK_A))
			SetState(MARIO_STATE_RUNNING, -1);
		else
			SetState(MARIO_STATE_WALKING, -1);
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
		if (!isOnPlatform && marioType == CAT_MARIO)
		{
			SetState(MARIO_STATE_FLYING_DROPDOWN);
			break;
		}
		SetState(MARIO_STATE_JUMP);
		break;
	case DIK_A:
		CanHoldKoopa = 1;
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
	case DIK_S:
		SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		if (marioType == SMALL_MARIO)
			return;
		SetState(MARIO_STATE_SIT_RELEASE);
		position = position + D3DXVECTOR2(0, (-Big_Mario_Height + Small_Mario_Height) / 2);
		break;
	case  DIK_A:
		CanHoldKoopa = 0;
		if (koopaHolding != NULL)
		{
			dynamic_cast<CKoopa*>(koopaHolding)->SetState(KOOPA_STATE_ROLLING, isLookingRight);
			koopaHolding = NULL;
		}
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
		if (isSitting)
			break;
		if (CanFlyUp)
			maxVx = MARIO_RUNNING_SPEED * (islookright ? 1 : -1);
		if (abs(velocity.x) > MARIO_WALKING_SPEED) {
			Ax = MARIO_ACCEL_RUN_X * (islookright ? 1 : -1);
			if (Ax * velocity.x < 0 || abs(velocity.x) < 0.5f * MARIO_WALKING_SPEED)
				Ax = 4 * Ax;

		}
		else {
			Ax = MARIO_ACCEL_WALK_X * (islookright ? 1 : -1);
			if (Ax * velocity.x < 0) Ax = 2 * Ax;
		}
		break;
	case MARIO_STATE_WALKING:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED * (islookright ? 1 : -1);
		Ax = MARIO_ACCEL_WALK_X * (islookright ? 1 : -1);

		if (Ax * velocity.x < 0 || abs(velocity.x) < 0.5f * MARIO_WALKING_SPEED)
			Ax = 2 * Ax;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->velocity.x) > MARIO_WALKING_SPEED)
				velocity.y = -MARIO_JUMP_RUN_SPEED_Y * (abs(velocity.x) - MARIO_WALKING_SPEED) - MARIO_JUMP_SPEED_Y;
			else
				velocity.y = -MARIO_JUMP_SPEED_Y;
		}
		break;
	case MARIO_STATE_FLYING_DROPDOWN:
	{
		if (abs(velocity.x) == abs(MARIO_RUNNING_SPEED) && CanFlyUp)
		{
			velocity.y = -1.6 * MARIO_FLY_DROPDOWN_SPEED;
			isFlyingUp = true;
		}
		else 		if (velocity.y > 0)
			velocity.y = MARIO_FLY_DROPDOWN_SPEED;

		flyingStart = GetTickCount64();
		isFlying = 1;
		break;
	}
	case MARIO_STATE_RELEASE_JUMP:

		if (velocity.y < 0 && !isFlying)
		{
			velocity.y += MARIO_JUMP_SPEED_Y / 2;
		}
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && marioType != SMALL_MARIO)
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
		velocity.y = -MARIO_JUMP_DEFLECT_SPEED * 2;
		velocity.x = 0;
		Ax = 0;
		break;

	}
	this->state = state;

}

void CPlayer::SetMarioType(int type, bool isPause)
{
	if (isPause) {
		CScenes::GetInstance()->GetCurrentScene()->SetPause(1000);
		isChangingform = -(type)-marioType;
	}
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