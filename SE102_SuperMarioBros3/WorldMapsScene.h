#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Hub.h"
#include "WorldMapMario.h"
#include "WorldMap.h"
		
#include "Animations.h"


class CWorldMapsScene :
    public CScene
{
protected:
	CHub* Hub;
	void LoadAssets(const char* filePath);
	CWorldMap* worldMap;
	CWorldMapMario* mario;
	D3DXVECTOR2 enemyPosition;
	float enemyVx = 0.01f;

	CGameOverArrow* gameOverArrow;

	void LoadGameObject();

public:
	CWorldMapsScene(string id, string filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void ResetGame();
};

