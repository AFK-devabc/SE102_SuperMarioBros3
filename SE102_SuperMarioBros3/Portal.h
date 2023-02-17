#pragma once
#include "GameObject.h"
class CPortal :
    public CGameObject
{
private:
	string nextScene;
public:
	CPortal(float x, float y,
		string NextScene) :CGameObject(D3DXVECTOR2(x, y))
	{
		nextScene = NextScene;
	}

	void GetBoundingBox(float& l, float& t, float& r, float& b) 
	{
		l = position.x - 16 / 2;
		t = position.y - 16 / 2;
		r = l + 16;
		b = t + 16;
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

