#include "IntroScene.h"
#define Title_Vy 0.1f
CIntroScene::CIntroScene(string id, string filePath) :
	CScene(id, filePath)
{
}


void CIntroScene::LoadAssets(const char* filePath)
{
	DebugOut(L"[INFO] Start loading assets from : \"%s\"\n", ToLPCWSTR(filePath));
	TiXmlDocument doc(filePath);
	if (doc.LoadFile())
	{
		TiXmlElement* Root = doc.RootElement();

		if (Root)
		{
			//Load texture first
			for (TiXmlElement* textureNode = Root->FirstChildElement(); textureNode != nullptr; textureNode = textureNode->NextSiblingElement())
			{
				CTextures* textures = CTextures::GetInstance();
				CAnimations* animations = CAnimations::GetInstance();
				CSprites* sprites = CSprites::GetInstance();

				const char* texID = textureNode->Attribute("texID");
				textures->Add(texID, ToLPCWSTR(textureNode->Attribute("texturePath")));
				LPTEXTURE texture = textures->Get(texID);

				const char* texFlipXID = "";
				texFlipXID = textureNode->Attribute("texFlipXID");

				if (texFlipXID != NULL) 					//Load animaion node when there a flipX
				{
					textures->Add(texFlipXID, ToLPCWSTR(textureNode->Attribute("texturePathFlipX")));

					LPTEXTURE textureFlipX = textures->Get(texFlipXID);
					int textureWidth = textureFlipX->getWidth();

					for (TiXmlElement* aniNode = textureNode->FirstChildElement(); aniNode != nullptr; aniNode = aniNode->NextSiblingElement())
					{
						string aniID = aniNode->Attribute("aniID");

						if (aniID != "none")
						{
							string aniFlipXID = aniID + "FlipX";

							int frameTime = 100;
							aniNode->QueryIntAttribute("frameTime", &frameTime);
							CAnimation* ani = new CAnimation(frameTime);

							CAnimation* aniFlipX = new CAnimation(frameTime);


							for (TiXmlElement* spriteNode = aniNode->FirstChildElement(); spriteNode != nullptr; spriteNode = spriteNode->NextSiblingElement())
							{
								string spriteID = spriteNode->Attribute("spriteID");
								string spriteFlipXID = spriteID + "FlipX";

								if (sprites->Get(spriteID) == NULL)
								{
									int left = 0, top = 0, width = 0, height = 0;
									spriteNode->QueryIntAttribute("x", &left);
									spriteNode->QueryIntAttribute("y", &top);
									spriteNode->QueryIntAttribute("w", &width);
									spriteNode->QueryIntAttribute("h", &height);
									sprites->Add(spriteID, left, top, width, height, texture);

									sprites->Add(spriteFlipXID, textureWidth - left - width, top, width, height, textureFlipX);
								}
								ani->Add(spriteID);
								aniFlipX->Add(spriteFlipXID);

							}
							animations->Add(aniID, ani);
							animations->Add(aniFlipXID, aniFlipX);

						}
						else
						{
							for (TiXmlElement* spriteNode = aniNode->FirstChildElement(); spriteNode != nullptr; spriteNode = spriteNode->NextSiblingElement())
							{
								string spriteID = spriteNode->Attribute("spriteID");
								string spriteFlipXID = spriteID + "FlipX";

								int left = 0, top = 0, width = 0, height = 0;
								spriteNode->QueryIntAttribute("x", &left);
								spriteNode->QueryIntAttribute("y", &top);
								spriteNode->QueryIntAttribute("w", &width);
								spriteNode->QueryIntAttribute("h", &height);
								sprites->Add(spriteID, left, top, width, height, texture);
								sprites->Add(spriteFlipXID, textureWidth - left - width, top, width, height, texture);

							}
						}
					}

				}
				else 					//Load animaion node when there no flipX
				{
					for (TiXmlElement* aniNode = textureNode->FirstChildElement(); aniNode != nullptr; aniNode = aniNode->NextSiblingElement())
					{
						string aniID = aniNode->Attribute("aniID");
						if (aniID != "none")
						{

							int frameTime = 100;
							aniNode->QueryIntAttribute("frameTime", &frameTime);
							CAnimation* ani = new CAnimation(frameTime);

							for (TiXmlElement* spriteNode = aniNode->FirstChildElement(); spriteNode != nullptr; spriteNode = spriteNode->NextSiblingElement())
							{
								string spriteID = spriteNode->Attribute("spriteID");
								if (sprites->Get(spriteID) == NULL)
								{
									int left = 0, top = 0, width = 0, height = 0;
									spriteNode->QueryIntAttribute("x", &left);
									spriteNode->QueryIntAttribute("y", &top);
									spriteNode->QueryIntAttribute("w", &width);
									spriteNode->QueryIntAttribute("h", &height);
									sprites->Add(spriteID, left, top, width, height, texture);
								}
								ani->Add(spriteID);
							}
							animations->Add(aniID, ani);
						}
						else
						{
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
	}
	else
	{
		DebugOut(L"[ERROR] Failed to load assets file \"%s\"\n", ToLPCWSTR(filePath));
		return;
	}
	DebugOut(L"[INFO] Done loading assets from \"%s\"\n", ToLPCWSTR(filePath));
}

void CIntroScene::LoadGameObject()
{
	//titlePosition = D3DXVECTOR2(151, 64);
	//roofPosition = D3DXVECTOR2(151, 8);
	//leftTreePosition = D3DXVECTOR2(32, 176);
	//rightTreePosition = D3DXVECTOR2(276, 160);

	groundPosition = D3DXVECTOR2(151, 224);
	introArrow = new CIntroArrow();

}



void CIntroScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : \"%s\"\n", ToLPCWSTR(sceneFilePath));

	this->SetState(SCENE_STATE_IDLE);
	LPKeyHandler.clear();
	CCamera::GetInstance()->SetCamLock(D3DXVECTOR2(0, 0));

	D3DXCOLOR backGroundColor = D3DXCOLOR(0, 0, 0, 0);
	
	CGraphics::GetInstance()->SetBackGroundColor(backGroundColor);

	LoadGameObject();

	LPKeyHandler.push_back(introArrow);
	introTime = 0;	
	eventCount = 0;

	TiXmlDocument doc(sceneFilePath.c_str());
	if (doc.LoadFile())
	{
		TiXmlElement* Root = doc.RootElement();
		if (Root)
		{
			for (TiXmlElement* resourcePathNode = Root->FirstChildElement(); resourcePathNode != nullptr; resourcePathNode = resourcePathNode->NextSiblingElement())
			{
				const char* resourceType = resourcePathNode->Attribute("Type");
				if (strcmp(resourceType, "Assets") == 0)
				{
					const char* filePath = resourcePathNode->Attribute("filePath");
					LoadAssets(filePath);
				}
			}
		}
	}
	else
	{
		DebugOut(L"[ERROR] Failed to load scene from file \"%s\"\n", ToLPCWSTR(sceneFilePath));
		return;
	}
	DebugOut(L"[INFO] Done loading scene  \"%s\"\n", ToLPCWSTR(sceneFilePath));
}

void CIntroScene::Update(DWORD dt)
{
	introTime += dt;
	if (introTime < 2500 || eventCount < 1)
	{
		if (eventCount < 1)
		{
			eventCount++;

			roofPosition = D3DXVECTOR2(151, 216);
		}

		roofPosition.y -= Title_Vy * dt;

	}
	else if (introTime < 5000 || eventCount < 2)
	{
		if (eventCount < 2)
		{
			eventCount++;
			
			titlePosition = D3DXVECTOR2(151, -64);
			roofPosition = D3DXVECTOR2(151, -120);
		}
		if (titlePosition.y < 64)
		{
			titlePosition.y += Title_Vy * dt;
			roofPosition.y += Title_Vy * dt;
		}

	}
	else 
	{
		if (eventCount < 3)
		{
			eventCount++;
			this->SetState(SCENE_STATE_PLAYING);
			D3DXCOLOR backGroundColor = D3DXCOLOR(1, 0.86, 0.63, 1);
			CGraphics::GetInstance()->SetBackGroundColor(backGroundColor);

			titlePosition = D3DXVECTOR2(151, 64);
			roofPosition = D3DXVECTOR2(151, 8);
			leftTreePosition = D3DXVECTOR2(32, 176);
			rightTreePosition = D3DXVECTOR2(276, 160);
		}
	}


}
void CIntroScene::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* ani = CAnimations::GetInstance();

	sprites->Get("ground")->DrawHub(groundPosition + D3DXVECTOR2(128, 0));
	sprites->Get("ground")->DrawHub(groundPosition + D3DXVECTOR2(0, 0));
	sprites->Get("ground")->DrawHub(groundPosition + D3DXVECTOR2(-128, 0));
	switch (eventCount)
	{

	case 1:
	{
		sprites->Get("roof_2")->DrawHub(roofPosition + D3DXVECTOR2(128, 0));
		sprites->Get("roof_2")->DrawHub(roofPosition + D3DXVECTOR2(0, 0));
		sprites->Get("roof_2")->DrawHub(roofPosition + D3DXVECTOR2(-128, 0));
		int i = 1;
		while (roofPosition.y - i * 16 > 0)
		{
			sprites->Get("roof_1")->DrawHub(roofPosition + D3DXVECTOR2(128, -16 * i));
			sprites->Get("roof_1")->DrawHub(roofPosition + D3DXVECTOR2(0, -16 * i));
			sprites->Get("roof_1")->DrawHub(roofPosition + D3DXVECTOR2(-128, -16 * i));
			i++;
		}

		break;
	}
	case 2:
	{
		sprites->Get("roof_3")->DrawHub(roofPosition + D3DXVECTOR2(128, 0));
		sprites->Get("roof_3")->DrawHub(roofPosition + D3DXVECTOR2(0, 0));
		sprites->Get("roof_3")->DrawHub(roofPosition + D3DXVECTOR2(-128, 0));

		sprites->Get("GameTitle_0")->DrawHub(titlePosition + D3DXVECTOR2(0, -16));
		sprites->Get("GameTitle_1")->DrawHub(titlePosition + D3DXVECTOR2(0, 20));

		sprites->Get("Number_3_0")->DrawHub(titlePosition + D3DXVECTOR2(0, 64));

		sprites->Get("BigCloud")->DrawHub(titlePosition + D3DXVECTOR2(-112, -16));
		sprites->Get("BigCloud")->DrawHub(titlePosition + D3DXVECTOR2(96, -32));
		sprites->Get("SmallCloud")->DrawHub(titlePosition + D3DXVECTOR2(-128, 16));

		break;
	}
	default:
	{
		sprites->Get("roof_3")->DrawHub(roofPosition + D3DXVECTOR2(128, 0));
		sprites->Get("roof_3")->DrawHub(roofPosition + D3DXVECTOR2(0, 0));
		sprites->Get("roof_3")->DrawHub(roofPosition + D3DXVECTOR2(-128, 0));

		sprites->Get("GameTitle_0")->DrawHub(titlePosition + D3DXVECTOR2(0, -16));
		sprites->Get("GameTitle_1")->DrawHub(titlePosition + D3DXVECTOR2(0, 20));

		ani->Get("Number_3")->Render(titlePosition + D3DXVECTOR2(0, 64));

		sprites->Get("BigCloud")->DrawHub(titlePosition + D3DXVECTOR2(-112, -16));
		sprites->Get("BigCloud")->DrawHub(titlePosition + D3DXVECTOR2(96, -32));
		sprites->Get("SmallCloud")->DrawHub(titlePosition + D3DXVECTOR2(-128, 16));

		sprites->Get("Tree_Left")->DrawHub(leftTreePosition);
		sprites->Get("Tree_Right")->DrawHub(rightTreePosition);
		introArrow->Render();

		break;
	}
	}

}

void CIntroScene::Unload()
{
	delete introArrow;
}
