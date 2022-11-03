#pragma once
#include <Windows.h>
#include <d3dx10.h>

#include "Animations.h"

class CGameObject
{
protected:

	D3DXVECTOR2 position;

	// This should be a pointer to an object containing all graphic/sound/audio assets for rendering this object. 
	// For now, just a pointer to a single texture	
	LPTEXTURE texture;
public:
	void SetPosition(D3DXVECTOR2 position) { this->position = position; }
	D3DXVECTOR2 GetPosition() { return position; }

	CGameObject(D3DXVECTOR2 position = D3DXVECTOR2(0,0), LPTEXTURE texture = NULL);

	virtual void Update(DWORD dt) = 0;
	virtual void Render();

	~CGameObject();
};
typedef CGameObject* LPGAMEOBJECT;
