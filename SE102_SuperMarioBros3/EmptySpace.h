#pragma once
#include "GameObject.h"
class CEmptySpace :
    public CGameObject
{
    int length;				
	string nextScene;
public:
	CEmptySpace(D3DXVECTOR2 position, int length, string nextScene) :CGameObject(position)
	{
		this->length = length;
		this->nextScene = nextScene;
	}

	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = position.x - length / 2;
		t = position.y - 1;
		r = l + length;
		b = t + 1;
	}
	virtual void Render()
	{
		RenderBoundingBox();
	}
	string GetNextScene()
	{
		return nextScene;
	}

};

