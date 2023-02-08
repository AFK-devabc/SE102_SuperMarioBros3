#pragma once
#include "GameObject.h"
class CColorBox :
    public CGameObject
{
private:
    D3DXVECTOR2 size;
public:
	CColorBox(float x, float y,
		float cell_width, float cell_height) :CGameObject(D3DXVECTOR2(x, y))
	{
		this->size = D3DXVECTOR2(cell_width, cell_height);
	}

	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = position.x - size.x / 2;
		t = position.y - size.y / 2;
		r = l + size.x;
		b = t + size.y;
	}


	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 2; }

};

