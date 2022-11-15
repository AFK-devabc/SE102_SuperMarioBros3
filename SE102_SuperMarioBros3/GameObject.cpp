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

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(position.x, position.y, 0);
	RECT* rect = new RECT();

	LPTEXTURE bbox = CTextures::GetInstance()->Get("BBox");

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect->left = 0;
	rect->top = 0;
	rect->right = (int)r - (int)l;
	rect->bottom = (int)b - (int)t;

	D3DXVECTOR2 campos=	CCamera::GetInstance()->GetPosition();
	CGraphics::GetInstance()->Draw(position.x - campos.x,position.y - campos.y, bbox, rect);

}

void CGameObject::Render()
{
}

CGameObject::~CGameObject()
{
	if (texture != NULL) delete texture;
}


