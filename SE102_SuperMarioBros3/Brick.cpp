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

	
	if (isDeleteNextFrame)
		this->Delete();
	if (hitted == 1)
	{
		velocity.y = velocity.y + 2*BRICK_DEFLECT_SPEED*dt;

		position = position + velocity * dt;

		if (position.y > initialposition.y)
		{
			velocity.y = 0;
			hitted = 0;
			position = initialposition;
		}
	}
	if (hitted == 2)
	{
		velocity.y = velocity.y - 2 * BRICK_DEFLECT_SPEED * dt;

		position = position + velocity * dt;

		if (position.y < initialposition.y)
		{
			velocity.y = 0;
			hitted = 0;
			position = initialposition;
		}
	}

}


void CBrick::Render()
{
	switch ( behavior)
	{
	case OBJECT_TYPE_QUESTION_MARK:
		CAnimations::GetInstance()->Get(to_string(OBJECT_TYPE_QUESTION_MARK))->Render(position);
		break;
	case OBJECT_TYPE_BRICK:
		CAnimations::GetInstance()->Get(to_string(OBJECT_TYPE_BRICK))->Render(position);
		break;
	case OBJECT_TYPE_MUSIC_NOTE:
		CAnimations::GetInstance()->Get(to_string(OBJECT_TYPE_MUSIC_NOTE))->Render(position);
		break;
	case OBJECT_TYPE_QUESTION_MARK_EMPTY:
		CAnimations::GetInstance()->Get(to_string(OBJECT_TYPE_QUESTION_MARK_EMPTY))->Render(position);
		break;

	default:
		break;
	}
}


void CBrick::SetState(int state, int islookright)
{
}

void CBrick::Hit(int type)
{
	if (!hitted)
	{
		hitted = type;
		CPlayScene* playscene = dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene());
		int marioType = dynamic_cast<CPlayer*> (playscene->GetPlayer())->GetMarioType();

		switch (this->behavior)
		{
		case OBJECT_TYPE_MUSIC_NOTE:
		{
			velocity = D3DXVECTOR2(0, -BRICK_DEFLECT_SPEED);
			if(type == 2)
				velocity = D3DXVECTOR2(0, BRICK_DEFLECT_SPEED);
			break;
		}
		case OBJECT_TYPE_BRICK:
		{
			velocity = D3DXVECTOR2(0, -BRICK_DEFLECT_SPEED);
			if (marioType != SMALL_MARIO || type == 2)
			{
				isDeleteNextFrame = 1;
				LPGAMEOBJECT effect = new CBrickBroken(this->position);
				LPPLAYSCENE p = dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene());
				p->AddGameObject(effect);
			}
			break;

		}
		case OBJECT_TYPE_QUESTION_MARK:
		{
			velocity = D3DXVECTOR2(0, -BRICK_DEFLECT_SPEED);
			DropItems();
			this->behavior = OBJECT_TYPE_QUESTION_MARK_EMPTY;
			break;

		}

		default:
			break;
		}


		
	}
}

void CBrick::DropItems()
{
	CPlayScene* playscene = dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene());
	int marioType = dynamic_cast<CPlayer*> (playscene->GetPlayer())->GetMarioType();
	switch (this->GetItemContain())
	{
	case OBJECT_TYPE_MUSHROOM:
	{
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
	case COIN_DROP:
	{
		LPGAMEOBJECT effect = new CCoinDrop(this->GetPosition());
		playscene->AddGameObject(effect);

	}
	}
}
