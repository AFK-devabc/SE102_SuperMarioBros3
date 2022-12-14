#pragma once
#include <Windows.h>
#include <unordered_map>
#include <d3dx10.h>

#include "Texture.h"
#include "Sprite.h"

#include <string>

using namespace std;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites* __instance;

	unordered_map<string, LPSPRITE> sprites;

public:
	void Add(string id, int left, int top, int width, int height, LPTEXTURE tex);
	LPSPRITE Get(string id);

	static CSprites* GetInstance();
	void Clear();
};

