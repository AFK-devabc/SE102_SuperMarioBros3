#include <Windows.h>

#include "debug.h"
#include "Graphics.h"
#include "Textures.h"

CTextures* CTextures::__instance = NULL;

CTextures::CTextures()
{

}

CTextures* CTextures::GetInstance()
{
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}



void CTextures::Add(string id, LPCWSTR filePath)
{
	textures[id] = CGraphics::GetInstance()->LoadTexture(filePath);
}

LPTEXTURE CTextures::Get(string id)
{
	return textures[id];
}



