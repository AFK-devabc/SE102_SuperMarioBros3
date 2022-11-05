#include "ImportFromXML.h"

void LoadAniData_FromXML(const char* filePath)
{
	TiXmlDocument doc(filePath);
	if (doc.LoadFile())
	{
		TiXmlElement* Root = doc.RootElement();

		if (Root)
		{
			//Load texture first
			for (TiXmlElement* textureNode = Root->FirstChildElement(); textureNode != nullptr; textureNode = textureNode->NextSiblingElement())
			{
				const char* texID = textureNode->Attribute("texID");
				CTextures* textures = CTextures::GetInstance();
				textures->Add(texID, ToLPCWSTR(textureNode->Attribute("texturePath")));
				LPTEXTURE texture = textures->Get(texID);

				//Load animaion node 
				for (TiXmlElement* aniNode = textureNode->FirstChildElement(); aniNode != nullptr; aniNode = aniNode->NextSiblingElement())
				{
					string aniID = aniNode->Attribute("aniID");
					if (aniID != "none")
					{

						CAnimations* animations = CAnimations::GetInstance();
						CSprites* sprites = CSprites::GetInstance();

						int frameTime = 100;
						aniNode->QueryIntAttribute("frameTime", &frameTime);
						CAnimation* ani = new CAnimation(frameTime);

						for (TiXmlElement* spriteNode = aniNode->FirstChildElement(); spriteNode != nullptr; spriteNode = spriteNode->NextSiblingElement())
						{
							string spriteID = spriteNode->Attribute("spriteID");

							int left = 0, top = 0, width = 0, height = 0;
							spriteNode->QueryIntAttribute("x", &left);
							spriteNode->QueryIntAttribute("y", &top);
							spriteNode->QueryIntAttribute("w", &width);
							spriteNode->QueryIntAttribute("h", &height);
							sprites->Add(spriteID, left, top, width, height, texture);
							ani->Add(spriteID);
						}
						animations->Add(aniID, ani);
					}
					else
					{
						CSprites* sprites = CSprites::GetInstance();
						for (TiXmlElement* spriteNode = aniNode->FirstChildElement(); spriteNode != nullptr; spriteNode = spriteNode->NextSiblingElement())
						{
							string spriteID = spriteNode->Attribute("spriteID");

							int left = 0, top = 0, width = 0, height = 0;
							spriteNode->QueryIntAttribute("x", &left);
							spriteNode->QueryIntAttribute("y", &top);
							spriteNode->QueryIntAttribute("w", &width);
							spriteNode->QueryIntAttribute("h", &height);
							sprites->Add(spriteID, left, top, width, height, texture);
						}
					}
				}
			}
		}
	}
	else
	{
		DebugOut(L"Failed to load anidata file \"%s\"\n", ToLPCWSTR(filePath));
	}
}

void LoadResources_FromXML(const char* filePath)
{
}

