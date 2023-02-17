#include "WorldMapsScene.h"
#include "PlayScene.h"
#include "GameObjectType.h"

#include "Animations.h"
#include "Sprites.h"



void CWorldMapsScene::LoadGameObject()
{

	mario->SetMario(worldMap->GetMarioType());
	CCamera::GetInstance()->SetCamLock(D3DXVECTOR2(0, 0));
	Hub->ReloadHub(0);

	LPKeyHandler.clear();

	if (Hub->IsGameOver())
	{
		gameOverArrow = new CGameOverArrow();
		LPKeyHandler.push_back(gameOverArrow);

	}
	else
	{
		LPKeyHandler.push_back(mario);
	}

	D3DXCOLOR backGroundColor = D3DXCOLOR(0, 0, 0, 0);
	CGraphics::GetInstance()->SetBackGroundColor(backGroundColor);

}

CWorldMapsScene::CWorldMapsScene(string id, string filePath) :
	CScene(id, filePath)
{
	worldMap = CWorldMap::GetInstance();
	mario = new CWorldMapMario();
	Hub = CHub::GetInstance();
	enemyPosition = D3DXVECTOR2(95, 128);
}

void CWorldMapsScene::LoadAssets(const char* filePath)
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

void CWorldMapsScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : \"%s\"\n", ToLPCWSTR(sceneFilePath));

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
				else if (strcmp(resourceType, "MapNodes") == 0)

				{
					const char* filePath = resourcePathNode->Attribute("filePath");
					worldMap->Load(filePath);
				}
			}
		}
	}
	else
	{
		DebugOut(L"[ERROR] Failed to load scene from file \"%s\"\n", ToLPCWSTR(sceneFilePath));
		return;
	}

	LoadGameObject();

	DebugOut(L"[INFO] Done loading scene  \"%s\"\n", ToLPCWSTR(sceneFilePath));
}

void CWorldMapsScene::Update(DWORD dt)
{
	switch (state)
	{
	case SCENE_STATE_PLAYING:
	{
		enemyPosition.x += enemyVx * dt;
		if (enemyPosition.x <= 87)
		{
			enemyVx = -enemyVx;
			enemyPosition.x = 87;
		}
		else if (enemyPosition.x >= 103)
		{
			enemyVx = -enemyVx;
			enemyPosition.x = 103;
		}

		mario->Update(dt);
		break;
	}
	case SCENE_STATE_SWITCHSCENE_DELAY:
	{
		break;
	}
	case SCENE_STATE_IDLE:
	{
		if (GetTickCount64() - startStateTime > totalStateTime)
			state = SCENE_STATE_PLAYING;
		break;
	}
	case SCENE_STATE_PAUSING:
	{
		break;
	}
	default:
		break;
	}

}

void CWorldMapsScene::Render()
{
	CSprites::GetInstance()->Get("Map_1_1")->DrawHub(D3DXVECTOR2(151, 100));
	worldMap->Render();
	Hub->Render();
	CAnimations::GetInstance()->Get(to_string(1000 + (enemyVx > 0 ? 1 : 0)))->Render(enemyPosition);
	if (state == SCENE_STATE_IDLE)
		CSprites::GetInstance()->Get("World_1_Title")->DrawHub(D3DXVECTOR2(151, 100));


	mario->Render();
	if(Hub->IsGameOver())
	gameOverArrow->Render();
}

void CWorldMapsScene::Unload()
{
}

void CWorldMapsScene::ResetGame()
{
	Hub->ResetHub();
	CWorldMap::GetInstance()->ResetWorldMap();
	this->state = SCENE_STATE_IDLE;

	startStateTime = GetTickCount64();

	totalStateTime = WorldMapScene_IDLE_START_TIME;

	this->Load();

	CKeyBoard::GetInstance()->Clear();
	CKeyBoard::GetInstance()->SetKeyHandler(LPKeyHandler);

}

