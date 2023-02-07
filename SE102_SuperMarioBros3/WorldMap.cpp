#include "WorldMap.h"
#include "DefineInfo.h"
#include "Sprites.h"
CWorldMap* CWorldMap::__instance = NULL;
CWorldMap::CWorldMap()
{
	isLoaded = false;
	__instance == this;
	marioType = SMALL_MARIO;
}

void CWorldMap::Load(const char* filePath)
{
	if (isLoaded)
		return;
	DebugOut(L"[INFO] Start loading Maps from : \"%s\"\n", ToLPCWSTR(filePath));
	TiXmlDocument doc(filePath);
	if (doc.LoadFile())
	{
		isLoaded = true;
		TiXmlElement* Root = doc.RootElement();
		if (Root)
		{
			LPMapNodes.clear();
			Root->QueryIntAttribute("numXNodes", &numXNodes);
			Root->QueryIntAttribute("numYNodes", &numYNodes);

			LPMapNodes.clear();

			for (TiXmlElement* mapNode = Root->FirstChildElement(); mapNode != nullptr; mapNode = mapNode->NextSiblingElement())
			{
				bool left, top, right, bottom;
				int x=0, y=0;
				D3DXVECTOR2 position;
				string sceneID;

				sceneID = mapNode->Attribute("sceneID");

				mapNode->QueryIntAttribute("x", &x);
				mapNode->QueryIntAttribute("y", &y);
				position = D3DXVECTOR2(x, y);

				mapNode->QueryBoolAttribute("left", &left);
				mapNode->QueryBoolAttribute("top", &top);
				mapNode->QueryBoolAttribute("right", &right);
				mapNode->QueryBoolAttribute("bottom", &bottom);
				MapNode* p = new MapNode(sceneID, position, left, top, right, bottom);
				LPMapNodes.push_back(p);
			}
		}

	}
	else
	{
		DebugOut(L"[ERROR] Failed to load Maps file \"%s\"\n", ToLPCWSTR(filePath));
		return;
	}
	DebugOut(L"[INFO] Done loading Maps from \"%s\"\n", ToLPCWSTR(filePath));

}

MapNode* CWorldMap::GetNode(int x, int y)
{
	return LPMapNodes[x + y * numXNodes];
}

CWorldMap* CWorldMap::GetInstance()
{
	if (__instance == NULL) __instance = new CWorldMap();

	return __instance;
}

void CWorldMap::Render()
{
	for (int i =0 ; i < LPMapNodes.size(); i++)
	{
		if (LPMapNodes[i]->isCompleted)
			CSprites::GetInstance()->Get("M_Complete")->DrawHub(LPMapNodes[i]->position);
	}
}
