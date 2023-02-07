#pragma once
#include <D3DX10.h>
#include <string>
#include "debug.h"
#include <vector>

#include "TinyXML/tinystr.h"
#include "TinyXML/tinyxml.h"

struct MapNode
{
	bool left, top, right, bottom;
	D3DXVECTOR2 position;
	string sceneID;
	bool isCompleted;
	MapNode(string sceneID, D3DXVECTOR2 position, bool left, bool top, bool right, bool bottom)
	{
		this->sceneID = sceneID;
		this->position = position;
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
		this->isCompleted = false;

	}
};

class CWorldMap
{
private:
	vector<MapNode*> LPMapNodes;
	int numXNodes, numYNodes;
	bool isLoaded;

	int marioType;
	int currentNode;
	static CWorldMap* __instance;
public:

	CWorldMap();

	void Load(const char* filePath);
	MapNode* GetNode(int x, int y);

	int GetMarioType() { return marioType; }
	void SetMarioType(int type) { this->marioType = type; }
	void  SetCurrentNode(int x,int y) {
		this->currentNode = x + y * numXNodes;
	}

	void Render();
	
	void SetNodeComplete() { LPMapNodes[currentNode]->isCompleted = true; }

	static CWorldMap* GetInstance();
};
