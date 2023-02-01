#pragma once
#include <vector>
#include<D3DX10math.h>
#include <unordered_map>

#include "Sprites.h"
#include "debug.h"
class CHub
{
private:
	int life;
	int power;
	int item[3];
	int countDown;
	DWORD point;
public:

	void Render();
};

