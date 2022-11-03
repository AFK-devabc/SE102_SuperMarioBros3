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


