#pragma once
#include "GameObject.h"
#include "Scenes.h"
#include "PlayScene.h"

class CPAlarm :
    public CGameObject
{
public:
	CPAlarm(D3DXVECTOR2 position) : CGameObject(position) {
		state = ALARM_STATE_IDLE;
	};
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		l = position.x - 16 / 2;
		t = position.y - 16 / 2;
		r = l + 16;
		b = t + 16;
	}
	void Render() {
		CAnimations::GetInstance()->Get(to_string(state))->Render(position);
	}

	virtual int IsBlocking() { return state != ALARM_STATE_TOUCHED; }

	virtual void SetState(int state)
	{
		if (this->state != ALARM_STATE_TOUCHED)
		{
			this->state = state;
			vector<LPGAMEOBJECT> lpbrick;
		 lpbrick=	dynamic_cast<CPlayScene*>(CScenes::GetInstance()->GetCurrentScene())->GetBrick();;
		 for (int i = 0; i < lpbrick.size();i++)
			 lpbrick[i]->SetState(BRICK_STATE_CHANGED_INTO_COIN);
		}
	}
};

