#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"

/*
	Initialize game object
*/
CGameObject::CGameObject(float x, float y, LPTEXTURE tex)
{
	this->x = x;
	this->y = y;
	this->texture = tex;
}

void CGameObject::Render()
{
	CGame::GetInstance()->Draw(x, y, texture);
}

CGameObject::~CGameObject()
{
	if (texture != NULL) delete texture;
}

#define MARIO_VX 0.1f
#define MARIO_WIDTH 14

void CMario::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - MARIO_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - MARIO_WIDTH)
		{
			x = (float)(BackBufferWidth - MARIO_WIDTH);
		}
	}
}

#define BrickSize 8

void CBrick::Update(DWORD dt)
{
	//Moving x_axis
	x += vx * dt;
	y += vy * dt;


	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= (BackBufferWidth - BrickSize))
	{

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - BrickSize)
		{
			x = (float)(BackBufferWidth - BrickSize);
		}

	}

	//Moving Y_axis


	int BackBufferHeight = CGame::GetInstance()->GetBackBufferHeight();

	//DebugOut(L"%f	%f		%d\n", x, y);

	if (y <= 0 || y >= BackBufferHeight + BrickSize)
	{

		vy = -vy;

		if (y <= 0)
		{
			y = 0;
		}
		else if (y >= BackBufferHeight  +BrickSize)
		{
			y = (float)(BackBufferHeight + BrickSize);
		}
	}

};

