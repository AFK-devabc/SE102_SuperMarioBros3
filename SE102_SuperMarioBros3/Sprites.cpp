#include "Sprites.h"
#include "Game.h"
#include "debug.h"

CSprites* CSprites::__instance = NULL;

CSprites* CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}

void CSprites::Add(string id, int left, int top, int width, int height, LPTEXTURE tex)
{
	LPSPRITE s = new CSprite(left,top, width, height, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(string id)
{
	return sprites[id];
}