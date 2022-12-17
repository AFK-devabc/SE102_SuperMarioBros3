#include "Koopa.h"
#include "DefineInfo.h"
#include "GameObjectType.h"
#include "Goomba.h"
#include "Brick.h"

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

	isOnPlatform = false;
	velocity.y += GRAVITY * dt;
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
	CAnimations* ani = CAnimations::GetInstance();
	ani->Get(to_string(state))->Render(position);
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
	}
}

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	goomba->SetSpeed(goomba->GetVelocity().x, -GOOMBA_JUMP_DEFLECT_SPEED);
	goomba->SetState(GAME_OBJECT_STATE_DIE);
}

void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	this->velocity.x = -this->velocity.x;
	if (koopa->GetState() == KOOPA_STATE_INSIDE_SHELL)
	{
		koopa->SetState(KOOPA_STATE_ROLLING);

	}
	else if(koopa->GetState() != KOOPA_STATE_ROLLING)
	{
		koopa->SetSpeed(0, -KOOPA_JUMP_DEFLECT_SPEED);
		koopa->SetState(KOOPA_STATE_INSIDE_SHELL);
	}
	//else if (koopa->GetState() == KOOPA_STATE_ROLLING)
	//{
	//	float vx, vy;
	//	koopa->GetSpeed(vx, vy);
	//	koopa->SetSpeed(-vx, vy);

	//}
}

void CKoopa::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
		brick->Hit(2);
}

void CKoopa::SetState(int state, int isGoingRight)
{
	this->state = state;
	this->position.y += -1.0f;
	switch (state)
	{
	case KOOPA_STATE_WALKING:
		this->velocity.x = KOOPA_WALKING_SPEED * (isGoingRight ? 1 : -1);
		break;

	case KOOPA_STATE_ROLLING:
		this->velocity.x = KOOPA_ROLLING_SPEED * (isGoingRight ? 1 : -1);
		break;
	case KOOPA_STATE_INSIDE_SHELL :
		this->velocity.x = 0;
		break;
	default:
		break;
	}
}

