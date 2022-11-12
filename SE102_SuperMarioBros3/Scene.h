#pragma once

#include "KeyEventHandler.h"
#include <vector>
/*
*  Abstract class for a game scene
*/
class CScene
{
protected:
	vector<LPKEYEVENTHANDLER> LPKeyHandler;

	string id;
	string sceneFilePath;

public:
	CScene(string id,string filepath)
	{
		this->id = id;
		this->sceneFilePath = filepath;
		this->LPKeyHandler.clear();
	}

	vector<LPKEYEVENTHANDLER> GetKeyEventHandler()
	{
		return LPKeyHandler;
	}
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
typedef CScene* LPSCENE;