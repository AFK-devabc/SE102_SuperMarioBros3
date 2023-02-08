#pragma once
#include "GameEffect.h"
#include "AddPoint.h"
#include "PlayScene.h"
#include "Hub.h"

class CCoinDrop :
    public CGameEffect
{
public:
	CCoinDrop(D3DXVECTOR2 position) : CGameEffect(position, 500) {
		this->velocity = D3DXVECTOR2(0, -COINT_START_SPEEDY);
		Ay = COIN_AY;
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = position.x - 16 / 2;
		t = position.y - 16 / 2;
		r = l + 16;
		b = t + 16;
	}
	virtual void Render() {
		CAnimations* ani = CAnimations::GetInstance();
		ani->Get(to_string(COIN_DROP))->Render(position);
	};
	virtual void Delete() { 
		isDeleted = true;
		LPGAMEOBJECT addPoint = new CAddPoint(this->position, 100);
		 dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene())->AddGameObject(addPoint);
		 CHub::GetInstance()->AddCoin(1);
	}


};

