#include "Scenes.h"
#include "Animations.h"
#include "Sprites.h"

#include "PlayScene.h"
#include "WorldMapsScene.h"
#include "IntroScene.h"
#include "TinyXML/tinyxml.h"

CScenes* CScenes::__instance = NULL;

CScenes::CScenes()
{
	__instance = this;
}

void CScenes::InitScenes()
{
	DebugOut(L"[INFO] Start loading Scenes from : \"%s\"\n", ToLPCWSTR(filePath));
	TiXmlDocument doc(filePath);
	if (doc.LoadFile())
	{
		TiXmlElement* Root = doc.RootElement();
		if (Root)
		{
			for (TiXmlElement* scene = Root->FirstChildElement(); scene != nullptr; scene = scene->NextSiblingElement())
			{
				string id = scene->Attribute("ID");
				string filePath = scene->Attribute("scenePath");
				if (this->nextScene == "")
					nextScene = id;
				int type = -1;
				scene->QueryIntAttribute("type", &type);
				switch (type)
				{
				case 1:
				{
					CScene* temp = new CIntroScene(id, filePath);
					scenes[id] = temp;
					break;
				}
				case 2:
				{
					CScene* temp = new CWorldMapsScene(id, filePath);
					scenes[id] = temp;
					break;
				}
				case 3:
				{
					CScene* temp = new CPlayScene(id, filePath);
					scenes[id] = temp;
					break;
				}
				default:
				{
					break;
				}
				}
			}
		}
	}
	else
	{
		DebugOut(L"[ERROR] Failed to load Scenes file \"%s\"\n", ToLPCWSTR(filePath));
		return;
	}
	DebugOut(L"[INFO] Done loading Scenes from \"%s\"\n", ToLPCWSTR(filePath));

}

LPSCENE CScenes::GetCurrentScene()
{
	return scenes[currentScene];
}

void CScenes::SwitchScene()
{
	if (nextScene == ""|| nextScene == currentScene) return;

	DebugOut(L"[INFO] Switching to scene %s\n", ToLPCWSTR(nextScene));

	if(currentScene != "")
	scenes[currentScene]->Unload();
	CTextures::GetInstance()->Clear();
	CSprites::GetInstance()->Clear();
	CAnimations::GetInstance()->Clear();
	CKeyBoard::GetInstance()->Clear();

	currentScene = nextScene;
	LPSCENE s = scenes[nextScene];
	s->Load();
	
	CKeyBoard::GetInstance()->SetKeyHandler(s->GetKeyEventHandler());

}

void CScenes::InitiateSwitchScene(string id)
{
	nextScene = id;
}

CScenes* CScenes::GetInstance()
{
	if (__instance == NULL) __instance = new CScenes();
	
	return __instance;
}
