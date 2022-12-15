#pragma once
#include <vector>

#include "Scene.h"
#include "Game.h"

#include "GameObject.h"
#include "CPlayer.h"
#include "Goomba.h"
#include "Platform.h"
#include "Brick.h"
#include "MushRoom.h"
#include "Coin.h"
#include "Koopa.h"
#include "RedKoopa.h"
#include "KoopaEdgeDetect.h"
#include "CColorBox.h"
#include "Portal.h"
#include "Ground.h"

#include "TinyXML/tinyxml.h"
#include "Animations.h"
#include "Textures.h"
#include "Sprites.h"

#include "Grid.h"
#include "TileMap.h"

class CPlayScene : 
	public CScene
{
protected:
	// A play scene has to have player, right? 
	 CPlayer* player;

	CGrid* grid;
	CTileMap* tileMap;
	void LoadAssets(const char* filePath);
	void LoadGameObjects(const char* filePath);
public:
	CPlayScene(string id, string filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void PurgeDeletedObjects();

	void AddGameObject(LPGAMEOBJECT gameObject);
	void AddGameEffect(LPGAMEOBJECT gameObject);

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

