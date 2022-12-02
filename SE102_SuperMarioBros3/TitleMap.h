#pragma once
#include <vector>
#include<D3DX10math.h>
#include <unordered_map>

#include "Sprite.h"
#include "Textures.h"
#include "debug.h"
#include "TinyXML/tinyxml.h"

using namespace std;

class CTitleMap
{
private:
	vector<int*> lpTitle;

	unordered_map<int, LPSPRITE> lpMapSprites;

	int titleSize;
	int numXTitles, numYTitles;
	int mapWidth;
	int mapHeight;
	int startX, startY, endX, endY;
	D3DXVECTOR2 startPosi;
public:
	CTitleMap(int width, int height, int titleSize, const char* filePath);
	~CTitleMap();
	void LoadTitle(const char* filePath);
	void SetTitleRender(D3DXVECTOR2 start, D3DXVECTOR2 end);

	void Render();

};

