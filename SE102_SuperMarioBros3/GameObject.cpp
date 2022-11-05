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
	this->velocity = D3DXVECTOR2(0, 0);
	this->texture = tex;
}

void CGameObject::Render()
{
}

CGameObject::~CGameObject()
{
	if (texture != NULL) delete texture;
}


