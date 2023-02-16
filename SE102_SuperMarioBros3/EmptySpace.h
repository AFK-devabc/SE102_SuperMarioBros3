#pragma once
#include "GameObject.h"
class CEmptySpace :
    public CGameObject
{
    int length;				// Unit: cell 
public:
	CEmptySpace(D3DXVECTOR2 position) :CGameObject(position)
	{
		this->length = length;
	}

	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = position.x - length / 2;
		t = position.y - 1;
		r = l + length;
		b = t + 1;
	}

};

