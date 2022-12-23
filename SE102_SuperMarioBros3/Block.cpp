#include "Block.h"
#include "Animations.h"
#include "DefineInfo.h"
#include "GameObjectType.h"
#include "PlayScene.h"
#include "RedLeaf.h"
#include "BrickBroken.h"
#include "CoinDrop.h"

void CBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = position.x - BRICK_WIDTH / 2;
	t = position.y - BRICK_HEIGHT / 2;
	r = l + BRICK_WIDTH;
	b = t + BRICK_WIDTH;

}

void CBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CBlock::DropItems()
{
	CPlayScene* playscene = dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene());
	int marioType = dynamic_cast<CPlayer*> (playscene->GetPlayer())->GetMarioType();
	switch (itemContain)
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

