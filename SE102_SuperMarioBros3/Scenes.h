#pragma once
#include <unordered_map>

#include "Scene.h"
#include "debug.h"

class CScenes
{
private:
	static CScenes* __instance;




	unordered_map<string, LPSCENE> scenes;
	string currentScene = "";
	string nextScene = "";

	const char* filePath = "Resources/Scenes.xml";
public:
	CScenes();

	void InitScenes();

	LPSCENE GetCurrentScene();
	void SwitchScene();

	void InitiateSwitchScene(string id);

	static CScenes* GetInstance();

};

