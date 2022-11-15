#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "debug.h"
#include <string>

using namespace std;


class CAnimations
{
	static CAnimations* __instance;

	unordered_map<string, LPANIMATION> animations;

public:
	void Add(string id, LPANIMATION ani);
	LPANIMATION Get(string id);

	static CAnimations* GetInstance();
};