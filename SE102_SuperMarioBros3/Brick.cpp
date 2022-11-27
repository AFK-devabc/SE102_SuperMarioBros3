#include "Brick.h"
#include "Animations.h"
#include "DefineInfo.h"
#include "GameObjectType.h"
#include "PlayScene.h"
#include "RedLeaf.h"
#include "BrickBroken.h"

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - 16 / 2;
	t = position.y - 16 / 2;
	r = l + 16;
	b = t + 16;
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	
	if (isDeleteNextFrame)
		this->Delete();
	if (hitted == 1)
	{
		velocity.y = velocity.y + 2*MARIO_GRAVITY*dt;

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
		velocity.y = velocity.y - 2 * MARIO_GRAVITY * dt;

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
	case OBJECT_TYPE_QUESTION_MARK_Empty:
		CAnimations::GetInstance()->Get(to_string(OBJECT_TYPE_QUESTION_MARK_Empty))->Render(position);
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
			if (marioType != SMALL_MARIO)
			{
				isDeleteNextFrame = 1;
				LPGAMEOBJECT effect = new CBrickBroken(this->position);
				LPPLAYSCENE p = dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene());
				p->AddGameEffect(effect);
			}
			break;

		}
		case OBJECT_TYPE_QUESTION_MARK:
		{
			velocity = D3DXVECTOR2(0, -BRICK_DEFLECT_SPEED);
			DropItems();
			this->behavior = OBJECT_TYPE_QUESTION_MARK_Empty;
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
			CPlayScene* playscene = dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene());
			playscene->AddGameObject(redLeaf);

		}
		break;
	}
	}
}
