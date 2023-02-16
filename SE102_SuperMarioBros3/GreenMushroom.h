#pragma once
#include "MushRoom.h"
class CGreenMushroom :
	public CMushRoom
{
private:
	int startY;
	D3DXVECTOR2 startPosition;

public:
	CGreenMushroom(D3DXVECTOR2 position) : CMushRoom(position) {
		velocity = D3DXVECTOR2(0, -0.02f);
		state = MUSHROOM_STATE_INSIDE;
		startY = position.y;
	};
	void Render() {
		CAnimations::GetInstance()->Get(to_string(OBJECT_TYPE_GREEN_MUSHROOM))->Render(position);
	}
};

