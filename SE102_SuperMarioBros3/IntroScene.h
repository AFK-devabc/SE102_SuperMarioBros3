#pragma once
#include "Scene.h"

#include "Animations.h"
#include "Camera.h"
#include "Graphics.h"
#include "TinyXML/tinyxml.h"
#include "Textures.h"
#include "IntroArrow.h"
#include <vector>
#include "GameObject.h"

class CIntroScene :
    public CScene
{
protected:

	CIntroArrow* introArrow;
	void LoadAssets(const char* filePath);

	DWORD introTime;
	int eventCount = 0;
	void LoadGameObject();

	LPGAMEOBJECT ground, roof;
	D3DXVECTOR2 titlePosition;
	D3DXVECTOR2 groundPosition;
	D3DXVECTOR2 roofPosition;
	D3DXVECTOR2 leftTreePosition, rightTreePosition;

public:
	CIntroScene(string id, string filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

};

