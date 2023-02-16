#include "ItemContainer.h"
#include "PlayScene.h"
#include "RedLeaf.h"
#include "CoinDrop.h"
#include "PAlarm.h"
#include "GreenMushroom.h"
void CItemContainer::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - BRICK_WIDTH / 2;
	t = position.y - BRICK_HEIGHT / 2;
	r = l + BRICK_WIDTH;
	b = t + BRICK_WIDTH;
}

void CItemContainer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (hitted)
	{
		velocity.y +=  GRAVITY * dt;

		position = position + velocity * dt;

		if (position.y > initialposition.y)
		{
			velocity.y = 0;
			hitted = 0;
			position = initialposition;
		}
	}
}


void CItemContainer::Render()
{
	CAnimations::GetInstance()->Get(to_string(state))->Render(position);
}


void CItemContainer::SetState(int state)
{
	if (this->state == OBJECT_TYPE_EMPTY_BLOCK)
		return;
	this->state = state;
	
	DropItems();
}


void CItemContainer::DropItems()
{
	
	CPlayScene* playscene = dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene());
	int marioType = dynamic_cast<CPlayer*> (playscene->GetPlayer())->GetMarioType();
	switch (itemContain)
	{
	case OBJECT_TYPE_MUSHROOM:
	{
		this->hitted = true;
		velocity = D3DXVECTOR2(D3DXVECTOR2(0, -BRICK_DEFLECT_SPEED));

		if (marioType != BIG_MARIO)
		{
			LPGAMEOBJECT mushroom = new CMushRoom(this->position);
			playscene->AddGameObject(mushroom);
		}
		else
		{
			LPGAMEOBJECT redLeaf = new CRedLeaf(this->GetPosition());
			playscene->AddGameObject(redLeaf);

		}
		break;
	}
	case OBJECT_TYPE_P_ALARM:
	{
		LPGAMEOBJECT alarm = new CPAlarm(this->GetPosition() + D3DXVECTOR2(0,-BRICK_HEIGHT));
		playscene->AddGameObject(alarm);

		break;
	}
	case COIN_DROP:
	{
		this->hitted = true;
		velocity = D3DXVECTOR2(D3DXVECTOR2(0, -BRICK_DEFLECT_SPEED));

		LPGAMEOBJECT effect = new CCoinDrop(this->GetPosition());
		playscene->AddGameObject(effect);
		break;
	}
	case OBJECT_TYPE_GREEN_MUSHROOM:
	{
		this->hitted = true;
		velocity = D3DXVECTOR2(D3DXVECTOR2(0, -BRICK_DEFLECT_SPEED));

			LPGAMEOBJECT mushroom = new CGreenMushroom(this->position);
			playscene->AddGameObject(mushroom);
		break;
	}
	}
}
