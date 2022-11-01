#include "Sprites.h"
#include "Game.h"
#include "debug.h"

CSprites* CSprites::__instance = NULL;

CSprites* CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprites::Add(string id, int left, int top, int right, int bottom, LPTEXTURE tex)
{
	RECT spriteRect;
	spriteRect.left = left;
	spriteRect.top = top;
	spriteRect.bottom = bottom;
	spriteRect.right = right;
	LPSPRITE s = new CSprite(spriteRect, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(string id)
{
	return sprites[id];
}