#pragma once
#include <vector>

#include "Scene.h"
#include "Game.h"

#include "GameObject.h"
#include "CPlayer.h"
#include "Goomba.h"
#include "Platform.h"

#include "TinyXML/tinyxml.h"
#include "Animations.h"
#include "Textures.h"
#include "Sprites.h"

class CPlayScene : 
	public CScene
{
protected:
	// A play scene has to have player, right? 
	 CPlayer* player;

	vector<LPGAMEOBJECT> LPGameObject;

	void LoadAssets(const char* filePath);
	void LoadGameObjects(const char* filePath);
public:
	CPlayScene(int id, const char* filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

