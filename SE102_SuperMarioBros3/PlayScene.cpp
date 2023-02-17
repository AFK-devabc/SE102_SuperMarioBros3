#include "PlayScene.h"
#include "GameObjectType.h"
#include "WorldMap.h"

CPlayScene::CPlayScene(string id, string filePath) :
	CScene(id, filePath)
{
	player = NULL;
	Hub = CHub::GetInstance();
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

void CPlayScene::LoadGameObjects(const char* filePath)
{
	DebugOut(L"[INFO] Start loading GameObjects from : \"%s\"\n", ToLPCWSTR(filePath));
	TiXmlDocument doc(filePath);
	LPBrick.clear();
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

					player->SetMarioType(CWorldMap::GetInstance()->GetMarioType(), false);

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
					int  state = 0;
					gameObjectNode->QueryIntAttribute("state", &state);

					gameObject = new CKoopa(position);
					gameObject->SetState(state);
					break;
				}
				case OBJECT_TYPE_RED_KOOPA:
				{
					int  state = 0;
					gameObjectNode->QueryIntAttribute("state", &state);


					LPGAMEOBJECT block = new CKoopaEdgeDetect(position + D3DXVECTOR2(0,14.0f));

					gameObject = new CRedKoopa(position, block);
					gameObject->SetState(state);

					grid->AddGameObject(block);
					break;
				}

				case OBJECT_TYPE_BRICK:
				{
					gameObject = new CBrick(position);
					LPBrick.push_back(gameObject);
					break;
				}
				case OBJECT_TYPE_QUESTION_MARK:
				{
					int itemContain = 0;
					gameObjectNode->QueryIntAttribute("itemContain", &itemContain);

					gameObject = new CItemContainer(position, itemContain, OBJECT_TYPE_QUESTION_MARK);

					break;
				}
				case OBJECT_TYPE_FAKE_BRICK:
				{
					int itemContain = 0;
					gameObjectNode->QueryIntAttribute("itemContain", &itemContain);

					gameObject = new CItemContainer(position, itemContain, OBJECT_TYPE_BRICK);
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
				case OBJECT_TYPE_CHECKPOINT:
				{
					int blockX, blockY;
					gameObjectNode->QueryIntAttribute("blockX", &blockX);
					gameObjectNode->QueryIntAttribute("blockY", &blockY);
					LPGAMEOBJECT checkpointBlock = new CGround(blockX, blockY, 1, 128);
					grid->AddGameObject(checkpointBlock);
					gameObject = new CCheckPoint(position, checkpointBlock);

					break;
				}
				case OBJECT_TYPE_PINEPORTAL:
				{
					int desx,desy,camx,camy, type;
					gameObjectNode->QueryIntAttribute("desx", &desx);
					gameObjectNode->QueryIntAttribute("desy", &desy);
					gameObjectNode->QueryIntAttribute("camx", &camx);
					gameObjectNode->QueryIntAttribute("camy", &camy);
					gameObjectNode->QueryIntAttribute("type", &type);

					gameObject = new CPinePortal(position, D3DXVECTOR2(desx,desy), D3DXVECTOR2(camx,camy), type);

					break;
				}
				case OBJECT_TYPE_EMPTY_SPACE:
				{
					int length;
					gameObjectNode->QueryIntAttribute("length", &length);
					string nextScene = gameObjectNode->Attribute("nextScene");

					gameObject = new CEmptySpace(position, length, nextScene);
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

	CHub::GetInstance()->ReloadHub(GAME_PLAY_TIME);

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
	D3DXVECTOR2 camPosition = CCamera::GetInstance()->GetPosition();

	tileMap->SetTileRender(camPosition, camPosition + D3DXVECTOR2(303, 202));

	grid->SetCellUpdate(camPosition, camPosition + D3DXVECTOR2(303, 202));

	grid->Update(dt);
	Hub->Update(dt, player);
	for (int i = 0; i < LPBrick.size();i++)
		if (LPBrick[i]->IsDeleted())
			LPBrick.erase(LPBrick.begin() + i);
	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	tileMap->Render();
	grid->Render();
	Hub->Render();
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
	CWorldMap::GetInstance()->SetMarioType(player->GetMarioType());

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



