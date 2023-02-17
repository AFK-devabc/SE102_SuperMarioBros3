#pragma once

#include "KeyEventHandler.h"
#include <vector>
#include "SceneDefineInfo.h"

/*
*  Abstract class for a game scene
*/
class CScene
{
protected:
	vector<LPKEYEVENTHANDLER> LPKeyHandler;

	string id;
	string sceneFilePath;
	DWORD startStateTime, totalStateTime;
	int state;

public:
	CScene(string id,string filepath)
	{
		this->id = id;
		this->sceneFilePath = filepath;
		this->LPKeyHandler.clear();

		state = SCENE_STATE_PLAYING;
	}

	vector<LPKEYEVENTHANDLER> GetKeyEventHandler()
	{
		return LPKeyHandler;
	}
	virtual void SetPause(DWORD t) { startStateTime = GetTickCount64(); totalStateTime = t; SetState(SCENE_STATE_PAUSING); }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

	virtual void SetState(int state) { this->state = state; }
	int GetState() { return state; }

};
typedef CScene* LPSCENE;