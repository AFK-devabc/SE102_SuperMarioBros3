#include "TitleMap.h"

CTitleMap::CTitleMap(int width, int height, int titleSize, const char* filePath)
{
    mapWidth = width;
    mapHeight = height;
    this->titleSize = titleSize;
    numXTitles = (int)ceil((float)mapWidth / titleSize);
    numYTitles = (int)ceil((float)mapHeight / titleSize);

    lpTitle.resize(numXTitles * numYTitles);
    LoadTitle(filePath);
}

CTitleMap::~CTitleMap()
{
    for (auto x : lpMapSprites)
    {
        LPSPRITE s = x.second;
        delete s;
    }

    lpMapSprites.clear();

}

void CTitleMap::LoadTitle(const char* filePath)
{
	DebugOut(L"[INFO] Start loading Titles assets from : \"%s\"\n", ToLPCWSTR(filePath));
	TiXmlDocument doc(filePath);
	if (doc.LoadFile())
	{
		TiXmlElement* Root = doc.RootElement();
        if (Root)
        {
            for (TiXmlElement* textureNode = Root->FirstChildElement(); textureNode != nullptr; textureNode = textureNode->NextSiblingElement())
            {
                const char* texID = textureNode->Attribute("texID");
                CTextures* textures = CTextures::GetInstance();
                textures->Add(texID, ToLPCWSTR(textureNode->Attribute("texturePath")));
                LPTEXTURE texture = textures->Get(texID);

                for (TiXmlElement* spriteNode = textureNode->FirstChildElement(); spriteNode != nullptr; spriteNode = spriteNode->NextSiblingElement())
                {
                    int id;
                    spriteNode->QueryIntAttribute("ID", &id);
                    int left = 0, top = 0, width = 0, height = 0;
                    spriteNode->QueryIntAttribute("x", &left);
                    spriteNode->QueryIntAttribute("y", &top);
                    spriteNode->QueryIntAttribute("w", &width);
                    spriteNode->QueryIntAttribute("h", &height);
                    LPSPRITE s = new CSprite(left, top, width, height, texture);
                    lpMapSprites[id] = s;
                }
            }
        }
		
	}
	else
	{
		DebugOut(L"[ERROR] Failed to load Titles assets file \"%s\"\n", ToLPCWSTR(filePath));
		return;
	}
	DebugOut(L"[INFO] Done loading Titles assets from \"%s\"\n", ToLPCWSTR(filePath));
}


void CTitleMap::SetTitleRender(D3DXVECTOR2 start, D3DXVECTOR2 end)
{
    startX = (int)(start.x / titleSize);
    startY = (int)(start.y / titleSize);

    if (startX < 0) startX = 0;
    else if (startX >= numXTitles) startX = numXTitles - 1;
    if (startY < 0) startY = 0;
    else if (startY >= numYTitles) startY = numYTitles - 1;
    //convert to upper
    endX = (int)ceil(end.x / titleSize);
    endY = (int)ceil(end.y / titleSize);

    if (endX < 0) endX = 0;
    else if (endX >= numXTitles) endX = numXTitles - 1;
    if (endY < 0) endY = 0;
    else if (endY >= numYTitles) endY = numYTitles - 1;

}

void CTitleMap::Render()
{
    for(int i = startX; i< endX; i++)
        for (int j = startY; j < endY; j++)
        {
            lpMapSprites[/*i + j * numXTitles*/ 1]->Draw(D3DXVECTOR2(i * titleSize, j * titleSize));
        }
}
