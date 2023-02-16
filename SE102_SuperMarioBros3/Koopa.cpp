#include "Koopa.h"
#include "Goomba.h"
#include "Brick.h"
#include "AddPoint.h"
#include "PlayScene.h"

void CKoopa::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	l = position.x - KOOPA_SHEILD_WIDTH / 2;
	t = position.y - KOOPA_SHEILD_HEIGHT / 2;
	r = l + KOOPA_SHEILD_WIDTH;
	b = t + KOOPA_SHEILD_HEIGHT;
	if (state == KOOPA_STATE_WALKING || state == KOOPA_STATE_WING)
	{
		t = position.y - KOOPA_NORMAL_HEIGHT / 2;
		b = t + KOOPA_NORMAL_HEIGHT ;
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
	if (velocity.y <= -KOOPA_JUMP_DEFLECT_SPEED)
		velocity.y = -KOOPA_JUMP_DEFLECT_SPEED;
	if ((state == GAME_OBJECT_STATE_DIE))
	{
		isDeleted = true;
		return;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (state == KOOPA_STATE_WING && isOnPlatform)
	{
		velocity.y = -KOOPA_JUMP_DEFLECT_SPEED;

	}


}

void CKoopa::Render()
{
	string aniId = to_string(state);

	if (!isLookingRight)
		aniId += "FlipX";
	CAnimations* ani = CAnimations::GetInstance();
	ani->Get(aniId)->Render(position);


}

void CKoopa::OnNoCollision(DWORD dt)
{
	position += velocity * dt;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		velocity.y = 0;
		if (e->ny < 0) isOnPlatform = true;

	}



	if (e->nx != 0 && e->obj->IsBlocking())
	{
		velocity.x = -velocity.x;
		isLookingRight = !isLookingRight;
	}

	if (this->GetState() == KOOPA_STATE_ROLLING &&(e->nx !=0))
	{
		if (dynamic_cast<CGoomba*>(e->obj))
			OnCollisionWithGoomba(e);
		else if (dynamic_cast<CKoopa*>(e->obj))
			OnCollisionWithKoopa(e);
		else if (dynamic_cast<CBrick*>(e->obj))
			OnCollisionWithBrick(e);
		else if (dynamic_cast<CPlant*>(e->obj))
			OnCollisionWithPlant(e);
		else if (dynamic_cast<CItemContainer*>(e->obj))
			OnCollisionWithItemContainer(e);

	}
}

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	goomba->SetState(GOOMBA_STATE_ATTACKED);
	LPGAMEOBJECT addPoint = new CAddPoint(e->obj->GetPosition(), 100);
	dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene())->AddGameObject(addPoint);

}

void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	if (koopa->GetState() == KOOPA_STATE_INSIDE_SHELL)
	{
		this->velocity.x = -this->velocity.x;
		koopa->SetState(KOOPA_STATE_ROLLING);
	}
	else if(koopa->GetState() != KOOPA_STATE_ROLLING)
	{
		koopa->SetSpeed(0, -KOOPA_JUMP_DEFLECT_SPEED);
		koopa->SetState(KOOPA_STATE_INSIDE_SHELL);
		LPGAMEOBJECT addPoint = new CAddPoint(e->obj->GetPosition(), 100);
		dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene())->AddGameObject(addPoint);
	}
}

void CKoopa::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
}

void CKoopa::OnCollisionWithPlant(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	LPGAMEOBJECT addPoint = new CAddPoint(e->obj->GetPosition(), 100);
	dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene())->AddGameObject(addPoint);

}

void CKoopa::OnCollisionWithItemContainer(LPCOLLISIONEVENT e)
{
	e->obj->SetState(OBJECT_TYPE_EMPTY_BLOCK);
}

void CKoopa::SetState(int state, int isGoingRight)
{
	this->state = state;
	this->position.y += -1.0f;
	switch (state)
	{
	case KOOPA_STATE_WING:
	case KOOPA_STATE_WALKING:
		this->velocity.x = KOOPA_WALKING_SPEED * (isGoingRight ? 1 : -1);
		break;
	case KOOPA_STATE_ESCAPE_SHELL:
		escapeShellStart = GetTickCount64();
		break;
	case KOOPA_STATE_ROLLING:
		this->velocity.x = KOOPA_ROLLING_SPEED * (isGoingRight ? 1 : -1);
		break;
	case KOOPA_STATE_INSIDE_SHELL :
		insideShellStart = GetTickCount64();
		this->velocity.x = 0;
		break;
	default:
		break;
	}
}

