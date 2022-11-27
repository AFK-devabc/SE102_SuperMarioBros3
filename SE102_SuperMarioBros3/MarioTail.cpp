#include "MarioTail.h"
#include "GameObject.h"
#include "CPlayer.h"
#include "Goomba.h"
#include "Brick.h"
#include "RedLeaf.h"
#include "Koopa.h"
#include "MushRoom.h"
#include "Scenes.h"
#include "PlayScene.h"
#include "BrickBroken.h"
#include "HardCollision.h"
#include "GameEffect.h"

void CMarioTail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - 16 / 2;
	t = position.y - 8 / 2;
	r = l + 16;
	b = t + 8;

}

void CMarioTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CCollision::GetInstance()->ProcessIsColliding(this, dt, coObjects);
	this->Delete();
}

void CMarioTail::Render()
{
	RenderBoundingBox();
}

void CMarioTail::IsCollidingWith(LPGAMEOBJECT e)
{
	if (dynamic_cast<CGoomba*>(e))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CBrick*>(e))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CKoopa*>(e))
		OnCollisionWithKoopa(e);

}

void CMarioTail::OnCollisionWithGoomba(LPGAMEOBJECT e)
{
	e->SetState(GOOMBA_STATE_DYING);
	e->SetSpeed(0, -MARIO_JUMP_DEFLECT_SPEED);

	LPGAMEOBJECT effect = new CHardCollision(this->position);

	LPPLAYSCENE p = dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene());
	p->AddGameEffect(effect);

}

void CMarioTail::OnCollisionWithKoopa(LPGAMEOBJECT e)
{
	e->SetState(KOOPA_STATE_INSIDE_SHELL);
	e->SetSpeed(0, -MARIO_JUMP_DEFLECT_SPEED);

	LPGAMEOBJECT effect = new CHardCollision(this->position);

	LPPLAYSCENE p = dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene());
	p->AddGameEffect(effect);


}

void CMarioTail::OnCollisionWithBrick(LPGAMEOBJECT e)
{
	dynamic_cast<CBrick*>(e)->Hit(1);
}

