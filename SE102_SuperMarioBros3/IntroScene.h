#pragma once
#include "Scene.h"

#include "Animations.h"
#include "Camera.h"
#include "Graphics.h"
#include "TinyXML/tinyxml.h"
#include "Textures.h"
#include "IntroArrow.h"

class CIntroScene :
    public CScene
{
protected:
	CIntroArrow* introArrow;
	void LoadAssets(const char* filePath);
public:
	CIntroScene(string id, string filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

};

