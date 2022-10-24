#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"

/*
	Initialize game object
*/
CGameObject::CGameObject(D3DXVECTOR2 position, LPTEXTURE tex)
{
	this->position = position;
	this->texture = tex;
}

void CGameObject::Render()
{
}

CGameObject::~CGameObject()
{
	if (texture != NULL) delete texture;
}

#define MARIO_VX 0.1f
#define MARIO_WIDTH 14

void CMario::Update(DWORD dt)
{
}

void CMario::Render()
{
	CAnimations* ani = CAnimations::GetInstance();
	ani->Get(500)->Render(position.x, position.y);
}

#define BrickSize 8

void CBrick::Update(DWORD dt)
{
	//Moving x_axis
	position += velocity * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
};

