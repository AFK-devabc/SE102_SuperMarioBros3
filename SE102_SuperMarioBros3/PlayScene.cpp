#include "PlayScene.h"
#include "GameObjectType.h"

CPlayScene::CPlayScene(string id, string filePath) :
	CScene(id, filePath)
{
	player = NULL;
}

void CPlayScene::LoadAssets(const char* filePath)
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
		DebugOut(L"[ERROR] Failed to load assets file \"%s\"\n", ToLPCWSTR(filePath));
		return;
	}
	DebugOut(L"[INFO] Done loading assets from \"%s\"\n", ToLPCWSTR(filePath));
}

void CPlayScene::LoadGameObjects(const char* filePath)
{
	DebugOut(L"[INFO] Start loading GameObjects from : \"%s\"\n", ToLPCWSTR(filePath));
	TiXmlDocument doc(filePath);
	if (doc.LoadFile())
	{
		TiXmlElement* Root = doc.RootElement();

		if (Root)
		{
			for (TiXmlElement* gameObjectNode = Root->FirstChildElement(); gameObjectNode != nullptr; gameObjectNode = gameObjectNode->NextSiblingElement())
			{
				LPGAMEOBJECT gameObject;
				int gameObjectType = 0, x = 0, y = 0;
				gameObjectNode->QueryIntAttribute("objType", &gameObjectType);

				gameObjectNode->QueryIntAttribute("x", &x);
				gameObjectNode->QueryIntAttribute("y", &y);

				D3DXVECTOR2 position = D3DXVECTOR2(x, y);

				switch (gameObjectType)
				{
				case OBJECT_TYPE_MARIO:
				{
					if (player != NULL)
					{
						DebugOut(L"[Error] Player was already loaded\n");
						return;
					}
					player = new CPlayer(position);
					CCamera::GetInstance()->SetCamFollow(player->GetPPosition());

					LPKeyHandler.push_back(player);
					gameObject = player;
					break;
				}
				case OBJECT_TYPE_GOOMBA:
				{
					int type = 0, state = 0;
					gameObjectNode->QueryIntAttribute("type", &type);
					gameObjectNode->QueryIntAttribute("state", &state);

					gameObject = new CGoomba(position, type);

					if (state != 0)
					{
						gameObject->SetState(state);
					}
					break;
				}
				case OBJECT_TYPE_KOOPA:
				{
					gameObject = new CKoopa(position);
					break;
				}
				case OBJECT_TYPE_RED_KOOPA:
				{
					LPGAMEOBJECT block = new CKoopaEdgeDetect(position + D3DXVECTOR2(0,14.0f));

					gameObject = new CRedKoopa(position, block);
					grid->AddGameObject(block);
					break;
				}

				case OBJECT_TYPE_BRICK:
				{
					int behavior = 0, itemContain = 0;

					gameObjectNode->QueryIntAttribute("behavior", &behavior);
					gameObjectNode->QueryIntAttribute("itemContain", &itemContain);

					gameObject = new CBrick(position, behavior, itemContain);
					break;
				}
				case OBJECT_TYPE_CLOUD_PLATFORM:
				{
					int w = 0, h = 0, num = 0;
					gameObjectNode->QueryIntAttribute("w", &w);
					gameObjectNode->QueryIntAttribute("h", &h);
					gameObjectNode->QueryIntAttribute("num", &num);

					string spriteBegin = gameObjectNode->Attribute("spriteBegin");
					string spriteMidder = gameObjectNode->Attribute("spriteMidder");
					string spriteEnd = gameObjectNode->Attribute("spriteEnd");

					gameObject = new CPlatform(x, y, w, h, num, spriteBegin, spriteMidder, spriteEnd);
					break;
				}
				case OBJECT_TYPE_GROUND:
				{
					int w = 0, h = 0;
					gameObjectNode->QueryIntAttribute("w", &w);
					gameObjectNode->QueryIntAttribute("h", &h);

					gameObject = new CGround(x, y, w, h);
					break;
				}

				case OBJECT_TYPE_COLORBOX:
				{
					int w = 0, h = 0;
					gameObjectNode->QueryIntAttribute("w", &w);
					gameObjectNode->QueryIntAttribute("h", &h);
					gameObject = new CColorBox(x, y, w, h);
					break;
				}
				case  OBJECT_TYPE_COIN:
				{
					gameObject = new CCoin(position);
					break;
				}
				case  OBJECT_TYPE_PLANT:
				{
					int plantType = PLANT_STATE_BITE;
					gameObjectNode->QueryIntAttribute("Type", &plantType);

					gameObject = new CPlant(position, plantType);
					break;
				}

				case OBJECT_TYPE_PORTAL:
				{
					string nextScene = gameObjectNode->Attribute("nextScene");

					gameObject = new CPortal(x, y, nextScene);
					break;
				}

				default:
				{
					gameObject = NULL;
					break;
				}
				}

				if (gameObject != NULL)
					grid->AddGameObject(gameObject);
			}
		}
	}

	else
	{
		DebugOut(L"[ERROR] Failed to load GameObjects file \"%s\"\n", ToLPCWSTR(filePath));
		return;
	}
	DebugOut(L"[INFO] Done loading GameObjects from \"%s\"\n", ToLPCWSTR(filePath));
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : \"%s\"\n", ToLPCWSTR(sceneFilePath));
	LPKeyHandler.clear();
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
				else if (strcmp(resourceType, "GameObjects") == 0)
				{
					const char* filePath = resourcePathNode->Attribute("filePath");
					LoadGameObjects(filePath);
				}
				else if(strcmp(resourceType, "Grid") == 0)
				{
					int w = 0, h = 0, cs = 0;
					resourcePathNode->QueryIntAttribute("width", &w);
					resourcePathNode->QueryIntAttribute("height", &h);
					resourcePathNode->QueryIntAttribute("CellSize", &cs);
					grid = new CGrid(w, h, cs);

					CCamera::GetInstance()->SetWorldSize(D3DXVECTOR2(w, h));
				}
				else if (strcmp(resourceType, "TitleMap") == 0)
				{
					const char* filePath = resourcePathNode->Attribute("filePath");

					tileMap = new CTileMap( filePath);

					
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

void CPlayScene::Update(DWORD dt)
{

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	if (isPausing)
	{
		if (GetTickCount64() > startPauseTime + pauseTime)
		{
			isPausing = 0;
			player->EndChangingForm();
		}
		return;
	}
	CCamera* camera = CCamera::GetInstance();

	tileMap->SetTileRender(camera->GetPosition(), camera->GetPosition()+ D3DXVECTOR2(303, 202));

	grid->SetCellUpdate(camera->GetPosition(), camera->GetPosition()+ D3DXVECTOR2(303, 202));

	grid->Update(dt);
	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	tileMap->Render();
	grid->Render();
}

/*
*	Clear all LPGameObject from this scene
*/

/*
	Unload scene

	TODO: Beside LPGameObject, we need to clean up sprites, animations and textures as well

*/
void CPlayScene::Unload()
{
	player = NULL;
	delete tileMap;
	tileMap = NULL;
	delete grid;
	grid = NULL;
}


void CPlayScene::PurgeDeletedObjects()
{
	grid->PurgeDeletedObjects();
}

void CPlayScene::AddGameObject(LPGAMEOBJECT gameObject)
{
	grid->AddGameObject(gameObject);
}



